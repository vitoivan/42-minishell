/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itohex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 13:19:42 by vivan-de          #+#    #+#             */
/*   Updated: 2022/08/07 08:28:17 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static int	nbr_len(unsigned long int number)
{
	int	size;

	size = 0;
	while (number >= 1)
	{
		number = number / 16;
		size++;
	}
	return (size);
}

char	*ft_itohex(unsigned long int number, char type)
{
	int		i;
	int		rest;
	int		letter_nbr;
	char	*hex;

	if (type == 'X')
		letter_nbr = 55;
	if (type == 'x')
		letter_nbr = 87;
	i = nbr_len(number);
	hex = malloc((i + 1) * sizeof(char));
	hex[i] = '\0';
	i--;
	if (!hex)
		return (NULL);
	while (number != 0)
	{
		rest = number % 16;
		if (rest < 10)
			hex[i--] = 48 + rest;
		else
			hex[i--] = letter_nbr + rest;
		number = number / 16;
	}
	return (hex);
}
