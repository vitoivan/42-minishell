/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 22:19:04 by victor            #+#    #+#             */
/*   Updated: 2022/08/06 16:29:32 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	const char	*tmp1;
	const char	*tmp2;

	tmp1 = s1;
	tmp2 = s2;
	if (ft_strlen(tmp1) != ft_strlen(tmp2))
		return (1);
	while (tmp1 && tmp2)
	{
		if (*tmp1 != *tmp2)
			return ((unsigned char)*tmp1 - (unsigned char)*tmp2);
		else if (!(*tmp1) || !(*tmp2))
			break ;
		tmp1++;
		tmp2++;
	}
	return (0);
}
