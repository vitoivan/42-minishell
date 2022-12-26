/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 15:21:11 by victor            #+#    #+#             */
/*   Updated: 2022/12/26 09:51:39 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "ctx.h"
# include "define.h"
# include "minishell.h"

BOOL	get_line_from_terminal(char **line, t_ctx *);
void	free_if_exists(void **data);
void	free_token(void *data);
void	print_lkd_list(t_lkd_lst **list);
void	skip_whitespace(char **line, int always_skip_one);
void	print_terminal(t_ctx *ctx);
char	*get_hostname(void);

#endif
