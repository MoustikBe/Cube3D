/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 18:10:36 by misaac-c          #+#    #+#             */
/*   Updated: 2024/02/24 18:52:50 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_unsigned(unsigned int nbr, int *count_2)
{
	if (nbr > 9)
	{
		ft_putnbr(nbr / 10, count_2);
		ft_putchar(nbr % 10 + '0', count_2);
	}
	else
		ft_putchar(nbr + '0', count_2);
}
