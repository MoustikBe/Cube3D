/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:31:42 by misaac-c          #+#    #+#             */
/*   Updated: 2025/03/19 12:49:24 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cube.h"
#include "../../libs/libft/libft.h"
#include "../../libs/minilibx-linux/mlx.h"

static void init_player_rotation(t_game *game, t_cube *cube)
{
	if(cube->player == 'E')
		game->pa = 0;
	else if(cube->player == 'S')
		game->pa = 1.55;
	else if(cube->player == 'W')
		game->pa = 3.10;
	else if(cube->player == 'N')
		game->pa = 4.65;
	return ;
}

void graph_init(t_game *game, t_cube *cube, t_texture *skin)
{
	game->front = 0;
	game->back = 0;
	game->r_left = 0;
	game->r_right = 0;
	game->exit = 0;
	game->floor_color = rgb_to_hex(skin->F);
	game->ceiling_color = rgb_to_hex(skin->C);
	init_player_rotation(game, cube);
	game->pdx = cos(game->pa) * 0.05;
	game->pdy = sin(game->pa) * 0.05;
	game->cube = cube;
	searching_data(cube, game);
	game->px = cube->x_plr;
	game->py = cube->y_plr;
	game->angle = 0;
	game->speed = 1.4;
	game->mlx3d = mlx_init();
	mlx_get_screen_size(game->mlx3d, &game->width, &game->height);
	game->wdw3d = mlx_new_window(game->mlx3d, game->width / 2.5, game->height / 2, "cube3D");
	game->img3d = mlx_new_image(game->mlx3d, game->width / 2.5, game->height / 2);
	game->addr3d = mlx_get_data_addr(game->img3d, &game->bit_per_pixel3d, &game->line_length3d, &game->endian3d);
}
