/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:58:44 by misaac-c          #+#    #+#             */
/*   Updated: 2025/06/16 19:57:38 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cube.h"
#include "../../libs/libft/libft.h"

void	check_component(t_texture *skin)
{
	if (!skin->no || !skin->so || !skin->ea
		|| !skin->we || !skin->c || !skin->f)
	{
		ft_printf("Error\nMissing color or texture valid.\n");
		skin->error = 1;
	}
	else if (open(skin->no, O_RDONLY) < 0
		|| open(skin->so, O_RDONLY) < 0 || open(skin->ea, O_RDONLY) < 0
		|| open(skin->we, O_RDONLY) < 0)
	{
		ft_printf("Error\nInvalid texture file.\n");
		skin->error = 1;
	}
	else
	{
		if (rgb_checker(skin->c) || rgb_checker(skin->f))
		{
			skin->error = 1;
			return ;
		}
	}
}

int	parsing(t_texture *skin, t_cube *cube, char **argv)
{
	cube->file_map = ft_strdup(argv[1]);
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
