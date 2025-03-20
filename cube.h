#ifndef CUBE_H
# define CUBE_H

// # --- Library --- # // 
# include <stdio.h>
# include <unistd.h> 
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
// # --- Library --- # // 

// # --- Macro --- # // 
#define PI 3.1415926

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

typedef struct s_img
{
    void    *img;
    int     *data;
    int     width;
    int     height;
    int     bpp;
    int     line_len;
    int     endian;
} t_img;



typedef struct t_game
{
	/* Display */
	int		width;
	int		height;
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
	char    *wall_texutre;
	t_img tex_N;
    t_img tex_S;
    t_img tex_E;
    t_img tex_W;
	t_img mini_map;

	int ceiling_color;
	int floor_color;

	int front;
	int back;
	int r_left;
	int r_right;
	int exit;

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

typedef struct t_ray
{
	int		screenWidth;
	int		screenHeight;
	float	FOV;
	int		x;
	int		y;
	float	ray_angle;
	int		mapX;
	int		mapY;
	int		side;
	int		stepX;
	int		stepY;
	float	perpWallDist;
	float	correctedDist;
	int		lineHeight;
	int		drawStart;
	int		drawEnd;
	float	rayDirX;
	float	rayDirY;
	float	wallX;
	int		textureX;
	int		d;
	int		textureY;
	int		color;
	/* Cast_ray */
	float posX;
	float posY;
	float rayDirX2;
	float rayDirY2;
	float deltaDistX;
	float deltaDistY;
	float sideDistX;
	float sideDistY;
	int hit;
}	t_ray;


// # --- struct --- # //

// # --- functions --- # //

// -- Graphics -- //
// - graph_main.c - //
void	graph_main(t_cube *cube, t_texture *skin);
// - graph_init.c - //
void	graph_init(t_game *game, t_cube *cube, t_texture *skin);
int		rgb_to_hex(int *rgb);
int		load_all_texture(t_texture *skin, t_game *game);
// - graph_gameplay.c - //
int		exit_game(t_game *game);
int		game_loop(t_game *game);
// - graph_moov.c - //
int		moov_front(t_game *game, float new_x, float new_y);
int		moov_back(t_game *game, float new_x, float new_y);
void	rotate_left(t_game *game);
void	rotate_right(t_game *game);
// - graph_key.c - //
int ft_key_press(int keycode, t_game *game);
int ft_key_release(int keycode, t_game *game);
// - graph_raycast.c - // 
void ray_tracer(t_game *game);
// - graph_ray_utils.c - //
t_img *texturing(t_ray *ray, t_game *game, t_img *texture);
void init_ray(t_ray *ray, t_game *game);
void init_cast_ray(t_ray *ray, t_game *game);
void	my_mlx_pixel_put3D(t_game *game, int x, int y, int color);


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