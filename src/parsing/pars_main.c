/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:58:44 by misaac-c          #+#    #+#             */
/*   Updated: 2025/03/07 11:13:48 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube.h"
#include "../libs/libft/libft.h"

void	check_component(t_texture *skin)
{
	int i;

	if(!skin->NO || !skin->SO || !skin->EA || !skin->WE || !skin->C || !skin->F)
	{
		ft_printf("Error\nMissing color or texture valid.\n");
		skin->error = 1;
	}
	else if(open(skin->NO, R_OK) < 0 || open(skin->SO, R_OK) < 0 || open(skin->EA, R_OK) < 0 || open(skin->WE, R_OK) < 0)
	{
		ft_printf("Error\nInvalid texture file.\n");
		skin->error = 1;
	}
	else
	{
		if(rgb_checker(skin->C) || rgb_checker(skin->F))
		{
			skin->error = 1;
			return ;
		}
	}
}

int	parsing(t_texture *skin, t_cube *cube, char **argv)
{
	cube->file_map = ft_strdup(argv[1]); // leaks
	if (verif_file(cube))
		return (1);
	verif_info(skin, cube);
	if (skin->error)
		return (1);
	if (verif_map(cube))
		return (1);
	if (algo_wall(cube))
		return (1);
	return (0);
}
