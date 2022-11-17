/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_conversion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 12:13:23 by vivan-de          #+#    #+#             */
/*   Updated: 2022/08/07 08:28:45 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	ft_print_conversion(unsigned int c, va_list args, int **char_count)
{
	if (c == 'c')
		ft_print_char(va_arg(args, unsigned int), &char_count);
	else if (c == '%')
		ft_print_char('%', &char_count);
	else if (c == 's')
		ft_print_str(va_arg(args, char *), &char_count);
	else if (c == 'i' || c == 'd')
		ft_print_signed_digit(va_arg(args, int), &char_count);
	else if (c == 'u')
		ft_print_udigit(va_arg(args, unsigned int), &char_count);
	else if (c == 'x' || c == 'X')
		ft_print_hex(va_arg(args, unsigned long int), c, &char_count, 0);
	else if (c == 'p')
		ft_print_ptr(va_arg(args, void *), &char_count);
}
