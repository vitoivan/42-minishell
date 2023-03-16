/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isquote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 13:46:45 by vivan-de          #+#    #+#             */
/*   Updated: 2023/03/16 13:46:46 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

BOOL	ft_is_double_quote(char c)
{
	if (!c)
		return (False);
	if (c == DOUBLE_QUOTE)
		return (True);
	return (False);
}

BOOL	ft_is_single_quote(char c)
{
	if (!c)
		return (False);
	if (c == SINGLE_QUOTE)
		return (True);
	return (False);
}

BOOL	ft_isquote(char c)
{
	if (!c)
		return (False);
	if (ft_is_double_quote(c) || ft_is_single_quote(c))
		return (True);
	return (False);
}
