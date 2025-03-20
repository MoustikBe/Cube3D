/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:31:02 by misaac-c          #+#    #+#             */
/*   Updated: 2025/03/20 12:32:13 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cube.h"
#include "../../libs/libft/libft.h"

void	init_struct(t_texture *skin, t_cube *cube)
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
		if (verif_line(line))
			len++;
		free(line);
		line = get_next_line(fd_map);
	}
	close(fd_map);
	return (len);
}

int	len_array(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

char	**copy_map(char **map)
{
	char	**map_copy;
	int		i;

	map_copy = malloc(sizeof(char *) * (len_array(map) + 1));
	i = 0;
	while (map[i])
	{
		map_copy[i] = ft_strdup(map[i]);
		i++;
	}
	map_copy[i] = NULL;
	return (map_copy);
}

void	free_struct(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
	return ;
}
