/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 12:13:12 by vivan-de          #+#    #+#             */
/*   Updated: 2022/08/07 08:28:30 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	ft_print_arg(char *str, va_list args, int *char_count, int *i)
{
	if (ft_is_conversion(str[*i]))
	{
		ft_print_conversion(str[*i], args, &char_count);
		*i += 1;
	}
}
