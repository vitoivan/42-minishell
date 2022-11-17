/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <vivan-de@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 14:57:15 by victor            #+#    #+#             */
/*   Updated: 2021/08/22 13:04:18 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*s;
	char	*d;	

	s = (char *) src;
	d = (char *) dst;
	if (!d && !s)
		return (0);
	while (n)
	{
		*d = *s;
		n--;
		d++;
		s++;
	}
	return (dst);
}
