/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_if_exists.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 10:54:35 by vivan-de          #+#    #+#             */
/*   Updated: 2022/11/19 16:22:48 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_if_exists(void **data)
{
	if (*data)
		free(*data);
}

void free_token(void *data)
{
  if (data)
    free(data);
}
