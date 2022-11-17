/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <vivan-de@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 22:18:28 by victor            #+#    #+#             */
/*   Updated: 2021/09/02 15:48:32 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*tmp;

	tmp = s;
	while (*tmp)
		tmp++;
	while (tmp >= s)
	{
		if ((unsigned char) *tmp == (unsigned char) c)
			return ((char *) tmp);
		tmp--;
	}
	return (NULL);
}
