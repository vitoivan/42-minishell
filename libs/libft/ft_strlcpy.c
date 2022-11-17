/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <vivan-de@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 14:25:23 by victor            #+#    #+#             */
/*   Updated: 2021/09/16 13:41:31 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t		s_len;
	char		*d;
	const char	*s;

	if (!dst || !src)
		return (0);
	d = dst;
	s = src;
	s_len = ft_strlen(s);
	if (!size)
		return (s_len);
	while (size - 1 && *s)
	{
		*d++ = *s++;
		size--;
	}
	*d = '\0';
	return (s_len);
}
