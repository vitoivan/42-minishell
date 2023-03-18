/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 22:16:17 by victor            #+#    #+#             */
/*   Updated: 2022/12/09 20:03:13 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strdup(const char *s)
{
	char	*ptr;
	size_t	l;

	l = ft_strlen(s);
	ptr = malloc(l + 1);
	if (!ptr)
		return (0);
	ft_strlcpy(ptr, s, l + 1);
	return (ptr);
}
