/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:58:44 by misaac-c          #+#    #+#             */
/*   Updated: 2025/03/05 12:40:34 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube.h"
#include "../libs/libft/libft.h"

int	verif_file(t_cube *c)
{
	int	l;

	l = ft_strlen(c->file_map);
	if (l > 3)
	{
		if (c->file_map[l - 1] == 'b' && c->file_map[l - 2] == 'u'
			&& c->file_map[l - 3] == 'c' && c->file_map[l - 4] == '.')
		{
			if (open(c->file_map, R_OK))
				return(0);
			else
				return(ft_printf("Error\nFile not found or not readable\n"));
		}
	}
	return(ft_printf("Error\nBad file extension\n"));
}

void	set_skin(t_texture *skin, char **texture, char *line)
{
	char *str;
	int len;
	int i;
	int i_copy;

	if(*texture)
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
	while (line[i] && line[i] != ' ' && line[i] != '\n')
	{
		len++;
		i++;
	}
	str = malloc(len + 1);
	len = 0;
	while (line[i_copy] && line[i_copy] != ' ' && line[i_copy] != '\n')
		str[len++] = line[i_copy++];
	str[len] = '\0';
	*texture = ft_strdup(str);
	free(str);
}

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

void verif_info(t_texture *skin, t_cube *cube)
{
	// regarder les info avec get_next_line, puis les sauvegarder. CAD NO SO EA WE C F
	char	*line;
	int		fd_map;

	fd_map = open(cube->file_map, R_OK);
	line = get_next_line(fd_map);
	while (line)
	{
		// regarder le contenus de la ligne et verifier si on voit une des info que l'on a besoin. 
		if (ft_strncmp("NO ", line, 3) == 0)
			set_skin(skin, &skin->NO, line);
		if (ft_strncmp("SO ", line, 3) == 0)
			set_skin(skin, &skin->SO, line);
		if (ft_strncmp("EA ", line, 3) == 0)
			set_skin(skin, &skin->EA, line);
		if (ft_strncmp("WE ", line, 3) == 0)
			set_skin(skin, &skin->WE, line);
		if (ft_strncmp("C ", line, 2) == 0)
			set_fc_color(skin, &skin->C, line);
		if (ft_strncmp("F ", line, 2) == 0)
			set_fc_color(skin, &skin->F, line);
		free(line);
		line = get_next_line(fd_map);
	}
	check_component(skin);
	close(fd_map);
}

int verif_line(char *line)
{
	int i = 0;
	
	while (line[i] == '\v' || line[i] == '\t' || line[i] == ' ' || line[i] == '1' || line[i] == '0' || line[i] == 'N' || line[i] == 'E' || line[i] == 'W' || line[i] == 'S')
	{
		if(!line[i + 1] || line[i + 1] == '\n')
			return(1); // Ligne avec seuelemt 1 0 N E W S, mais pas le plus otpi assez brouillon et moche. //
		i++;
	}
	return(0);
}

int	len_map(t_cube *cube)
{
	char	*line;
	int		fd_map;
	int		len;

	len = 0;
	fd_map = open(cube->file_map, R_OK);
	line = get_next_line(fd_map);
	while (line)
	{
		if(verif_line(line))
			len++;
		free(line);
		line = get_next_line(fd_map);
	}
	close(fd_map);
	return(len);
}

int saving_data(t_cube *cube, char *line, int index)
{
	int i;

	i = 0;
	while (line[i])
	{
		if(line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
		{
			if(cube->y_plr || cube->x_plr)
				return(ft_printf("Error duplicate component\n"));
			cube->y_plr = index;
			cube->x_plr = i;
		}
		if(line[i] == 'N')
		{
			cube->y_dir_plr = -1;
			cube->x_dir_plr = 0;
		}
		else if(line[i] == 'S')
		{
			cube->y_dir_plr = 1;
			cube->x_dir_plr = 0;
		}
		else if(line[i] == 'W')
		{
			cube->y_dir_plr = 0;
			cube->x_dir_plr = -1;
		}
		else if(line[i] == 'E')
		{
			cube->y_dir_plr = 0;
			cube->x_dir_plr = 1;
		}
		i++;
	}
	cube->map[index] = ft_strdup(line);
	return(0);
}

int verif_map(t_cube *cube)
{
	char	*line;
	int		fd_map;
	int		index;

	index = 0;
	cube->map = malloc(sizeof(char *) * (len_map(cube) + 1));
	fd_map = open(cube->file_map, R_OK);
	line = get_next_line(fd_map);
	while (line)
	{
		if(verif_line(line))
		{
			
			if(saving_data(cube, line, index))
			{
				free(line);
				return(1);
			}
			index++;
			free(line);
			line = get_next_line(fd_map);
		}
		else if(!ft_strncmp("NO ", line, 3) || !ft_strncmp("EA ", line, 3) || !ft_strncmp("WE ", line, 3) || !ft_strncmp("SO ", line, 3) || ft_strncmp("F ", line, 2) == 0 || ft_strncmp("C ", line, 2) == 0 || line[0] == '\n')
		{
			free(line);
			line = get_next_line(fd_map);
		}
		else
		{
			free(line);
			return(ft_printf("Error bad config file\n"));
		}
	}
	close(fd_map);
	cube->map[index] = NULL;
	if(!cube->x_plr && !cube->y_plr)
		return(ft_printf("Error no player location found\n"));
	return(0);
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
	return (0);
}
