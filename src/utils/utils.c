#include "../../cube.h"
#include "../libs/libft/libft.h"

void init_struct(t_texture *skin, t_cube *cube)
{
	skin->NO = NULL;
	skin->SO = NULL;
	skin->EA = NULL;
	skin->WE = NULL;
	skin->C = NULL;
	skin->F = NULL;
	skin->error = 0;
	cube->y_plr = 0;
	cube->x_plr = 0;
}
