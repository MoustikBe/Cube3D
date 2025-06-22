/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:27:51 by misaac-c          #+#    #+#             */
/*   Updated: 2025/03/20 12:48:50 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube.h"
#include "../libs/libft/libft.h"

int	main(int argc, char **argv)
{
	t_texture	*skin; //contains all textures and floor/ceiling colors + error
	t_cube		*cube; //contains player position and direction coordinates
	t_game		*game; //mlx struct

	if (argc != 2)
		return (ft_printf("Error\nOnly one argument is accepted !\n"));
	skin = malloc(sizeof(t_texture));
	cube = malloc(sizeof(t_cube));
	game = malloc(sizeof(t_game));
	init_struct(skin, cube);
	if (parsing(skin, cube, argv)) //verifies file extension .cub, map header, player's presence and map enclosed by walls
		return (1);
	game->map = copy_map(cube->map); //creates a copy of the map to change the player's position without affecting the real original map
	graph_main(cube, skin);
	return (free(cube), free(skin), free(game), 0); //free the structs
}
