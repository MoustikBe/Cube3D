#include "../../cube.h"
#include "../libs/libft/libft.h"


void 	print_map(t_cube *cube)
{
	int i = 0;

	while (cube->map[i])
	{
		ft_printf("map[%d] -> %s", i, cube->map[i]);
		i++;
	}
	ft_printf("\npos->x %d\npos->y %d\npos->x_dir %d\npos->y_dir %d\n", cube->x_plr, cube->y_plr, cube->x_dir_plr, cube->y_dir_plr);

}

int main(int argc, char **argv)
{
	t_texture *skin;
	t_cube *cube;

	if (argc != 2)
		return(ft_printf("Error\nOnly one argument is accepted !\n"));
	skin = malloc(sizeof(t_texture));
	cube = malloc(sizeof(t_cube));
	init_struct(skin, cube);
	if(parsing(skin, cube, argv))
		return(1);
	
	ft_printf(">> SUCCESS !\n");
	print_map(cube);
	graph_main(cube);

	return(free(cube), free(skin), 0);
}
