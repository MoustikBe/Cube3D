/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 20:14:24 by misaac-c          #+#    #+#             */
/*   Updated: 2025/03/13 13:44:18 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cube.h"
#include "../../libs/libft/libft.h"
#include "../../libs/minilibx-linux/mlx.h"

#define PI 3.1415926



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
				draw_square(game, j * cell_size, i * cell_size, cell_size, 0xFFFFFF);
			}
			else if(map[i][j] == 'N')
			{
				draw_square(game, j * cell_size, i * cell_size, cell_size, 0x000000);
				game->px = (float)j;
				game->py = (float)i;
				draw_square(game, j * cell_size, i * cell_size, player_size, 0xFF0000);
			}
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->wdw, game->img, 0, 0);
}

void draw_line_negatif(t_game *game)
{
	// Ce qu'on fait ici c'est avance h24 de 10 alors on fait sa pour la ligne
	float x = game->px;
	float y = game->py;
	int cell_size = 100;
	int offset = (cell_size - 10) / 2;
	int i = 0;

	while (i < 6)
	{
		x -= game->pdx;
		y -= game->pdy;
		draw_square(game, x * cell_size + offset, y * cell_size + offset, 5, 0xFF0000);
		i++;
	}
}

void draw_line_positif(t_game *game)
{
	// Ce qu'on fait ici c'est avance h24 de 10 alors on fait sa pour la ligne
	float x = game->px;
	float y = game->py;
	int cell_size = 100;
	int offset = (cell_size - 10) / 2;
	int i = 0;

	while (i < 6)
	{
		x += game->pdx;
		y += game->pdy;
		draw_square(game, x * cell_size + offset, y * cell_size + offset, 100, 0xFF0000);
		i++;
	}
}

void clean_line(t_game *game)
{
	// Ce qu'on fait ici c'est avance h24 de 10 alors on fait sa pour la ligne
	float x = game->px;
	float y = game->py;
	int cell_size = 100;
	int offset = (cell_size - 10) / 2;
	int i = 0;

	while (i < 6)
	{
		x += game->pdx;
		y += game->pdy;
		draw_square(game, x * cell_size + offset, y * cell_size + offset, 5, 0x000000);
		i++;
	}
}

void ray_tracer(t_game *game)
{
    // On part du même angle que celui du joueur
    game->ra = game->pa;
    float ray_step = 0.01;  // Incrément de déplacement (à ajuster selon la précision désirée)
    float distance = 0;
    float rx = game->px;    // Position x du rayon (en coordonnées de la grille)
    float ry = game->py;    // Position y du rayon

    // On avance le rayon tant qu'on ne dépasse pas une distance maximale (pour éviter une boucle infinie)
    while (distance < 1000)
    {
        int mapX = (int)rx;
        int mapY = (int)ry;
		printf("############\ncube[%d][%d] -> %c\n", (int)(game->py), (int)(game->px), game->cube->map[(int)(game->py)][(int)(game->px)]);
		printf("-----------\nmap -> X %d | map -> Y %d\n", mapX, mapY);
        
        // Vérifier que le rayon reste dans les limites de la carte
        if (mapY < 0 || mapY >= game->len_y || mapX < 0 || mapX >= (int)ft_strlen(game->cube->map[mapY]))
        {
            printf("Ray hors limites après %f unités.\n", distance);
            return;
        }
        
        // Si le rayon touche un mur ('1' dans la carte)
        if (game->cube->map[mapY][mapX] == '1')
        {
            printf("Ray a touché un mur à une distance de %f unités.\n", distance);
            return;
        }
        
        // Avancer le rayon le long de sa direction
        rx += cos(game->ra) * ray_step;
        ry += sin(game->ra) * ray_step;
        distance += ray_step;
    }
    
    // Si aucun mur n'est détecté dans la distance maximale
    printf("Aucun mur détecté dans un rayon de %f unités.\n", distance);
}

int mng_input(int keysym, t_game *game, t_cube *cube)
{
    int new_x;
    int new_y;
	int cell_size = 100;
	int player_size = 10;
	int offset = (cell_size - player_size) / 2;

    if (keysym == 65307) // Touche Échap -> Quitte //
    {
        if (game->mlx && game->wdw)
            mlx_destroy_window(game->mlx, game->wdw);
        free(game->mlx);
        exit(1);
    }
    else if (keysym == 119) // Touche W -> Avancer //
    {
		//clean_line(game);
		/*
		if(game->cube->map[(int)(game->py + 0.40)][(int)(game->px + 0.60)] == '1')
		{
			//printf("X direction -> %f | Y direction -> %f \n", game->pdx, game->pdy);
			return(2);
        }
		*/
		draw_square(game, game->px * cell_size, game->py * cell_size, player_size, 0x000000);
		game->px += game->pdx;
		game->py += game->pdy;
		//draw_line_positif(game);
		draw_square(game, game->px * cell_size, game->py * cell_size, player_size, 0xFF0000);
        mlx_put_image_to_window(game->mlx, game->wdw, game->img, 0, 0);
    }
	else if (keysym == 115) // Touche S -> Reculer //
    {
		//clean_line(game);
		/*
		if(game->cube->map[(int)(game->py + 0.70)][(int)(game->px + 0.60)] == '1')
			return(2);
        */
		draw_square(game, game->px * cell_size, game->py * cell_size, player_size, 0x000000);
		game->px -= game->pdx;
		game->py -= game->pdy;
		draw_square(game, game->px * cell_size, game->py * cell_size, player_size, 0xFF0000);
        mlx_put_image_to_window(game->mlx, game->wdw, game->img, 0, 0);
    }
	else if (keysym == 97) // Touche A -> Gauche
    {
		//clean_line(game); 
        draw_square(game, game->px * cell_size, game->py * cell_size, player_size, 0x000000);
		game->pa -= 0.1;
		if(game->pa < 0)
			game->pa += 2*PI;
		game->pdx = cos(game->pa) * 0.10;
		game->pdy = sin(game->pa) * 0.10;
		//draw_line_positif(game);
		draw_square(game, game->px * cell_size, game->py * cell_size, player_size, 0xFF0000);
        mlx_put_image_to_window(game->mlx, game->wdw, game->img, 0, 0);
    }
	else if (keysym == 100) // Touche D -> Droite
    {
		//clean_line(game);
        draw_square(game, game->px * cell_size, game->py * cell_size, player_size, 0x000000);
		
		game->pa += 0.1;
		if(game->pa > 2*PI)
			game->pa -= 2*PI;
		game->pdx = cos(game->pa) * 0.10;
		game->pdy = sin(game->pa) * 0.10;
		//draw_line_positif(game);
		draw_square(game, game->px * cell_size, game->py * cell_size, player_size, 0xFF0000);
        mlx_put_image_to_window(game->mlx, game->wdw, game->img, 0, 0);
    }
	ray_tracer(game);
    return 0;
}



void	graph_main(t_cube *cube, t_texture *skin)
{
	t_game	game;
	int		img_w;
	int		img_h;

	game.pdx = cos(game.pa) * 0.10;
	game.pdy = sin(game.pa) * 0.10;
	game.cube = cube;
	// Still need to define len_x et len_y //
	searching_data(cube, &game);
	game.px = cube->x_plr;
	game.py = cube->y_plr;
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
	ray_tracer(&game);
	draw_map(&game, cube->map);
	printf("\n y -> %f x-> %f\n", game.py, game.px);
	//mlx_key_hook(game.wdw, mng_input, &game);
	mlx_hook(game.wdw, 2, 1L << 0, mng_input, &game);
	mlx_hook(game.wdw, 17, 0, exit_game, &game);
	mlx_loop(game.mlx);
}
