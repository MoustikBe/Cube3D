/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:53:24 by misaac-c          #+#    #+#             */
/*   Updated: 2025/03/05 12:56:29 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube.h"
#include "../libs/libft/libft.h"

int	rgb_checker(int *nb)
{
	int i;

	i = 0;
	while (i < 3)
	{
		if(nb[i] > 255 || nb[i] < 0)
			return (ft_printf("Error\nRGB color are bettween 0 and 255\n"));
		i++;
	}
	return(0);
}

void	set_fc_color(t_texture *skin, int **color, char *line)
{
	// INT *C = [0,0,0]; 
	int i;
	int i_copy;
	int flag;

	flag = 0;
	if(*color)
	{
		ft_printf("Error\nDuplicate color.\n");
		skin->error = 1;
	}
	i = 1; 
	while (line[i] == ' ')
		i++;
	while (line[i])
	{
		if(!ft_isdigit(line[i]) && line[i] != ',' && line[i] != ' ' && line[i] != '\n')
		{
			ft_printf("Error\nNot valid color format\n");
			skin->error = 1;
			return ;
		}
		while((line[i] == ',' || line[i] == ' ') && line[i])
		{
			if(line[i] == ',')
				flag++;
			i++;	
		}
		if(ft_isdigit(line[i]) || line[i] == '\n')
			i++;	
	}
	if(flag != 2)
		return ;
	/* VERIFICATION */
	*color = malloc(sizeof(int) * 3);
	char *clr_str;
	i = 1;
	i_copy = 0;
	int nb = 0;
	int len = 0;
	while (nb < 3)
	{
		len = 0;
		i_copy = i;
		while (line[i] != ',' && line[i])
		{
			if(line[i] == ' ' || line[i] == '\n')
				i++;
			else
			{
				i++;
				len++;
			}
		}
		clr_str = malloc(sizeof(char) * len + 1);
		len = 0;
		while (line[i_copy] != ',' && line[i_copy])
		{
			if(line[i_copy] == ' ' || line[i_copy] == '\n')
				i_copy++;
			else
				clr_str[len++] = line[i_copy++];
		}
		clr_str[len] = '\0';
		if(clr_str[0] == '\0')
		{
			ft_printf("Error\nNot existing value for rgb\n");
			skin->error = 1;
			return ;
		}
		(*color)[nb] = ft_atoi(clr_str);
		free(clr_str);
		nb++;
		i++;
	}
}
