/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 18:10:33 by misaac-c          #+#    #+#             */
/*   Updated: 2024/02/24 18:45:09 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putstr(char *s, int *count_2)
{
	int	i;

	i = 0;
	if (s == NULL)
	{
		ft_putstr("(null)", count_2);
		return ;
	}
	while (s[i])
		ft_putchar((int)s[i++], count_2);
}
