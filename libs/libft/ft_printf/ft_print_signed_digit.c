/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_signed_digit.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 10:50:04 by vivan-de          #+#    #+#             */
/*   Updated: 2022/08/07 08:29:17 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	ft_print_signed_digit(int nbr, int ***char_count)
{
	char	*nbr_str;

	nbr_str = ft_itoa(nbr);
	ft_print_str(nbr_str, char_count);
	free(nbr_str);
}
