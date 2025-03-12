/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 18:10:20 by misaac-c          #+#    #+#             */
/*   Updated: 2024/02/24 18:26:39 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_hexadecimal(unsigned int nbr, char *hexa, int *count_2)
{
	if (nbr >= 16)
		ft_hexadecimal(nbr / 16, hexa, count_2);
	ft_putchar(hexa[nbr % 16], count_2);
}
