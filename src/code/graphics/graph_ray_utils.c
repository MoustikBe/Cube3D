/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_ray_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:56:40 by misaac-c          #+#    #+#             */
/*   Updated: 2025/03/24 11:59:36 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cube.h"
#include "../../libs/libft/libft.h"
#include "../../libs/minilibx-linux/mlx.h"

void	my_mlx_pixel_put3d(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= game->width / 2.5 || y >= game->height / 2)
		return ;
	dst = game->addr3d + (y * game->line_length3d
			+ x * (game->bit_per_pixel3d / 8));
	*(unsigned int *)dst = color;
}

void	init_ray(t_ray *ray, t_game *game) //converts from 60º (typical angle in FPS) to radians
{
	ray->screenwidth = game->width / 2.5;
	ray->screenheight = game->height / 2;
	ray->fov = 60.0f * (PI / 180.0f); //converts from 60º (typical angle in FPS) to radians
}

void	set_dda_values(t_ray *ray) //calculates DDA values such as delta distance
{
	if (ray->raydirx2 == 0) //if the direction x is 0, it's a vertical ray
		ray->deltadistx = 1e30f; //deltadistx is how far you need to go to cross until the next square, 1e30f is a huge float number that we use instead of dividing by 0
	else
		ray->deltadistx = fabs(1.0f / ray->raydirx2);
	if (ray->raydiry2 == 0) //same here but for y direction
		ray->deltadisty = 1e30f;
	else
		ray->deltadisty = fabs(1.0f / ray->raydiry2); //calculates how much you need to move to cross a grid (more on this on code xplained on my notion)
	if (ray->raydirx2 < 0) //if the ray is pointing left (less than 0), the step is -1
		ray->stepx = -1;
	else
		ray->stepx = 1; //if the ray is pointing right (more than 0), the step is 1
	if (ray->raydiry2 < 0) //if the ray is pointing down (less than 0), the step is -1
		ray->stepy = -1;
	else
		ray->stepy = 1; //if the ray is pointing up (more than 0), the step is 1
	if (ray->raydirx2 < 0) //if the ray if going left, we calculate the distance to the grid from the left side 
		ray->sidedistx = (ray->posx - ray->mapx) * ray->deltadistx;
	else //if the ray if going left, we calculate the distance to the grid from the left side 
		ray->sidedistx = (ray->mapx + 1.0f - ray->posx) * ray->deltadistx; //you add 1 because in order to go to the next line you just need to use 1 unit each time
	if (ray->raydiry2 < 0) //if the ray if going down, we calculate the distance to the grid from the lower side 
		ray->sidedisty = (ray->posy - ray->mapy) * ray->deltadisty;
	else //if the ray if going up, we calculate the distance to the grid from the upper side 
		ray->sidedisty = (ray->mapy + 1.0f - ray->posy) * ray->deltadisty;
}

void	init_cast_ray(t_ray *ray, t_game *game) //inits ray position and direction and calculates DDA values such as delta distances
{
	ray->posx = game->px; //the ray starts exactly where the player is (px is player x coordinate)
	ray->posy = game->py; //in y coordinate
	ray->raydirx2 = cos(ray->ray_angle); //the angle in which the ray is casted
	ray->raydiry2 = sin(ray->ray_angle);
	ray->mapx = (int)ray->posx; //determine the current map square where the ray is at (by converting float 2.1 to int 2)
	ray->mapy = (int)ray->posy;
	ray->hit = 0; //flag that saves if the ray hit a wall
	ray->side = 0; //flag that saves if the ray hit a vertical or horizontal side
	set_dda_values(ray); //calculates DDA values such as delta distance (distance to move onto the next gridline)
}

t_img	*texturing(t_ray *ray, t_game *game, t_img *texture) //returns the correct texture (north, south, west or east)
{
	if (ray->side == 0) //based on whether we hit vertical wall (0) or horizontal wall (1)
	{
		if (ray->stepx > 0) //if it hit vertically and it was moving towards the right (> 0)
			texture = &game->tex_e; //east texture
		else
			texture = &game->tex_w; //west texture
	}
	else //if it hit the horizontal wall (1)
	{
		if (ray->stepy > 0) //if its coming from down
			texture = &game->tex_s; //south
		else
			texture = &game->tex_n; //north
	}
	return (texture);
}
