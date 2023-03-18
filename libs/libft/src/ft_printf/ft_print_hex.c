/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 14:39:42 by vivan-de          #+#    #+#             */
/*   Updated: 2022/12/09 20:05:24 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

void	ft_print_hex(unsigned long int nbr, char c, int ***char_count, int pref)
{
	char	*nbr_str;

	if (pref != 0)
	{
		if (c == 'x')
			ft_print_str("0x", char_count);
		else
			ft_print_str("0X", char_count);
	}
	nbr_str = ft_itohex(nbr, c);
	ft_print_str(nbr_str, char_count);
	free(nbr_str);
	if (!nbr)
		ft_print_char('0', char_count);
}
