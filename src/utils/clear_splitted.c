/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_splitted.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor.simoes <victor.simoes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 15:37:22 by jv                #+#    #+#             */
/*   Updated: 2023/02/20 15:53:23 by victor.simo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	clear_splitted(char ***splitted)
{
	int		i;
	char	**tmp;

	i = -1;
	tmp = *splitted;
	while (tmp[++i])
		if (tmp[i])
			free(tmp[i]);
	if (*splitted)
		free(*splitted);
}
