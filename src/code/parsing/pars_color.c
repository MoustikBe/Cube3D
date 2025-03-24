/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:53:24 by misaac-c          #+#    #+#             */
/*   Updated: 2025/03/24 12:04:47 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cube.h"
#include "../../libs/libft/libft.h"

int	rgb_checker(int *nb)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (nb[i] > 255 || nb[i] < 0)
			return (ft_printf("Error\nRGB color are bettween 0 and 255\n"));
		i++;
	}
	return (0);
}

int	pars_color_format(t_texture *skin, char *line, int flag)
{
	int	i;

	i = 1;
	while (line[i] == ' ')
		i++;
	while (line[i])
	{
		if (!ft_isdigit(line[i]) && line[i] != ',' && line[i] != ' '
			&& line[i] != '\n')
		{
			skin->error = 1;
			return (ft_printf("Error\nNot valid color format\n"));
		}
		while ((line[i] == ',' || line[i] == ' ') && line[i])
		{
			if (line[i] == ',')
				flag++;
			i++;
		}
		if (ft_isdigit(line[i]) || line[i] == '\n')
			i++;
	}
	if (flag != 2)
		return (1);
	return (0);
}

char	*color_char_format(t_texture *skin, char *line, int len, int i_)
{
	int		i;
	char	*clr_str;

	i = 0;
	clr_str = malloc(sizeof(char) * (len + 1));
	while (line[i_] != ',' && line[i_])
	{
		if (line[i_] == ' ' || line[i_] == '\n')
			i_++;
		else
			clr_str[i++] = line[i_++];
	}
	clr_str[i] = '\0';
	if (clr_str[0] == '\0')
	{
		ft_printf("Error\nNot existing value for rgb\n");
		skin->error = 1;
		return (NULL);
	}
	return (clr_str);
}

int	store_color(t_texture *skin, int **color, char *line)
{
	int		i;
	int		i_;
	int		nb;
	int		len;
	char	*clr_str;

	i = 1;
	i_ = 0;
	nb = 0;
	*color = malloc(sizeof(int) * 3);
	while (nb < 3)
	{
		i_ = i;
		len = cal_len_color(line, &i);
		clr_str = color_char_format(skin, line, len, i_);
		if (clr_str == NULL)
			return (1);
		(*color)[nb] = ft_atoi(clr_str);
		free(clr_str);
		nb++;
		i++;
	}
	return (0);
}

void	set_fc_color(t_texture *skin, int **color, char *line)
{
	if (*color)
	{
		ft_printf("Error\nDuplicate color.\n");
		skin->error = 1;
	}
	if (pars_color_format(skin, line, 0))
		return ;
	if (store_color(skin, color, line))
		return ;
}
