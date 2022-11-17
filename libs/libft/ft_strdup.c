/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <vivan-de@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 22:16:17 by victor            #+#    #+#             */
/*   Updated: 2021/08/22 22:17:11 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

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
