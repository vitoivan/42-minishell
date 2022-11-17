/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <victor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 15:36:38 by victor            #+#    #+#             */
/*   Updated: 2021/09/01 08:41:56 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*ptr;
	size_t			len;
	unsigned int	ind;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	ptr = ft_calloc(len + 1, sizeof(char));
	ind = 0;
	if (!ptr)
		return (NULL);
	while (len > 0)
	{
		ptr[ind] = f(ind, (char)s[ind]);
		ind++;
		len--;
	}
	ptr[ind] = '\0';
	return (ptr);
}
