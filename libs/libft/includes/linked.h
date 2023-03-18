/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 20:20:51 by vivan-de          #+#    #+#             */
/*   Updated: 2023/03/18 11:00:43 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINKED_H
# define LINKED_H

typedef struct s_node
{
	void						*content;
	struct s_node				*next;
	struct s_node				*prev;
}								t_lkd_node;

typedef struct s_lkd_lst
{
	t_lkd_node					*head;
	t_lkd_node					*tail;
	unsigned int				size;
}								t_lkd_lst;

typedef unsigned int			t_uint;
typedef unsigned char			t_byte;

typedef void					(*t_lkd_lst_del_node_fn)(void *content);
typedef void					(*t_lkd_lst_each_fn)(void *content, t_uint i);
typedef void					*(*t_lkd_lst_map_fn)(void *content, t_uint i);
typedef int						(*t_lkd_lst_filter_fn)(void *content, t_uint i);

typedef t_lkd_lst_del_node_fn	t_lst_del_fn;
typedef t_lkd_lst_each_fn		t_lst_foreach_fn;
typedef t_lkd_lst_map_fn		t_lst_map_fn;
typedef t_lkd_lst_filter_fn		t_lst_filter_fn;

t_lkd_lst						*lkd_lst_new_list(void);
t_lkd_node						*lkd_lst_new_node(void *content);
void							lkd_lst_add_back(t_lkd_lst **list,
									t_lkd_node *node);
void							lkd_lst_add_front(t_lkd_lst **list,
									t_lkd_node *node);
void							lkd_lst_kill_list(t_lkd_lst **list,
									t_lst_del_fn fn);
t_lkd_lst						*lkd_lst_map(t_lkd_lst **list, t_lst_map_fn fn);
void							lkd_lst_foreach(t_lkd_lst **list,
									t_lst_foreach_fn fn);
t_lkd_lst						*lkd_lst_filter(t_lkd_lst **list,
									t_lst_filter_fn fn);
void							lkd_lst_pop_first(t_lkd_lst **list,
									t_lst_del_fn fn);
void							lkd_lst_pop_last(t_lkd_lst **list,
									t_lst_del_fn fn);
void							lkd_lst_pop_at(t_lkd_lst **lst, t_uint i,
									t_lst_del_fn fn);

#endif