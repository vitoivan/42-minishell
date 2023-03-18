/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 22:18:28 by victor            #+#    #+#             */
/*   Updated: 2022/12/09 20:03:39 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*tmp;

	tmp = s;
	while (*tmp)
		tmp++;
	while (tmp >= s)
	{
		if ((unsigned char)*tmp == (unsigned char)c)
			return ((char *)tmp);
		tmp--;
	}
	return (NULL);
}
