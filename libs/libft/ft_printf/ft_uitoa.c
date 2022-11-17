/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 12:42:05 by victor            #+#    #+#             */
/*   Updated: 2022/08/07 08:29:34 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static int	n_len(unsigned int n)
{
	int	len;

	len = 0;
	while (n >= 1)
	{
		len++;
		n = n / 10;
	}
	if (len == 0)
		return (len + 1);
	return (len);
}

static char	*transfer_nb_to_arr(char *output, unsigned int n, int len)
{
	int	curr_n;

	output[len] = '\0';
	len--;
	while (len >= 0)
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

char	*ft_uitoa(unsigned int n)
{
	int		len;
	char	*output;

	len = n_len(n);
	output = (char *)malloc(len + 1);
	if (!output)
		return (NULL);
	return (transfer_nb_to_arr(output, n, len));
}
