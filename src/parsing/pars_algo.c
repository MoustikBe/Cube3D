/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_algo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 11:14:06 by misaac-c          #+#    #+#             */
/*   Updated: 2025/03/07 13:40:13 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube.h"
#include "../libs/libft/libft.h"

void	fill_algo(char **map, int y, int x, int *detect)
{
	if(!map[y])
	{
		*detect = 1;
		return ;
	}
	if (x < 0 || y < 0 || x >= ft_strlen(map[y]) || y > len_array(map) - 1)
	{
		*detect = 1;
		return ;
	}
	if (map[y][x] == '1')
		return ;
	if (map[y][x] == 'V')
		return ;
	map[y][x] = 'V';
	fill_algo(map, y +1, x, detect);
	fill_algo(map, y -1, x, detect);
	fill_algo(map, y, x +1, detect);
	fill_algo(map, y, x -1, detect);
}

void free_struct(char **map)
{
	int i;

	i = 0;
	while(map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
	return ;
}

int algo_wall(t_cube *cube)
{
	int detect = 0;
	char **map_copy;
	
	map_copy = copy_map(cube->map);
	fill_algo(map_copy, cube->y_plr, cube->x_plr, &detect);
	if(detect)
		return(free_struct(map_copy) ,printf("Error, map not closed\n"));
	return(free_struct(map_copy) ,0);
}
