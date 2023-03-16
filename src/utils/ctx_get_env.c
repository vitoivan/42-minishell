/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx_get_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 14:43:11 by vivan-de          #+#    #+#             */
/*   Updated: 2023/03/16 13:46:16 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ctx_get_env(t_ctx **ctx, char *env_name)
{
	unsigned int	i;
	char			*env_value;
	char			**data;
	t_lkd_node		*node;

	i = 0;
	env_value = NULL;
	node = (*ctx)->env->head;
	while (i < (*ctx)->env->size)
	{
		data = ft_split((char *)node->content, '=');
		if (ft_strcmp(data[0], env_name) == 0)
		{
			env_value = ft_strdup(data[1]);
			clear_splitted(&data);
			break ;
		}
		node = node->next;
		clear_splitted(&data);
		i++;
	}
	return (env_value);
}
