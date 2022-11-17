/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <vivan-de@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 22:15:22 by victor            #+#    #+#             */
/*   Updated: 2021/09/02 15:45:36 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	const char	*tmp;

	if (!s)
		return (NULL);
	tmp = s;
	while (*tmp)
	{
		if ((unsigned char) *tmp == (unsigned char) c)
			return ((char *) tmp);
		tmp++;
	}
	if ((unsigned char) *tmp == (unsigned char) c)
		return ((char *) tmp);
	return (NULL);
}
