/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <vivan-de@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 18:01:51 by victor            #+#    #+#             */
/*   Updated: 2021/09/16 16:19:55 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*output;
	size_t	l_s1;
	size_t	l_s2;

	if (!s1 || !s2)
		return (NULL);
	l_s1 = ft_strlen(s1);
	l_s2 = ft_strlen(s2);
	output = malloc((l_s1 + l_s2 + 1) * sizeof(char));
	if (output == NULL)
		return (NULL);
	ft_strlcpy(output, s1, l_s1 + 1);
	ft_strlcpy((output + l_s1), s2, l_s2 + 1);
	return (output);
}
