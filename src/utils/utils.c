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

int	len_map(t_cube *cube)
{
	char	*line;
	int		fd_map;
	int		len;

	len = 0;
	fd_map = open(cube->file_map, R_OK);
	line = get_next_line(fd_map);
	while (line)
	{
		if(verif_line(line))
			len++;
		free(line);
		line = get_next_line(fd_map);
	}
	close(fd_map);
	return(len);
}
