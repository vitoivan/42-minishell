/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <victor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 16:12:43 by victor            #+#    #+#             */
/*   Updated: 2021/08/26 16:34:54 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	char	*s1;

	if (!s)
		return ;
	s1 = s;
	while (*s1)
	{
		ft_putchar_fd(*s1, fd);
		s1++;
	}
}
