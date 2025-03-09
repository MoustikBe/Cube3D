/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 20:14:24 by misaac-c          #+#    #+#             */
/*   Updated: 2025/03/09 17:47:28 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cube.h"
#include "../../libs/libft/libft.h"
#include "../../libs/minilibx-linux/mlx.h"


int	exit_game(t_game *game)
{
	mlx_destroy_window(game->mlx, game->wdw);
	free(game->mlx);
	exit(1);
}

void	searching_data(t_cube *cube, t_game *game)
{
	int x;
	int prev_x;
	int i;

	game->len_y = len_array(cube->map);
	i = 0;
	prev_x = ft_strlen(cube->map[i]);
	while (cube->map[i])
	{
		x = ft_strlen(cube->map[i]);
		if(x > prev_x)
			prev_x = x;
		i++;
	}
	game->len_x = prev_x;
	printf("len_x -> %d | len_y -> %d", game->len_x, game->len_y);
}


void put_texture(t_game *game, char **map)
{
	int i;
	int j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if(map[i][j] == '0')
				mlx_put_image_to_window(game->mlx, game->wdw, game->g_NO, j * 100, i * 100);
			else if(map[i][j] == '1')
				mlx_put_image_to_window(game->mlx, game->wdw, game->g_SO, j * 100, i * 100);
			else if(map[i][j] == 'N')
				mlx_put_image_to_window(game->mlx, game->wdw, game->g_EA, j * 100, i * 100);
			j++;
		}
		i++;
	}
	
}

int	mng_input(int keysym, t_game *game)
{
	return 0;	
}

void	graph_main(t_cube *cube, t_texture *skin, t_game *game)
{
	int		img_w;
	int		img_h;

	// Still need to define len_x et len_y //
	searching_data(cube, game);
	game->mlx = mlx_init();
	game->wdw = mlx_new_window(game->mlx, game->len_x * 100, game->len_y * 100, "cube3D");
	
	game->g_NO = mlx_xpm_file_to_image(game->mlx, skin->NO, &img_w, &img_h);
	game->g_SO = mlx_xpm_file_to_image(game->mlx, skin->SO, &img_w, &img_h);
	game->g_EA = mlx_xpm_file_to_image(game->mlx, skin->EA, &img_w, &img_h);
	game->g_WE = mlx_xpm_file_to_image(game->mlx, skin->WE, &img_w, &img_h);
	
	put_texture(game, cube->map);
	
	mlx_key_hook(game->wdw, mng_input, &game);
	mlx_hook(game->wdw, 17, 0, exit_game, &game);
	mlx_loop(game->mlx);
}
