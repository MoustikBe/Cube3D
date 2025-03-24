/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_moov.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:40:17 by misaac-c          #+#    #+#             */
/*   Updated: 2025/03/24 12:02:33 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cube.h"
#include "../../libs/libft/libft.h"
#include "../../libs/minilibx-linux/mlx.h"

int	moov_front(t_game *game, float new_x, float new_y)
{
	new_x = game->px + game->pdx;
	new_y = game->py + game->pdy;
	if (game->cube->map[(int)(new_y)][(int)(new_x)] == '1')
		return (2);
	else
	{
		game->px = new_x;
		game->py = new_y;
		ray_tracer(game);
	}
	return (0);
}

int	moov_back(t_game *game, float new_x, float new_y)
{
	new_x = game->px - game->pdx;
	new_y = game->py - game->pdy;
	if (game->cube->map[(int)(new_y)][(int)(new_x)] == '1')
		return (2);
	else
	{
		game->px = new_x;
		game->py = new_y;
		ray_tracer(game);
	}
	return (0);
}

void	rotate_left(t_game *game)
{
	game->pa -= 0.1;
	if (game->pa < 0)
		game->pa += 2 * PI;
	game->pdx = cos(game->pa) * 0.05;
	game->pdy = sin(game->pa) * 0.05;
	ray_tracer(game);
}

void	rotate_right(t_game *game)
{
	game->pa += 0.1;
	if (game->pa > 2 * PI)
		game->pa -= 2 * PI;
	game->pdx = cos(game->pa) * 0.05;
	game->pdy = sin(game->pa) * 0.05;
	ray_tracer(game);
}
