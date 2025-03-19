/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 20:14:24 by misaac-c          #+#    #+#             */
/*   Updated: 2025/03/19 12:36:53 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cube.h"
#include "../../libs/libft/libft.h"
#include "../../libs/minilibx-linux/mlx.h"

#define PI 3.1415926


int rgb_to_hex(int *rgb)
{
    return ((rgb[0] & 0xFF) << 16) | ((rgb[1] & 0xFF) << 8) | (rgb[2] & 0xFF);
}

int	exit_game(t_game *game)
{
		mlx_destroy_window(game->mlx3d, game->wdw3d);
		free(game->mlx3d);
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

void my_mlx_pixel_put3D(t_game *game, int x, int y, int color)
{
    if (x < 0 || y < 0 || x >= game->width / 2.5 || y >= game->height / 2)
        return; // Évite un accès mémoire hors limites

    char *dst = game->addr3d + (y * game->line_length3d + x * (game->bit_per_pixel3d / 8));
    *(unsigned int*)dst = color;
}

float cast_ray(t_game *game, float ray_angle,
               int *mapX, int *mapY, int *side,
               int *out_stepX, int *out_stepY)
{
    float posX = game->px;
    float posY = game->py;
    float rayDirX = cos(ray_angle);
    float rayDirY = sin(ray_angle);

    *mapX = (int)posX;
    *mapY = (int)posY;

    float deltaDistX = (rayDirX == 0) ? 1e30f : fabs(1.0f / rayDirX);
    float deltaDistY = (rayDirY == 0) ? 1e30f : fabs(1.0f / rayDirY);

    *out_stepX = (rayDirX < 0) ? -1 : 1;
    *out_stepY = (rayDirY < 0) ? -1 : 1;

    float sideDistX = (rayDirX < 0)
        ? (posX - *mapX) * deltaDistX
        : (*mapX + 1.0f - posX) * deltaDistX;

    float sideDistY = (rayDirY < 0)
        ? (posY - *mapY) * deltaDistY
        : (*mapY + 1.0f - posY) * deltaDistY;

    int hit = 0;
    *side = 0;

    while (!hit)
    {
        if (sideDistX < sideDistY)
        {
            sideDistX += deltaDistX;
            *mapX += *out_stepX;
            *side = 0; // mur vertical
        }
        else
        {
            sideDistY += deltaDistY;
            *mapY += *out_stepY;
            *side = 1; // mur horizontal
        }
        if (game->cube->map[*mapY][*mapX] == '1')
            hit = 1;
    }

    float perpWallDist;
    if (*side == 0)
        perpWallDist = (*mapX - posX + (1 - *out_stepX) / 2.0f) / rayDirX;
    else
        perpWallDist = (*mapY - posY + (1 - *out_stepY) / 2.0f) / rayDirY;

    return perpWallDist;
}



// Fonction de raytracing qui dessine l'image 3D avec des textures différentes selon la face
void ray_tracer(t_game *game)
{
    // Définir la taille du rendu 3D
    int screenWidth = game->width / 2.5;  // Par exemple
    int screenHeight = game->height / 2;  // Par exemple
    float FOV = 60.0f * (PI / 180.0f);

	// Intialisation pour remplacements massif des boucles for // 
	int x;
	int y;

	x = 0;
    // Pour chaque colonne de l'écran
    while (x < screenWidth)
    {
        float ray_angle = game->pa - (FOV / 2.0f) + ((float)x / (float)screenWidth) * FOV;

        int mapX, mapY, side;
        int stepX, stepY;
        float perpWallDist = cast_ray(game, ray_angle, &mapX, &mapY, &side, &stepX, &stepY);

        // Correction fish-eye
        float correctedDist = perpWallDist * cos(ray_angle - game->pa);
        if (correctedDist < 0.1f)
            correctedDist = 0.1f;

        int lineHeight = (int)(screenHeight / correctedDist);
        int drawStart = -lineHeight / 2 + screenHeight / 2;
        if (drawStart < 0)
            drawStart = 0;
        int drawEnd = lineHeight / 2 + screenHeight / 2;
        if (drawEnd >= screenHeight)
            drawEnd = screenHeight - 1;

        // Dessin du plafond pour la colonne x
        y = 0;
		while (y < drawStart)
        {
            my_mlx_pixel_put3D(game, x, y, game->ceiling_color);
			y++;
        }

        // Sélection de la texture pour le mur en fonction de la face
        t_img *texture;
        float rayDirX = cos(ray_angle);
        float rayDirY = sin(ray_angle);
        if (side == 0)
        {
            if (stepX > 0)
                texture = &game->tex_E;
            else
                texture = &game->tex_W;
        }
        else
        {
            if (stepY > 0)
                texture = &game->tex_S;
            else
                texture = &game->tex_N;
        }

        // Calcul de wallX (position fractionnaire sur la case)
        float wallX;
        if (side == 0)
            wallX = game->py + perpWallDist * rayDirY;
        else
            wallX = game->px + perpWallDist * rayDirX;
        wallX -= floor(wallX);

        int textureX = (int)(wallX * (float)texture->width);
        if ((side == 0 && rayDirX > 0) || (side == 1 && rayDirY < 0))
            textureX = texture->width - textureX - 1;

        // Dessin du mur pour la colonne x
        y = drawStart;
		while (y < drawEnd)
        {
            int d = (y - (screenHeight / 2) + (lineHeight / 2));
            int textureY = (d * texture->height) / lineHeight;
            int color = texture->data[textureY * texture->width + textureX];
            my_mlx_pixel_put3D(game, x, y, color);
			y++;
        }

        // Dessin du sol pour la colonne x
        y = drawEnd; 
		while (y < screenHeight)
        {
            my_mlx_pixel_put3D(game, x, y, game->floor_color);
			y++;
        }
		x++;
    }

    mlx_put_image_to_window(game->mlx3d, game->wdw3d, game->img3d, 0, 0);
}



// Fonction qui lance un rayon selon un angle donné et renvoie la distance perpendiculaire au mur
// game->px et game->py représentent la position du joueur en coordonnées de grille (float)
// game->cube->map est un tableau de chaînes, où '1' indique un mur


int mng_input(int keysym, t_game *game, t_cube *cube)
{
    float new_x = 0;
    float new_y = 0;
	int cell_size = 20;
	int player_size = 2;
	int offset = (cell_size - player_size) / 2;

    if (game->exit)
    {
		mlx_destroy_window(game->mlx3d, game->wdw3d);
        free(game->mlx3d);
        exit(1);
    }
    if (game->front) // Touche W -> Avancer //
    {
		new_x = game->px + game->pdx;
		new_y = game->py + game->pdy;
		if(game->cube->map[(int)(new_y)][(int)(new_x)] == '1')
		{
			//printf("X direction -> %f | Y direction -> %f \n", game->pdx, game->pdy);
			return(2);
        }
		else
		{
			game->px = new_x;
			game->py = new_y;
			ray_tracer(game);
		}
    }
	if (game->back) // Touche S -> Reculer //
    {
		
		new_x = game->px - game->pdx;
		new_y = game->py - game->pdy;
		if(game->cube->map[(int)(new_y)][(int)(new_x)] == '1')
			return(2);
		else
		{
			game->px = new_x;
			game->py = new_y;
			ray_tracer(game);
		}
	}
	if (game->r_left) // Touche A -> Gauche
    {
		game->pa -= 0.1;
		if(game->pa < 0)
			game->pa += 2*PI;
		game->pdx = cos(game->pa) * 0.05;
		game->pdy = sin(game->pa) * 0.05;
		ray_tracer(game);
    }
	if (game->r_right) // Touche D -> Droite
    {
		game->pa += 0.1;
		if(game->pa > 2*PI)
			game->pa -= 2*PI;
		game->pdx = cos(game->pa) * 0.05;
		game->pdy = sin(game->pa) * 0.05;
		ray_tracer(game);
    }
    return 0;
}

int load_texture(t_game *game, t_img *tex, char *path)
{
    tex->img = mlx_xpm_file_to_image(game->mlx3d, path, &tex->width, &tex->height);
    if (!tex->img)
        return (printf("Error loading wall texture: %s\n", path), 1);
    tex->data = (int *)mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_len, &tex->endian);
    return 0;
}


int load_all_texture(t_texture *skin, t_game *game)
{
	if(load_texture(game, &game->tex_N, skin->NO))
		return(ft_printf("Error loading the North texture, verify the path pls\n"));
	if(load_texture(game, &game->tex_S, skin->SO))
		return(ft_printf("Error loading the South texture, verify the path pls\n"));
	if(load_texture(game, &game->tex_E, skin->EA))
		return(ft_printf("Error loading the East texture, verify the path pls\n"));
	if(load_texture(game, &game->tex_W, skin->WE))
		return(ft_printf("Error loading the West texture, verify the path pls\n"));
	return(0);
}

int ft_key_press(int keycode, t_game *game)
{
	if(keycode == 119)
		game->front = 1;
	else if(keycode == 115)
		game->back = 1;
	else if(keycode == 97)
		game->r_left = 1;
	else if(keycode == 100)
		game->r_right = 1;
	else if(keycode == 65307)
		game->exit = 1;
}
int ft_key_release(int keycode, t_game *game)
{
	if(keycode == 119)
		game->front = 0;
	else if(keycode == 115)
		game->back = 0;
	else if(keycode == 97)
		game->r_left = 0;
	else if(keycode == 100)
		game->r_right = 0;
	else if(keycode == 65307)
		game->exit = 0;
}

int game_loop(t_game *game)
{
	if(game->front || game->back || game->r_left || game->r_right || game->exit)
		mng_input(0,game,game->cube);
	return(0);
}

void	graph_main(t_cube *cube, t_texture *skin)
{
	t_game	game;

	graph_init(&game, cube, skin);
	if (load_all_texture(skin, &game))
	    return ;
	ray_tracer(&game);
	mlx_hook(game.wdw3d, 17, 0, exit_game, &game);
	mlx_hook(game.wdw3d, 2, 1L << 0, ft_key_press, &game);
	mlx_loop_hook(game.mlx3d, game_loop, &game);
	mlx_hook(game.wdw3d, 3, 1L << 1, ft_key_release, &game);
	mlx_loop(game.mlx3d);
}
