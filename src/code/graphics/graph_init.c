/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:31:42 by misaac-c          #+#    #+#             */
/*   Updated: 2025/03/25 11:57:09 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cube.h"
#include "../../libs/libft/libft.h"
#include "../../libs/minilibx-linux/mlx.h"

int	load_texture(t_game *game, t_img *tex, char *path) //loads texture
{
	tex->img = mlx_xpm_file_to_image(game->mlx3d, //converts from xpm file to image
			path, &tex->width, &tex->height);
	if (!tex->img)
		return (ft_printf("Error loading wall texture: %s\n", path), 1);
	tex->data = (int *)mlx_get_data_addr(tex->img,
			&tex->bpp, &tex->line_len, &tex->endian);
	return (0);
}

int	load_all_texture(t_texture *skin, t_game *game) //loads textures
{
	if (load_texture(game, &game->tex_n, skin->no)) //loads texture
		return (ft_printf(
				"Error loading the North texture, verify the path please\n"));
	if (load_texture(game, &game->tex_s, skin->so))
		return (ft_printf(
				"Error loading the South texture, verify the path please\n"));
	if (load_texture(game, &game->tex_e, skin->ea))
		return (ft_printf(
				"Error loading the East texture, verify the path please\n"));
	if (load_texture(game, &game->tex_w, skin->we))
		return (ft_printf(
				"Error loading the West texture, verify the path please\n"));
	return (0);
}

int	rgb_to_hex(int *rgb) //combines the color values into a single hex_value, int[0] is red, [1] is green and [2] is blue
{
	return (((rgb[0] & 0xFF) << 16) | ((rgb[1] & 0xFF) << 8) | (rgb[2] & 0xFF)); //0xFF is a mask 11111111. combines the values to create a single value 0xFF0000 | 0x00A500 | 0x000000 = 0xFFA500
}

static void	init_player_rotation(t_game *game, t_cube *cube) //sets the angle based on the direction. in c we use radians, not angles
{
	if (cube->player_letter == 'E')
		game->pa = 0; //right 0
	else if (cube->player_letter == 'S')
		game->pa = 1.55; //south 90ª
	else if (cube->player_letter == 'W')
		game->pa = 3.10; //left 180º
	else if (cube->player_letter == 'N')
		game->pa = 4.71; //north 270º
	return ;
}

void	graph_init(t_game *game, t_cube *cube, t_texture *skin) //inits game struct, converts rgb to hexadecimal colors, step size and inits mlx
{
	game->front = 0;
	game->back = 0;
	game->left = 0;
	game->right = 0;
	game->r_left = 0;
	game->r_right = 0;
	game->exit = 0;
	game->floor_color = rgb_to_hex(skin->f); //converts the int rgb colors to hexadecimal 0xRRGGBB
	game->ceiling_color = rgb_to_hex(skin->c); 
	init_player_rotation(game, cube); //sets the angle based on the direction. in c we use radians, not angles
	game->pdx = cos(game->pa) * 0.05; //0.05 is the step size (it's small to make it smoother) and pa is the player's angle, pdx is the direction vector (more on this on code explained in my notion)
	game->pdy = sin(game->pa) * 0.05;
	game->cube = cube;
	game->px = cube->x_plr; //player x position
	game->py = cube->y_plr; //player y position
	game->mlx3d = mlx_init(); //inits mlx
	mlx_get_screen_size(game->mlx3d, &game->width, &game->height); //gets screen_size
	game->wdw3d = mlx_new_window(game->mlx3d, //create a window named cub3D
			game->width / 2.5, game->height / 2, "cub3D"); //correct window name in graph_init
	game->img3d = mlx_new_image(game->mlx3d, // we draw an image offscreen instead of pixel by pixel
			game->width / 2.5, game->height / 2); //makes it half as big aprox as the full screen /2
	game->addr3d = mlx_get_data_addr(game->img3d,
			&game->bit_per_pixel3d, &game->line_length3d, &game->endian3d);
}
