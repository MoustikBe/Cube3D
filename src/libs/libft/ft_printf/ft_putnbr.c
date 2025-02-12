/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 18:10:23 by misaac-c          #+#    #+#             */
/*   Updated: 2024/02/24 18:43:15 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr(int nbr, int *count_2)
{
	unsigned int	n;

	if (nbr < 0)
	{
		ft_putchar('-', count_2);
		n = -nbr;
	}
	else
		n = nbr;
	if (n > 9)
	{
		ft_putnbr(n / 10, count_2);
		ft_putchar(n % 10 + '0', count_2);
	}
	else
		ft_putchar(n + '0', count_2);
}
