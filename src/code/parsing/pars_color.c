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

int	rgb_checker(int *nb) //checks if the number is between 0 and 255
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

int	pars_color_format(t_texture *skin, char *line, int flag) //checks if the color format is good
{
	int	i;

	i = 1; //skips the first char cause the first one is F for floor or C for ceiling
	while (line[i] == ' ')
		i++;
	while (line[i])
	{
		if (!ft_isdigit(line[i]) && line[i] != ',' && line[i] != ' ' //If the character is NOT a digit, comma, space, or newline, this is invalid for a color format.
			&& line[i] != '\n')
		{
			skin->error = 1;
			return (ft_printf("Error\nNot valid color format\n"));
		}
		while ((line[i] == ',' || line[i] == ' ') && line[i])
		{
			if (line[i] == ',')
				flag++; //flag counts how manu commands were found
			i++;
		}
		if (ft_isdigit(line[i]) || line[i] == '\n')
			i++;
	}
	if (flag != 2) //Color formats usually have 3 components separated by 2 commas (e.g. R,G,B).
		return (1);
	return (0);
}

char	*color_char_format(t_texture *skin, char *line, int len, int i_) //extracts a single color value as a string (for example, 255)
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

int	store_color(t_texture *skin, int **color, char *line) //Esta función lee una línea de texto que contiene tres valores de color (RGB), los extrae, los convierte a enteros y los almacena en un arreglo de tres enteros (un array de 3 valores que representan R, G y B).
{
	int		i;
	int		i_;
	int		nb;
	int		len;
	char	*clr_str;

	i = 1;
	i_ = 0;
	nb = 0;
	*color = malloc(sizeof(int) * 3); //array que contendrá los colores R,G,B
	while (nb < 3)
	{
		i_ = i;
		len = cal_len_color(line, &i); //counts the length of a single color value (until it reaches a comma). for example, in 255,   200, 200, it returns 3 for 255 and the pointer i stays at the comma position
		clr_str = color_char_format(skin, line, len, i_); //extracts a single color value as a string (for example, 255)
		if (clr_str == NULL)
			return (1);
		(*color)[nb] = ft_atoi(clr_str); //pasa de string a int
		free(clr_str);
		nb++;
		i++;
	}
	return (0);
}

void	set_fc_color(t_texture *skin, int **color, char *line) //checks if the color format is good and saves each color in an array
{
	if (*color)
	{
		ft_printf("Error\nDuplicate color.\n");
		skin->error = 1;
	}
	if (pars_color_format(skin, line, 0)) //checks if the color format is good
		return ;
	if (store_color(skin, color, line)) //read the line that contains the colors, extracts them as string, converts them to int, saves the values in the color array
	{
		return ;
	}
}
