/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <vivan-de@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 14:42:51 by victor            #+#    #+#             */
/*   Updated: 2021/09/19 16:49:43 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	unsigned char	*dst;

	dst = (unsigned char *) str;
	while (n)
	{
		*dst = (unsigned char) c;
		dst++;
		n--;
	}	
	return (str);
}
