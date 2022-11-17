/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 22:09:17 by vivan-de          #+#    #+#             */
/*   Updated: 2022/08/07 08:29:10 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	ft_print_ptr(void *ptr, int ***char_count)
{
	if (!ptr)
		ft_print_str("(nil)", char_count);
	else
		ft_print_hex((unsigned long int)ptr, 'x', char_count, 1);
}
