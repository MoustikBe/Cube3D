/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_algo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 11:14:06 by misaac-c          #+#    #+#             */
/*   Updated: 2025/06/22 21:24:49 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cube.h"
#include "../../libs/libft/libft.h"

int	verif_first_last(t_cube *cube, int i, int *j)
{
	while (cube->map[i][*j])
	{
		if (cube->map[i][*j] == '1' || cube->map[i][*j] == '\v'
			|| cube->map[i][*j] == '\t' || cube->map[i][*j] == ' '
			|| cube->map[i][*j] == '\n')
			(*j)++;
		else
			return (printf("Error, invalid map\n"), 1);
	}
	return (0);
}

int	verif_inter_wall(t_cube *cube, int i, int *j)
{
	int	index;

	index = ft_strlen(cube->map[i]) - 2;
	if (cube->map[i][0] != '1' && cube->map[i][0] != ' ')
		return (printf("Error, invalid map\n"), 1);
	else if (cube->map[i][ft_strlen(cube->map[i]) - 2] == ' ')
	{
		index = ft_strlen(cube->map[i]) - 2;
		while (cube->map[i][index] == ' ')
			index--;
	}
	if (cube->map[i][index] != '1')
		return (printf("Error, invalid map\n"));
	if (cube->map[i][*j] == '0')
	{
		if (!cube->map[i - 1][*j] || !cube->map[i + 1][*j])
			return (printf("Error, invalid map\n"), 1);
		else if (cube->map[i - 1][*j] == ' ' || cube->map[i + 1][*j] == ' ')
			return (printf("Error, invalid map\n"), 1);
	}
	else if (cube->map[i][*j] == '\t')
		return (printf("Error, invalid map\n"), 1);
	(*j)++;
	return (0);
}

int	algo_wall(t_cube *cube)
{
	int	i;
	int	j;

	i = 0;
	while (cube->map[i])
	{
		j = 0;
		if (i == 0 || i == len_map(cube) - 1)
			if (verif_first_last(cube, i, &j))
				return (1);
		while (cube->map[i][j])
			if (verif_inter_wall(cube, i, &j))
				return (1);
		i++;
	}
	return (0);
}
