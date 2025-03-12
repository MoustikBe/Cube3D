/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 18:10:13 by misaac-c          #+#    #+#             */
/*   Updated: 2024/02/24 18:25:12 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar(int s, int *count_2)
{
	int	tchek;

	tchek = write(1, &s, 1);
	if (tchek < 0)
	{
		(*count_2) = -1;
		return ;
	}
	(*count_2)++;
}
