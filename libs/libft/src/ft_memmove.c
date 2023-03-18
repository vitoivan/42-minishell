/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 10:49:34 by victor            #+#    #+#             */
/*   Updated: 2022/12/09 20:02:45 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*d;
	char	*s;

	d = (char *)dest;
	s = (char *)src;
	if (s == d)
		return (dest);
	if (d > s)
	{
		s = s + n - 1;
		d = d + n - 1;
		while (n)
		{
			*d = *s;
			d--;
			s--;
			n--;
		}
	}
	else
		ft_memcpy(dest, src, n);
	return (dest);
}
