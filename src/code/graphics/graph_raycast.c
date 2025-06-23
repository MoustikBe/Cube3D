/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_raycast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 10:44:54 by misaac-c          #+#    #+#             */
/*   Updated: 2025/03/24 11:59:40 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cube.h"
#include "../../libs/libft/libft.h"
#include "../../libs/minilibx-linux/mlx.h"

void	cast_ray(t_game *game, t_ray *ray) //init ray's info, calculate DDA values and find the first wall the ray hits, gets ray length until wall
{
	init_cast_ray(ray, game); //inits ray's position and direction and calculates DDA values such as delta distances
	while (!ray->hit) //while we don't hit a wall
	{
		if (ray->sidedistx < ray->sidedisty) //compares which one is closer (distance to the horizontal or vertical wall?)
		{ //if it's closer to the vertical gridline
			ray->sidedistx += ray->deltadistx; //read the one below this one first (this line increases the distance to the next vertical gridline)
			ray->mapx += ray->stepx; //we take a step forward to it
			ray->side = 0; //we set it to 0 to mean that we hit a VERTICAL wall
		}
		else //if it's closer to the horizontal gridline
		{
			ray->sidedisty += ray->deltadisty; 
			ray->mapy += ray->stepy; //we take a step towards it
			ray->side = 1; //we set it to 1 to mean that we hit a HORIZONTAL wall
		}
		if (game->cube->map[ray->mapy][ray->mapx] == '1') //if this new grid is a wall (1), we set hit to 1 to stop the loop, since we already hit the wall
			ray->hit = 1;
	} //now we get the raw distance to the wall along the ray (no fisheye correction yet)
	if (ray->side == 0)
		ray->perpwalldist = (ray->mapx - ray->posx //perpwalldist is the raw distance to the grid along the ray (no fisheye correction yet)
				+ (1 - ray->stepx) / 2.0f) / ray->raydirx2; //stepx is 1 if going right and -1 if going left
	else
		ray->perpwalldist = (ray->mapy - ray->posy //same logic for the vertical side
				+ (1 - ray->stepy) / 2.0f) / ray->raydiry2;
	return ;
}

void	ray_calcul(t_ray *ray, t_game *game) //calculates a ray's angle and starting/ending pixels, calculates DDA values
{
	ray->ray_angle = game->pa - (ray->fov / 2.0f) //Calculate this ray's specific angle, by dividing the fov (60º) in two, one half for the right rays and another half for the left rays
		+ ((float)ray->x / (float)ray->screenwidth) * ray->fov;
	cast_ray(game, ray); //init ray's info, calculate DDA values and find the first wall the ray hits
	ray->correcteddist = ray->perpwalldist * cos(ray->ray_angle - game->pa); //we get the correcteddist (straight ahead to avoid fisheye)
	if (ray->correcteddist < 0.1f) //if it's less than 0.1 we set it to 0.1 to avoid division by zero
		ray->correcteddist = 0.1f;
	ray->lineheight = (int)(ray->screenheight / ray->correcteddist); //calculate height of the wall slice to draw (farther, smaller; or closer, bigger)
	ray->drawstart = -ray->lineheight / 2 + ray->screenheight / 2; //draw start is the start pixel of the wall slice
	if (ray->drawstart < 0) //we center the wall around the middle of the screen (screenheight / 2)
		ray->drawstart = 0;
	ray->drawend = ray->lineheight / 2 + ray->screenheight / 2; //draw end is the last pixel of the wall slice
	if (ray->drawend >= ray->screenheight)
		ray->drawend = ray->screenheight - 1;
}

void	drawing_wall_x(t_ray *ray, t_game *game, t_img *texture) //draws a vertical wall
{
	if (ray->side == 0) //for vertical walls
		ray->wallx = game->py + ray->perpwalldist * ray->raydiry; //calculate where exactly the ray hit
	else //for horizontal walls
		ray->wallx = game->px + ray->perpwalldist * ray->raydirx;
	ray->wallx -= floor(ray->wallx); //floor is a function from math.h, it returns the closest smaller integer. Example 4.9-> 4
	ray->texturex = (int)(ray->wallx * (float)texture->width); //calculates which column of the texture to draw (example: if we hit at 0.6 and the texture width is 64, 0.6 x 64 = 38,  we sample column 38)
	if ((ray->side == 0 && ray->raydirx > 0) //if we hit east or north walls, we flip the x coordinate to mirror the coordinates
		|| (ray->side == 1 && ray->raydiry < 0))
		ray->texturex = texture->width - ray->texturex - 1;
	ray->y = ray->drawstart;
	while (ray->y < ray->drawend) //loop from the top of the wall until the bottom of the wall
	{
		ray->d = (ray->y - (ray->screenheight / 2) + (ray->lineheight / 2)); //d is how far we are down the wall slice (0 is at the top and the higher it is, the more bottom you are)
		ray->texturey = (ray->d * texture->height) / ray->lineheight;
		ray->color = texture->data[ray->texturey
			* texture->width + ray->texturex]; //picks the rigth color from the texture
		my_mlx_pixel_put3d(game, ray->x, ray->y, ray->color); //draws the color using the coordinates at x and y
		ray->y++;
	}
}

void	drawing_floor_x(t_ray *ray, t_game *game) //draws the floor pixels for a single vertical column on the screen
{
	ray->y = ray->drawend; //starts on the pixel just below the wall
	while (ray->y < ray->screenheight) //loops until the bottom of the screen
	{
		my_mlx_pixel_put3d(game, ray->x, ray->y, game->floor_color); //draws a solid color
		ray->y++;
	}
	ray->x++;
}

void	ray_tracer(t_game *game) //draws the walls
{
	t_ray	*ray;
	t_img	*texture;

	ray = malloc(sizeof(t_ray));
	init_ray(ray, game); //converts from 60º (typical angle in FPS) to radians
	ray->x = 0;
	while (ray->x < ray->screenwidth) //we loop through each column of the window screen (one ray per vertical column)
	{
		ray_calcul(ray, game); //calculates a ray's angle and starting/ending pixels, calculates DDA values, corrects fisheye
		ray->y = 0;
		while (ray->y < ray->drawstart) //draw ceiling pixels from the top of the screen to the starting pixel of the line (called once per vertical line)
		{
			my_mlx_pixel_put3d(game, ray->x, ray->y, game->ceiling_color); //draw ceiling pixels
			ray->y++;
		}
		ray->raydirx = cos(ray->ray_angle); //raydirx is adjacent cathetus
		ray->raydiry = sin(ray->ray_angle); //raydiry is opposite cathetus
		texture = texturing(ray, game, texture); //returns the correct texture (north, south, west or east)
		drawing_wall_x(ray, game, texture); //draws a vertical wall
		drawing_floor_x(ray, game); //draws the floor pixels for a single vertical column on the screen
	}
	mlx_put_image_to_window(game->mlx3d, game->wdw3d, game->img3d, 0, 0); //draw the image on the window
	free(ray); //free to avoid leaks
}
