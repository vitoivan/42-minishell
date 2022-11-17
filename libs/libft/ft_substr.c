/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <vivan-de@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 06:02:36 by victor            #+#    #+#             */
/*   Updated: 2021/09/16 16:14:47 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sbstr;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start > s_len)
		len = 1;
	else if (start + len > s_len)
		len = s_len - start + 1;
	else
		len++;
	sbstr = malloc(len * sizeof(char));
	if (sbstr == NULL)
		return (NULL);
	ft_strlcpy(sbstr, s + start, len);
	return (sbstr);
}
