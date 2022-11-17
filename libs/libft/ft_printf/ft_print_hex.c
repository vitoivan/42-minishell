/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 14:39:42 by vivan-de          #+#    #+#             */
/*   Updated: 2022/08/07 08:28:56 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

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
