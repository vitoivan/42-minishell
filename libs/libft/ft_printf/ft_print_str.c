/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 12:13:28 by vivan-de          #+#    #+#             */
/*   Updated: 2022/08/07 08:29:20 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	ft_print_str(char *str, int ***char_count)
{
	char	*tmp;

	tmp = str;
	if (!tmp)
	{
		ft_print_str("(null)", char_count);
	}
	else
	{
		while (*tmp)
		{
			ft_putchar_fd(*tmp, 1);
			tmp++;
			***char_count += 1;
		}
	}
}
