/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_verif.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:57:15 by misaac-c          #+#    #+#             */
/*   Updated: 2025/03/05 13:01:51 by misaac-c         ###   ########.fr       */
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

void verif_info(t_texture *skin, t_cube *cube)
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
			set_skin(skin, &skin->NO, line);
		if (ft_strncmp("SO ", line, 3) == 0)
			set_skin(skin, &skin->SO, line);
		if (ft_strncmp("EA ", line, 3) == 0)
			set_skin(skin, &skin->EA, line);
		if (ft_strncmp("WE ", line, 3) == 0)
			set_skin(skin, &skin->WE, line);
		if (ft_strncmp("C ", line, 2) == 0)
			set_fc_color(skin, &skin->C, line);
		if (ft_strncmp("F ", line, 2) == 0)
			set_fc_color(skin, &skin->F, line);
		free(line);
		line = get_next_line(fd_map);
	}
	check_component(skin);
	close(fd_map);
}

int verif_line(char *line)
{
	int i = 0;
	
	while (line[i] == '\v' || line[i] == '\t' || line[i] == ' ' || line[i] == '1' || line[i] == '0' || line[i] == 'N' || line[i] == 'E' || line[i] == 'W' || line[i] == 'S')
	{
		if(!line[i + 1] || line[i + 1] == '\n')
			return(1); // Ligne avec seuelemt 1 0 N E W S, mais pas le plus otpi assez brouillon et moche. //
		i++;
	}
	return(0);
}

int verif_map(t_cube *cube)
{
	char	*line;
	int		fd_map;
	int		index;

	index = 0;
	cube->map = malloc(sizeof(char *) * (len_map(cube) + 1));
	fd_map = open(cube->file_map, R_OK);
	line = get_next_line(fd_map);
	while (line)
	{
		if(verif_line(line))
		{
			//Possible probleme dans le cas d'une ligne vide pour faire la map |1111\n||    \n||1111| //
			if(saving_data(cube, line, index))
			{
				free(line);
				return(1);
			}
			index++;
			free(line);
			line = get_next_line(fd_map);
		}
		else if(!ft_strncmp("NO ", line, 3) || !ft_strncmp("EA ", line, 3) || !ft_strncmp("WE ", line, 3) || !ft_strncmp("SO ", line, 3) || ft_strncmp("F ", line, 2) == 0 || ft_strncmp("C ", line, 2) == 0 || line[0] == '\n')
		{
			free(line);
			line = get_next_line(fd_map);
		}
		else
		{
			free(line);
			return(ft_printf("Error bad config file\n"));
		}
	}
	close(fd_map);
	cube->map[index] = NULL;
	if(!cube->x_plr && !cube->y_plr)
		return(ft_printf("Error no player location found\n"));
	return(0);
}
