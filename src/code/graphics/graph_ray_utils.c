/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_ray_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:56:40 by misaac-c          #+#    #+#             */
/*   Updated: 2025/03/24 11:29:09 by misaac-c         ###   ########.fr       */
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
	ray->screenWidth = game->width / 2.5;
	ray->screenHeight = game->height / 2;
	ray->FOV = 60.0f * (PI / 180.0f);
}

void	replace_ternaries(t_ray *ray)
{
	if (ray->rayDirX2 == 0)
		ray->deltaDistX = 1e30f;
	else
		ray->deltaDistX = fabs(1.0f / ray->rayDirX2);
	if (ray->rayDirY2 == 0)
		ray->deltaDistY = 1e30f;
	else
		ray->deltaDistY = fabs(1.0f / ray->rayDirY2);
	if (ray->rayDirX2 < 0)
		ray->stepX = -1;
	else
		ray->stepX = 1;
	if (ray->rayDirY2 < 0)
		ray->stepY = -1;
	else
		ray->stepY = 1;
	if (ray->rayDirX2 < 0)
		ray->sideDistX = (ray->posX - ray->mapX) * ray->deltaDistX;
	else
		ray->sideDistX = (ray->mapX + 1.0f - ray->posX) * ray->deltaDistX;
	if (ray->rayDirY2 < 0)
		ray->sideDistY = (ray->posY - ray->mapY) * ray->deltaDistY;
	else
		ray->sideDistY = (ray->mapY + 1.0f - ray->posY) * ray->deltaDistY;
}

void	init_cast_ray(t_ray *ray, t_game *game)
{
	ray->posX = game->px;
	ray->posY = game->py;
	ray->rayDirX2 = cos(ray->ray_angle);
	ray->rayDirY2 = sin(ray->ray_angle);
	ray->mapX = (int)ray->posX;
	ray->mapY = (int)ray->posY;
	ray->hit = 0;
	ray->side = 0;
	replace_ternaries(ray);
}

t_img	*texturing(t_ray *ray, t_game *game, t_img *texture)
{
	if (ray->side == 0)
	{
		if (ray->stepX > 0)
			texture = &game->tex_E;
		else
			texture = &game->tex_W;
	}
	else
	{
		if (ray->stepY > 0)
			texture = &game->tex_S;
		else
			texture = &game->tex_N;
	}
	return (texture);
}
