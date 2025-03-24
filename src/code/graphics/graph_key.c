/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 10:42:23 by misaac-c          #+#    #+#             */
/*   Updated: 2025/03/24 12:03:02 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cube.h"
#include "../../libs/libft/libft.h"
#include "../../libs/minilibx-linux/mlx.h"

int	ft_key_press(int keycode, t_game *game)
{
	if (keycode == 119)
		game->front = 1;
	else if (keycode == 115)
		game->back = 1;
	else if (keycode == 97)
		game->r_left = 1;
	else if (keycode == 100)
		game->r_right = 1;
	else if (keycode == 65307)
		game->exit = 1;
	return (0);
}

int	ft_key_release(int keycode, t_game *game)
{
	if (keycode == 119)
		game->front = 0;
	else if (keycode == 115)
		game->back = 0;
	else if (keycode == 97)
		game->r_left = 0;
	else if (keycode == 100)
		game->r_right = 0;
	else if (keycode == 65307)
		game->exit = 0;
	return (0);
}
