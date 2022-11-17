/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_udigit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 14:39:47 by vivan-de          #+#    #+#             */
/*   Updated: 2022/08/07 08:29:23 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	ft_print_udigit(unsigned int nbr, int ***char_count)
{
	char	*nbr_str;

	nbr_str = ft_uitoa(nbr);
	ft_print_str(nbr_str, char_count);
	free(nbr_str);
}
