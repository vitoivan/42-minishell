/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 14:25:23 by victor            #+#    #+#             */
/*   Updated: 2022/12/09 20:03:28 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

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
