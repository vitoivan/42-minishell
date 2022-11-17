/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 12:12:53 by vivan-de          #+#    #+#             */
/*   Updated: 2022/08/07 08:29:28 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		i;
	int		char_count;

	va_start(args, str);
	i = 0;
	char_count = 0;
	while (str[i])
	{
		if (str[i] == '%' && str[++i])
			ft_print_arg((char *)str, args, &char_count, &i);
		else
		{
			ft_putchar_fd(str[i], 1);
			char_count++;
			i++;
		}
	}
	va_end(args);
	return (char_count);
}
