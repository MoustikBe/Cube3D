/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_raycast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 10:44:54 by misaac-c          #+#    #+#             */
/*   Updated: 2025/03/24 11:34:53 by misaac-c         ###   ########.fr       */
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
		if (ray->sideDistX < ray->sideDistY)
		{
			ray->sideDistX += ray->deltaDistX;
			ray->mapX += ray->stepX;
			ray->side = 0;
		}
		else
		{
			ray->sideDistY += ray->deltaDistY;
			ray->mapY += ray->stepY;
			ray->side = 1;
		}
		if (game->cube->map[ray->mapY][ray->mapX] == '1')
			ray->hit = 1;
	}
	if (ray->side == 0)
		ray->perpWallDist = (ray->mapX - ray->posX
				+ (1 - ray->stepX) / 2.0f) / ray->rayDirX2;
	else
		ray->perpWallDist = (ray->mapY - ray->posY
				+ (1 - ray->stepY) / 2.0f) / ray->rayDirY2;
	return ;
}

void	ray_calcul(t_ray *ray, t_game *game)
{
	ray->ray_angle = game->pa - (ray->FOV / 2.0f)
		+ ((float)ray->x / (float)ray->screenWidth) * ray->FOV;
	cast_ray(game, ray);
	ray->correctedDist = ray->perpWallDist * cos(ray->ray_angle - game->pa);
	if (ray->correctedDist < 0.1f)
		ray->correctedDist = 0.1f;
	ray->lineHeight = (int)(ray->screenHeight / ray->correctedDist);
	ray->drawStart = -ray->lineHeight / 2 + ray->screenHeight / 2;
	if (ray->drawStart < 0)
		ray->drawStart = 0;
	ray->drawEnd = ray->lineHeight / 2 + ray->screenHeight / 2;
	if (ray->drawEnd >= ray->screenHeight)
		ray->drawEnd = ray->screenHeight - 1;
}

void	drawing_wall_x(t_ray *ray, t_game *game, t_img *texture)
{
	if (ray->side == 0)
		ray->wallX = game->py + ray->perpWallDist * ray->rayDirY;
	else
		ray->wallX = game->px + ray->perpWallDist * ray->rayDirX;
	ray->wallX -= floor(ray->wallX);
	ray->textureX = (int)(ray->wallX * (float)texture->width);
	if ((ray->side == 0 && ray->rayDirX > 0)
		|| (ray->side == 1 && ray->rayDirY < 0))
		ray->textureX = texture->width - ray->textureX - 1;
	ray->y = ray->drawStart;
	while (ray->y < ray->drawEnd)
	{
		ray->d = (ray->y - (ray->screenHeight / 2) + (ray->lineHeight / 2));
		ray->textureY = (ray->d * texture->height) / ray->lineHeight;
		ray->color = texture->data[ray->textureY
			* texture->width + ray->textureX];
		my_mlx_pixel_put3d(game, ray->x, ray->y, ray->color);
		ray->y++;
	}
}

void	drawing_floor_x(t_ray *ray, t_game *game)
{
	ray->y = ray->drawEnd;
	while (ray->y < ray->screenHeight)
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
	while (ray->x < ray->screenWidth)
	{
		ray_calcul(ray, game);
		ray->y = 0;
		while (ray->y < ray->drawStart)
		{
			my_mlx_pixel_put3d(game, ray->x, ray->y, game->ceiling_color);
			ray->y++;
		}
		ray->rayDirX = cos(ray->ray_angle);
		ray->rayDirY = sin(ray->ray_angle);
		texture = texturing(ray, game, texture);
		drawing_wall_x(ray, game, texture);
		drawing_floor_x(ray, game);
	}
	mlx_put_image_to_window(game->mlx3d, game->wdw3d, game->img3d, 0, 0);
	free(ray);
}
