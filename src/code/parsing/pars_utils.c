/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:22:12 by misaac-c          #+#    #+#             */
/*   Updated: 2025/03/24 12:04:27 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cube.h"
#include "../../libs/libft/libft.h"

int	is_map_line(char *line) //checks if the line is part of the map or of the textures/color lines
{
	if (!ft_strncmp("NO ", line, 3) || !ft_strncmp("EA ", line, 3)
		|| !ft_strncmp("WE ", line, 3)
		|| !ft_strncmp("SO ", line, 3)
		|| ft_strncmp("F ", line, 2) == 0
		|| ft_strncmp("C ", line, 2) == 0
		|| line[0] == '\n')
		return (1);
	return (0);
}

int	cal_len_color(char *line, int *i) //counts the length of a single color value (until it reaches a comma). for example, in 255,   200, 200, it returns 3 for 255 and the pointer i stays at the comma position
{
	int	len;

	len = 0;
	while (line[*i] != ',' && line[*i])
	{
		if (line[*i] == ' ' || line[*i] == '\n')
			(*i)++;
		else
		{
			(*i)++;
			len++;
		}
	}
	return (len);
}
