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

void	init_ray(t_ray *ray, t_game *game)
{
	ray->screenwidth = game->width / 2.5;
	ray->screenheight = game->height / 2;
	ray->fov = 60.0f * (PI / 180.0f);
}

void	replace_ternaries(t_ray *ray)
{
	if (ray->raydirx2 == 0)
		ray->deltadistx = 1e30f;
	else
		ray->deltadistx = fabs(1.0f / ray->raydirx2);
	if (ray->raydiry2 == 0)
		ray->deltadisty = 1e30f;
	else
		ray->deltadisty = fabs(1.0f / ray->raydiry2);
	if (ray->raydirx2 < 0)
		ray->stepx = -1;
	else
		ray->stepx = 1;
	if (ray->raydiry2 < 0)
		ray->stepy = -1;
	else
		ray->stepy = 1;
	if (ray->raydirx2 < 0)
		ray->sidedistx = (ray->posx - ray->mapx) * ray->deltadistx;
	else
		ray->sidedistx = (ray->mapx + 1.0f - ray->posx) * ray->deltadistx;
	if (ray->raydiry2 < 0)
		ray->sidedisty = (ray->posy - ray->mapy) * ray->deltadisty;
	else
		ray->sidedisty = (ray->mapy + 1.0f - ray->posy) * ray->deltadisty;
}

void	init_cast_ray(t_ray *ray, t_game *game)
{
	ray->posx = game->px;
	ray->posy = game->py;
	ray->raydirx2 = cos(ray->ray_angle);
	ray->raydiry2 = sin(ray->ray_angle);
	ray->mapx = (int)ray->posx;
	ray->mapy = (int)ray->posy;
	ray->hit = 0;
	ray->side = 0;
	replace_ternaries(ray);
}

t_img	*texturing(t_ray *ray, t_game *game, t_img *texture)
{
	if (ray->side == 0)
	{
		if (ray->stepx > 0)
			texture = &game->tex_e;
		else
			texture = &game->tex_w;
	}
	else
	{
		if (ray->stepy > 0)
			texture = &game->tex_s;
		else
			texture = &game->tex_n;
	}
	return (texture);
}
