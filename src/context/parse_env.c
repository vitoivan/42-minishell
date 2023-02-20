/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor.simoes <victor.simoes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 13:53:32 by vivan-de          #+#    #+#             */
/*   Updated: 2023/02/20 12:32:46 by victor.simo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_lkd_lst	*ctx_parse_env(char **envp)
{
	t_lkd_lst	*list;
	int			i;

	i = -1;
	list = lkd_lst_new_list();
	while (envp[++i])
		lkd_lst_add_back(&list, lkd_lst_new_node(ft_strdup(envp[i])));
	return (list);
}

char	**parse_ldk_lst_to_char_array(t_lkd_lst *list)
{
	char			**envp;
	unsigned int	i;
	t_lkd_node		*node;

	i = 0;
	envp = ft_calloc(list->size + 1, sizeof(char *));
	node = list->head;
	while (i < list->size)
	{
		envp[i] = ft_strdup((char *)node->content);
		node = node->next;
		i++;
	}
	return (envp);
}
