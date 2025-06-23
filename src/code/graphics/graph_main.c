/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 20:14:24 by misaac-c          #+#    #+#             */
/*   Updated: 2025/03/24 11:19:54 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cube.h"
#include "../../libs/libft/libft.h"
#include "../../libs/minilibx-linux/mlx.h"

void	graph_main(t_cube *cube, t_texture *skin)
{
	t_game	game;

	graph_init(&game, cube, skin); //inits game struct, converts rgb to hexadecimal colors, step size and inits mlx
	if (load_all_texture(skin, &game)) //loads textures
		return ;
	ray_tracer(&game); //draws the walls
	mlx_hook(game.wdw3d, 17, 0, exit_game, &game); //if you press the cross in the window (event 17), exit game
	mlx_hook(game.wdw3d, 2, 1L << 0, ft_key_press, &game); //if a key is pressed (event 2)
	mlx_loop_hook(game.mlx3d, game_loop, &game); //runs game_loop every frame to draw the map
	mlx_hook(game.wdw3d, 3, 1L << 1, ft_key_release, &game); //if a key is released (event 3)
	mlx_loop(game.mlx3d); //listens to events
}
