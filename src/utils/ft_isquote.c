/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isquote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor.simoes <victor.simoes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 14:31:23 by victor.simo       #+#    #+#             */
/*   Updated: 2023/02/04 14:31:26 by victor.simo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

BOOL	ft_isquote(char c)
{
	if (c == SINGLE_QUOTE)
		return (True);
	if (c == DOUBLE_QUOTE)
		return (True);
	return (False);
}
