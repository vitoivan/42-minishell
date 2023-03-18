/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 22:15:22 by victor            #+#    #+#             */
/*   Updated: 2022/12/09 20:03:08 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strchr(const char *s, int c)
{
	const char	*tmp;

	if (!s)
		return (NULL);
	tmp = s;
	while (*tmp)
	{
		if ((unsigned char)*tmp == (unsigned char)c)
			return ((char *)tmp);
		tmp++;
	}
	if ((unsigned char)*tmp == (unsigned char)c)
		return ((char *)tmp);
	return (NULL);
}
