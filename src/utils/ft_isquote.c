/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_double_quote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor.simoes <victor.simoes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 14:31:23 by victor.simo       #+#    #+#             */
/*   Updated: 2023/02/04 14:31:26 by victor.simo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

BOOL	ft_is_double_quote(char c)
{
	if (c == DOUBLE_QUOTE)
		return (True);
	return (False);
}

BOOL	ft_is_single_quote(char c)
{
	if (c == SINGLE_QUOTE)
		return (True);
	return (False);
}

BOOL	ft_isquote(char c)
{
	if (ft_is_double_quote(c) || ft_is_single_quote(c))
		return (True);
	return (False);
}
