/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_storage.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:09:25 by misaac-c          #+#    #+#             */
/*   Updated: 2025/06/23 18:05:52 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cube.h"
#include "../../libs/libft/libft.h"

void	set_skin(t_texture *skin, char **texture, char *line)
{
	char	*str;
	int		len;
	int		i;
	int		i_copy;

	if (*texture)
	{
		ft_printf("Error\nDuplicate information detected.\n");
		skin->error = 1;
		return ;
	}
	len = 0;
	i = 2;
	while (line[i] == ' ')
		i++;
	i_copy = i;
	while (line[i] && line[i] != ' ' && line[i++] != '\n')
		len++;
	str = malloc(len + 1);
	len = 0;
	while (line[i_copy] && line[i_copy] != ' ' && line[i_copy] != '\n')
		str[len++] = line[i_copy++];
	str[len] = '\0';
	*texture = ft_strdup(str);
	free(str);
}

void	set_dir_ply(t_cube *cube, int a, int b)
{
	cube->y_dir_plr = a;
	cube->x_dir_plr = b;
}

int	saving_data(t_cube *cube, char *line, int index)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 'N' || line[i] == 'S'
			|| line[i] == 'E' || line[i] == 'W')
		{
			if (cube->y_plr || cube->x_plr)
				return (ft_printf("Error duplicate component\n"));
			cube->y_plr = index;
			cube->x_plr = i;
			cube->player = line[i];
		}
		if (line[i] == 'N')
			set_dir_ply(cube, -1, 0);
		else if (line[i] == 'S')
			set_dir_ply(cube, 1, 0);
		else if (line[i] == 'W')
			set_dir_ply(cube, 0, -1);
		else if (line[i] == 'E')
			set_dir_ply(cube, 0, 1);
		i++;
	}
	return (cube->flag = 1, cube->map[index] = ft_strdup(line), 0);
}
