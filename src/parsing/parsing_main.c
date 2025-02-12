/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:58:44 by misaac-c          #+#    #+#             */
/*   Updated: 2025/02/12 13:37:29 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube.h"
#include "../libs/libft/libft.h"

int	verif_file(t_cube *c)
{
	int	l;

	l = ft_strlen(c->file_map);
	if (l > 3)
	{
		if (c->file_map[l - 1] == 'b' && c->file_map[l - 2] == 'u'
			&& c->file_map[l - 3] == 'c' && c->file_map[l - 4] == '.')
		{
			if (open(c->file_map, R_OK))
				return(0);
			else
				return(ft_printf("Error\nFile not found or not readable\n"));
		}
	}
	return(ft_printf("Error\nBad file extension\n"));
}

void	set_no_skin(char *texture, char *line)
{
	// Verification necessaire. 
	// On doit verifier que la texture existe et si oui alors faire dup de la partie essentiel dans char *texture sans NO ou SO etc.
}


int verif_info(t_texture *skin, t_cube *cube)
{
	// regarder les info avec get_next_line, puis les sauvegarder. CAD NO SO EA WE C F
	char	*line;
	int		fd_map;

	fd_map = open(cube->file_map, R_OK);
	line = get_next_line(fd_map);
	while (line)
	{
		// regarder le contenus de la ligne et verifier si on voit une des info que l'on a besoin. 
		if (ft_strncmp("NO ", line, 3) == 0)
			set_no_skin(skin->NO, line);
		if (ft_strncmp("SO ", line, 3) == 0)
			set_no_skin(skin->SO, line);
		if (ft_strncmp("EA ", line, 3) == 0)
			set_no_skin(skin->EA, line);
		if (ft_strncmp("WE ", line, 3) == 0)
			set_no_skin(skin->WE, line);
		
		free(line);
		line = get_next_line(fd_map);
	}
	return(1);	
}

int	parsing(t_texture *skin, t_cube *cube, char **argv)
{
	cube->file_map = ft_strdup(argv[1]);
	if (verif_file(cube))
		return (1);
	if (verif_info(skin, cube))
		return (1);
	return (0);
}
