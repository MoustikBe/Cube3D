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

void	cast_ray(t_game *game, t_ray *ray)
{
	init_cast_ray(ray, game);
	while (!ray->hit)
	{
		if (ray->sidedistx < ray->sidedisty)
		{
			ray->sidedistx += ray->deltadistx;
			ray->mapx += ray->stepx;
			ray->side = 0;
		}
		else
		{
			ray->sidedisty += ray->deltadisty;
			ray->mapy += ray->stepy;
			ray->side = 1;
		}
		if (game->cube->map[ray->mapy][ray->mapx] == '1')
			ray->hit = 1;
	}
	if (ray->side == 0)
		ray->perpwalldist = (ray->mapx - ray->posx
				+ (1 - ray->stepx) / 2.0f) / ray->raydirx2;
	else
		ray->perpwalldist = (ray->mapy - ray->posy
				+ (1 - ray->stepy) / 2.0f) / ray->raydiry2;
	return ;
}

void	ray_calcul(t_ray *ray, t_game *game)
{
	ray->ray_angle = game->pa - (ray->fov / 2.0f)
		+ ((float)ray->x / (float)ray->screenwidth) * ray->fov;
	cast_ray(game, ray);
	ray->correcteddist = ray->perpwalldist * cos(ray->ray_angle - game->pa);
	if (ray->correcteddist < 0.1f)
		ray->correcteddist = 0.1f;
	ray->lineheight = (int)(ray->screenheight / ray->correcteddist);
	ray->drawstart = -ray->lineheight / 2 + ray->screenheight / 2;
	if (ray->drawstart < 0)
		ray->drawstart = 0;
	ray->drawend = ray->lineheight / 2 + ray->screenheight / 2;
	if (ray->drawend >= ray->screenheight)
		ray->drawend = ray->screenheight - 1;
}

void	drawing_wall_x(t_ray *ray, t_game *game, t_img *texture)
{
	if (ray->side == 0)
		ray->wallx = game->py + ray->perpwalldist * ray->raydiry;
	else
		ray->wallx = game->px + ray->perpwalldist * ray->raydirx;
	ray->wallx -= floor(ray->wallx);
	ray->texturex = (int)(ray->wallx * (float)texture->width);
	if ((ray->side == 0 && ray->raydirx > 0)
		|| (ray->side == 1 && ray->raydiry < 0))
		ray->texturex = texture->width - ray->texturex - 1;
	ray->y = ray->drawstart;
	while (ray->y < ray->drawend)
	{
		ray->d = (ray->y - (ray->screenheight / 2) + (ray->lineheight / 2));
		ray->texturey = (ray->d * texture->height) / ray->lineheight;
		ray->color = texture->data[ray->texturey
			* texture->width + ray->texturex];
		my_mlx_pixel_put3d(game, ray->x, ray->y, ray->color);
		ray->y++;
	}
}

void	drawing_floor_x(t_ray *ray, t_game *game)
{
	ray->y = ray->drawend;
	while (ray->y < ray->screenheight)
	{
		my_mlx_pixel_put3d(game, ray->x, ray->y, game->floor_color);
		ray->y++;
	}
	ray->x++;
}

void	ray_tracer(t_game *game)
{
	t_ray	*ray;
	t_img	*texture;

	ray = malloc(sizeof(t_ray));
	init_ray(ray, game);
	ray->x = 0;
	while (ray->x < ray->screenwidth)
	{
		ray_calcul(ray, game);
		ray->y = 0;
		while (ray->y < ray->drawstart)
		{
			my_mlx_pixel_put3d(game, ray->x, ray->y, game->ceiling_color);
			ray->y++;
		}
		ray->raydirx = cos(ray->ray_angle);
		ray->raydiry = sin(ray->ray_angle);
		texture = texturing(ray, game, texture);
		drawing_wall_x(ray, game, texture);
		drawing_floor_x(ray, game);
	}
	mlx_put_image_to_window(game->mlx3d, game->wdw3d, game->img3d, 0, 0);
	free(ray);
}
