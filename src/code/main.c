/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:27:51 by misaac-c          #+#    #+#             */
/*   Updated: 2025/03/20 12:30:47 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube.h"
#include "../libs/libft/libft.h"

int	main(int argc, char **argv)
{
	t_texture	*skin;
	t_cube		*cube;
	t_game		*game;

	if (argc != 2)
		return (ft_printf("Error\nOnly one argument is accepted !\n"));
	skin = malloc(sizeof(t_texture));
	cube = malloc(sizeof(t_cube));
	game = malloc(sizeof(t_game));
	init_struct(skin, cube);
	if (parsing(skin, cube, argv))
		return (1);
	game->map = copy_map(cube->map);
	graph_main(cube, skin);
	return (free(cube), free(skin), free(game), 0);
}
