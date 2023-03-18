/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 22:58:48 by victor            #+#    #+#             */
/*   Updated: 2022/12/09 20:03:37 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	const char	*b;
	const char	*l;
	int			l_len;

	if (!big || !little)
		return (NULL);
	b = big;
	l = little;
	l_len = ft_strlen(l);
	if (!l_len)
		return ((char *)b);
	if ((int)len == -1)
		len = ft_strlen(big);
	while (*b && len)
	{
		if (*b == *l)
		{
			if (!(ft_strncmp(b, l, l_len)) && (int)l_len <= (int)len)
				return ((char *)b);
		}
		b++;
		len--;
	}
	return (NULL);
}
