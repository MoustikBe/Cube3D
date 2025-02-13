#include "cube.h"
#include "src/libs/libft/libft.h"


int main(int argc, char **argv)
{
	t_texture *skin;
	t_cube *cube;

	if (argc != 2)
		return(ft_printf("Error\nOnly one argument is accepted !\n"));
	skin = malloc(sizeof(t_texture));
	cube = malloc(sizeof(t_cube));
	init_struct(skin);
	if(parsing(skin, cube, argv))
		return(1);
	return(free(cube), free(skin), 0);
}
