/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:22:12 by misaac-c          #+#    #+#             */
/*   Updated: 2025/03/20 13:22:31 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cube.h"
#include "../../libs/libft/libft.h"

int	big_condition(char *line)
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
