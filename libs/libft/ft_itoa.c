/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <victor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 12:42:05 by victor            #+#    #+#             */
/*   Updated: 2021/09/16 07:44:54 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	is_negative(int n)
{
	if (n >= 0)
		return (0);
	return (1);
}

static int	n_len(int n)
{
	int	len;

	len = 0;
	if (is_negative(n))
	{
		while (n <= (-1))
		{
			len++;
			n = n / 10;
		}
	}
	else
	{
		while (n >= 1)
		{
			len++;
			n = n / 10;
		}
	}
	if (len == 0)
		return (len + 1);
	return (len);
}

static char	*transfer_nb_to_arr(char *output, int n, int len)
{
	int	curr_n;
	int	negative;

	negative = is_negative(n);
	if (negative)
		output[len + 1] = '\0';
	else
	{
		output[len] = '\0';
		len--;
	}
	while (len >= negative)
	{
		curr_n = n % 10;
		if (curr_n < 0)
			curr_n = curr_n * (-1);
		output[len] = curr_n + '0';
		len--;
		n = n / 10;
	}
	return (output);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*output;

	len = n_len(n);
	if (is_negative(n))
	{
		output = (char *) malloc(len + 2);
		if (!output)
			return (NULL);
		*output = '-';
	}
	else
	{
		output = (char *) malloc(len + 1);
		if (!output)
			return (NULL);
	}
	return (transfer_nb_to_arr(output, n, len));
}
