/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_moov_rotate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 11:57:36 by misaac-c          #+#    #+#             */
/*   Updated: 2025/06/23 16:56:40 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cube.h"
#include "../../libs/libft/libft.h"
#include "../../libs/minilibx-linux/mlx.h"

void	rotate_left(t_game *game)
{
	game->pa -= 0.05;
	if (game->pa < 0)
		game->pa += 2 * PI;
	game->pdx = cos(game->pa) * 0.05;
	game->pdy = sin(game->pa) * 0.05;
	ray_tracer(game);
}

void	rotate_right(t_game *game)
{
	game->pa += 0.05;
	if (game->pa > 2 * PI)
		game->pa -= 2 * PI;
	game->pdx = cos(game->pa) * 0.05;
	game->pdy = sin(game->pa) * 0.05;
	ray_tracer(game);
}
