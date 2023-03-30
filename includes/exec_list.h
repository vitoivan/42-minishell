/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_list.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 15:21:11 by victor            #+#    #+#             */
/*   Updated: 2023/03/30 08:07:50 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_LIST_H
# define EXEC_LIST_H

# include "define.h"

typedef struct s_handle_exec_list
{
	t_lkd_lst	*list;
	t_lkd_node	*cur;
	t_lkd_node	*prev;
	t_lkd_node	*next;
	t_token		*token;
	t_token		*tmp_token;
	int			i;
	int			**pipes;
	int			filein;
	int			fileout;
}				t_handle_exec_list;

void			create_pipes(t_lkd_lst *list);
void			handle_op_pipe(t_handle_exec_list *s);
void			handle_op_heredoc(t_handle_exec_list *s);
void			handle_op_redirect_in(t_handle_exec_list *s);
void			handle_op_redirect_out(t_handle_exec_list *s);
int				is_redir(t_token_type type);
void			exec_cmds(t_lkd_lst *list);
void			close_pipes(t_lkd_lst *list);
int				need_skip_cmd(t_lkd_node *node);

#endif
