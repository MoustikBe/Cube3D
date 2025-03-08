#ifndef CUBE_H
# define CUBE_H

// # --- Library --- # // 
# include <stdio.h>
# include <unistd.h> 
# include <stdlib.h>
# include <fcntl.h>
// # --- Library --- # // 

// # --- struct --- # //
typedef struct t_texture
{
	char	*NO;
	char	*SO;
	char	*EA;
	char	*WE;
	int		*F;
	int		*C;
	int		error;
}	t_texture;

typedef struct t_cube
{
	char	*file_map;
	char	**map;
	int		x_plr;
	int		y_plr;
	int		x_dir_plr;
	int		y_dir_plr;
	int		player;
}	t_cube;
// # --- struct --- # //

// # --- functions --- # //

// -- Graphics -- //
// - graph_main.c - //
void	display2d(t_cube *cube);

// -- Parsing -- //
// - pars_main.c - //
int		parsing(t_texture *skin, t_cube *cube, char **argv);
void	check_component(t_texture *skin);
// - pars_color.c - //
int		rgb_checker(int *nb);
void	set_fc_color(t_texture *skin, int **color, char *line);
// - pars_verif.c - //
int		verif_file(t_cube *c);
int		verif_line(char *line);
int		verif_map(t_cube *cube);
void	verif_info(t_texture *skin, t_cube *cube);
// - pars_storage.c - //
int		saving_data(t_cube *cube, char *line, int index);
void	set_skin(t_texture *skin, char **texture, char *line);
// - pars_algo.c - //
int		algo_wall(t_cube *cube);


// -- Utils -- //
// - utils.c - //
void	init_struct(t_texture *skin, t_cube *cube);
int		len_map(t_cube *cube);
int		len_array(char **map);
char	**copy_map(char **map);
void	free_struct(char **map);

// -- functions --//
#endif