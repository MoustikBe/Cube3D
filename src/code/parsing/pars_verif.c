/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_verif.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:57:15 by misaac-c          #+#    #+#             */
/*   Updated: 2025/06/23 16:36:24 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cube.h"
#include "../../libs/libft/libft.h"

int	verif_file(t_cube *c)
{
	int	l;

	l = ft_strlen(c->file_map);
	if (l > 3)
	{
		if (c->file_map[l - 1] == 'b' && c->file_map[l - 2] == 'u'
			&& c->file_map[l - 3] == 'c' && c->file_map[l - 4] == '.')
		{
			if (open(c->file_map, O_RDONLY))
				return (0);
			else
				return (ft_printf("Error\nFile not found or not readable\n"));
		}
	}
	return (ft_printf("Error\nBad file extension\n"));
}

void	verif_info(t_texture *skin, t_cube *cube)
{
	char	*line;
	int		fd_map;

	fd_map = open(cube->file_map, O_RDONLY);
	line = get_next_line(fd_map);
	while (line)
	{
		if (ft_strncmp("NO ", line, 3) == 0)
			set_skin(skin, &skin->no, line);
		if (ft_strncmp("SO ", line, 3) == 0)
			set_skin(skin, &skin->so, line);
		if (ft_strncmp("EA ", line, 3) == 0)
			set_skin(skin, &skin->ea, line);
		if (ft_strncmp("WE ", line, 3) == 0)
			set_skin(skin, &skin->we, line);
		if (ft_strncmp("C ", line, 2) == 0)
			set_fc_color(skin, &skin->c, line);
		if (ft_strncmp("F ", line, 2) == 0)
			set_fc_color(skin, &skin->f, line);
		free(line);
		line = get_next_line(fd_map);
	}
	check_component(skin);
	close(fd_map);
}

int	verif_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] == '\v' || line[i] == '\t' || line[i] == ' '
		|| line[i] == '1' || line[i] == '0' || line[i] == 'N'
		|| line[i] == 'E' || line[i] == 'W' || line[i] == 'S')
	{
		if (!line[i + 1] || line[i + 1] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int	cross_line(t_cube *cube, int fd_map, int *index)
{
	char	*line;
	int		d_index;

	d_index = 0;
	line = get_next_line(fd_map);
	while (line)
	{
		if (verif_line(line))
		{
			if (saving_data(cube, line, d_index))
			{
				free(line);
				return (1);
			}
			d_index++;
		}
		else if (!big_condition(line))
			return (free(line), ft_printf("Error bad config file\n"));
		else if (line[0] == '\n')
			empty_line_scenario(cube);
		free(line);
		line = get_next_line(fd_map);
	}
	*index = d_index;
	return (0);
}

int	verif_map(t_cube *cube)
{
	int		fd_map;
	int		index;

	index = 0;
	cube->map = malloc(sizeof(char *) * (len_map(cube) + 1));
	fd_map = open(cube->file_map, O_RDONLY);
	if (cross_line(cube, fd_map, &index))
		return (1);
	close(fd_map);
	cube->map[index] = NULL;
	if (!cube->x_plr && !cube->y_plr)
		return (ft_printf("Error no player location found\n"));
	return (0);
}
