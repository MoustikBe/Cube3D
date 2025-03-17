#ifndef CUBE_H
# define CUBE_H

// # --- Library --- # // 
# include <stdio.h>
# include <unistd.h> 
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
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

typedef struct t_game
{
	/* Display */
	void	*mlx;
	void	*mlx3d;
	void	*wdw;
	void	*wdw3d;
	void	*img;
	void	*img3d;
	char	*addr;
	char	*addr3d;
    int     endian;
	int     line_length;
	int		bit_per_pixel;
	int     line_length3d;
	int		bit_per_pixel3d;
	int     endian3d;

	char **map;
	float	angle;
	float	speed;

	float px;
	float py;
	float pdx;
	float pdy;
	float pa;

	/* -- RAYCASTER -- */
	int		r;
	int		mx;
	int 	my;
	int 	mp;
	int 	dof;
	
	float	rx;
	float	ry;
	float	ra;
	float	xo;
	float	yo;
	/* RAYCASTER */
	
	int keys[256]; 
	/* Info */
	int		len_x;
	int		len_y;
	/* PAUSE */
	void 	*g_NO;
	void 	*g_SO;
	void 	*g_EA;
	void 	*g_WE;
	t_cube	*cube;
}	t_game;

// # --- struct --- # //

// # --- functions --- # //

// -- Graphics -- //
// - graph_main.c - //
void	graph_main(t_cube *cube, t_texture *skin);

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