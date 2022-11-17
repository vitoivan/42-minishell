/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <vivan-de@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 14:46:34 by victor            #+#    #+#             */
/*   Updated: 2021/08/25 19:03:29 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	char		*d;
	const char	*s;
	size_t		d_len;
	size_t		s_len;

	d = dst;
	s = src;
	d_len = ft_strlen(d);
	s_len = ft_strlen(s);
	if (d_len >= size)
		return (s_len + size);
	else
		ft_strlcpy(d + d_len, s, size - d_len);
	return (d_len + s_len);
}
