/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 20:14:24 by misaac-c          #+#    #+#             */
/*   Updated: 2025/03/11 12:50:37 by misaac-c         ###   ########.fr       */
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
}

void my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
    if (x < 0 || y < 0 || x >= game->len_x * 100 || y >= game->len_y * 100)
        return; // Évite un accès mémoire hors limites

    char *dst = game->addr + (y * game->line_length + x * (game->bit_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void draw_square(t_game *game, int x, int y, int size, int color)
{
	int i;
	int j;

	i = 0;
	while(i < size)
	{
		j = 0;
		while (j < size)
		{
			my_mlx_pixel_put(game, x + i, y + j, color);	
			j++;
		}
		i++;	
	}
}

void draw_map(t_game *game, char **map)
{
	int i;
	int j;
	int cell_size = 100;
	int player_size = 10;
	int offset = (cell_size - player_size) / 2;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if(map[i][j] == '0')
			{
				//printf("drawing 0 -> %d\n", j * cell_size);
				draw_square(game, j * cell_size, i * cell_size, cell_size, 0x000000);
			}
			else if(map[i][j] == '1')
			{
				//printf("drawing 1 -> %d\n", i * cell_size);
				draw_square(game, j * cell_size - 5, i * cell_size - 5, cell_size - 5, 0xFFFFFF);
			}
			else if(map[i][j] == 'N')
			{
				draw_square(game, j * cell_size, i * cell_size, cell_size, 0x000000);
				game->player_x = (float)j;
				game->player_y = (float)i;
				draw_square(game, j * cell_size + offset, i * cell_size + offset, player_size, 0xFF0000);
			}
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->wdw, game->img, 0, 0);
}

int mng_input(int keysym, t_game *game, t_cube *cube)
{
	// Le joueur est compter comme si il était a 100% de la taille du block 
    int new_x;
    int new_y;
	int cell_size = 100;
	int player_size = 10;
	int offset = (cell_size - player_size) / 2;

    if (keysym == 65307) // Touche Échap -> Quitte 
    {
        if (game->mlx && game->wdw)
            mlx_destroy_window(game->mlx, game->wdw);
        free(game->mlx);
        exit(1);
    }
    else if (keysym == 119) // Touche W -> Avancer
    {
		printf("\ny -> %d | x -> %d\n", (int)game->player_y, (int)game->player_x);
		if(game->cube->map[(int)(game->player_y + 0.50)][(int)game->player_x] == '1')
			return(2);
        draw_square(game, game->player_x * cell_size + offset, game->player_y * cell_size + offset, player_size, 0x000000);
		game->player_y = game->player_y - 0.10;
		draw_square(game, game->player_x * cell_size + offset, game->player_y * cell_size + offset, player_size, 0xFF0000);
        mlx_put_image_to_window(game->mlx, game->wdw, game->img, 0, 0);
    }
	else if (keysym == 115) // Touche S -> Reculer
    {
        draw_square(game, game->player_x * cell_size + offset, game->player_y * cell_size + offset, player_size, 0x000000);
		game->player_y = game->player_y + 0.10;
		draw_square(game, game->player_x * cell_size + offset, game->player_y * cell_size + offset, player_size, 0xFF0000);
        mlx_put_image_to_window(game->mlx, game->wdw, game->img, 0, 0);
    }
	else if (keysym == 97) // Touche A -> Gauche
    {
		// Doit interferer avec l'angle ou nous les mouvements 
        draw_square(game, game->player_x * cell_size + offset, game->player_y * cell_size + offset, player_size, 0x000000);
		game->player_x = game->player_x - 0.10;
		draw_square(game, game->player_x * cell_size + offset, game->player_y * cell_size + offset, player_size, 0xFF0000);
        mlx_put_image_to_window(game->mlx, game->wdw, game->img, 0, 0);
    }
	else if (keysym == 100) // Touche D -> Droite
    {
		// Doit interferer avec l'angle ou nous les mouvements 
        draw_square(game, game->player_x * cell_size + offset, game->player_y * cell_size + offset, player_size, 0x000000);
		game->player_x = game->player_x + 0.10;
		draw_square(game, game->player_x * cell_size + offset, game->player_y * cell_size + offset, player_size, 0xFF0000);
        mlx_put_image_to_window(game->mlx, game->wdw, game->img, 0, 0);
    }
    return 0;
}


void	graph_main(t_cube *cube, t_texture *skin)
{
	t_game	game;
	int		img_w;
	int		img_h;

	game.cube = cube;
	// Still need to define len_x et len_y //
	searching_data(cube, &game);
	game.player_x = cube->x_plr;
	game.player_y = cube->y_plr;
	game.angle = 0;
	game.speed = 1.4;
		game.mlx = mlx_init();
	game.wdw = mlx_new_window(game.mlx, game.len_x * 100, game.len_y * 100, "cube3D");
	
	game.img = mlx_new_image(game.mlx, game.len_x * 100, game.len_y * 100);
	game.addr = mlx_get_data_addr(game.img, &game.bit_per_pixel, &game.line_length, &game.endian);
	
	/*
	game->g_NO = mlx_xpm_file_to_image(game->mlx, skin->NO, &img_w, &img_h);
	game->g_SO = mlx_xpm_file_to_image(game->mlx, skin->SO, &img_w, &img_h);
	game->g_EA = mlx_xpm_file_to_image(game->mlx, skin->EA, &img_w, &img_h);
	game->g_WE = mlx_xpm_file_to_image(game->mlx, skin->WE, &img_w, &img_h);
	*/

	draw_map(&game, cube->map);
	printf("\n y -> %f x-> %f\n", game.player_y, game.player_x);
	mlx_key_hook(game.wdw, mng_input, &game);
	mlx_hook(game.wdw, 17, 0, exit_game, &game);
	mlx_loop(game.mlx);
}
