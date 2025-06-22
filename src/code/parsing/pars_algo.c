/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_algo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 11:14:06 by misaac-c          #+#    #+#             */
/*   Updated: 2025/06/16 19:28:54 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cube.h"
#include "../../libs/libft/libft.h"

void	fill_algo(char **map, int y, int x, int *detect)
{
	if (!map[y])
	{
		*detect = 1;
		return ;
	}
	if (x < 0 || y < 0 || x >= (int)ft_strlen(map[y]) || y > len_array(map) - 1)
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


int	algo_wall(t_cube *cube) //checks if the map is surrounded by walls
{
	int i; //current map row
	i = 0;
	int index = 0;
	while(cube->map[i]) //iterates through each row of the map
	{
		int j = 0;
		if(i == 0 || i == len_map(cube) - 1) //if we are on the first or last row, we verify that there are only 1s or whitespaces
		{
			while (cube->map[i][j])
			{
				if(cube->map[i][j] == '1' || cube->map[i][j] == '\v' || cube->map[i][j] == '\t' || cube->map[i][j] == ' ' || cube->map[i][j] == '\n')
					j++;
				else 
					return(printf("Error, invalid map\n"), 1);
			}
		}
		while (cube->map[i][j])
		{
			index = ft_strlen(cube->map[i]) - 2;
			if(cube->map[i][0] != '1' && cube->map[i][0] != ' ') //first char must be 1 or space
				return(printf("Error, invalid map\n"), 1);
			else if(cube->map[i][ft_strlen(cube->map[i]) - 2] == ' ')
			{
				index = ft_strlen(cube->map[i]) - 2;
				while (cube->map[i][index] == ' ')
					index--;
			}
			if(cube->map[i][index] != '1')
				return(printf("Error, invalid map\n"));
			if(cube->map[i][j] == '0')
			{
				if(!cube->map[i - 1][j] || !cube->map[i + 1][j])
					return(printf("Error, invalid map\n"), 1);
				else if(cube->map[i - 1][j] == ' ' || cube->map[i + 1][j] == ' ')
					return(printf("Error, invalid map\n"), 1);
			}
			else if(cube->map[i][j] == '\t')
				return(printf("Error, invalid map\n"),1 );
			j++;
		}
		i++;
	}
	return(0);
}