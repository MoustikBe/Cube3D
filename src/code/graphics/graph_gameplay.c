/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_gameplay.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:02:01 by misaac-c          #+#    #+#             */
/*   Updated: 2025/06/23 16:56:40 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cube.h"
#include "../../libs/libft/libft.h"
#include "../../libs/minilibx-linux/mlx.h"

int	exit_game(t_game *game)
{
	mlx_destroy_window(game->mlx3d, game->wdw3d);
	free(game->mlx3d);
	exit(1);
}

int	mng_input(t_game *game)
{
	if (game->exit)
		exit_game(game);
	if (game->front)
		if (move_front(game, 0, 0))
			return (2);
	if (game->back)
		if (move_back(game, 0, 0))
			return (2);
	if (game->left)
		if (move_left(game, 0, 0))
			return (2);
	if (game->right)
		if (move_right(game, 0, 0))
			return (2);
	if (game->r_right)
		rotate_right(game);
	if (game->r_left)
		rotate_left(game);
	return (0);
}

int	game_loop(t_game *game)
{
	if (game->front || game->back || game->r_left
		|| game->r_right || game->exit
		|| game->right || game->left)
		mng_input(game);
	return (0);
}
