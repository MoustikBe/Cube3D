#ifndef CUBE_H
# define CUBE_H

// -- Library -- // 
# include <stdio.h>
# include <unistd.h> 
# include <stdlib.h>
# include <fcntl.h>
// -- Library -- // 

// -- struct --//
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
	char *file_map;
}	t_cube;
// -- struct --//

// -- functions --//
int parsing(t_texture *skin, t_cube *cube, char **argv);
void init_struct(t_texture *skin);

// -- functions --//
#endif