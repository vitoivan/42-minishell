/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 15:21:11 by victor            #+#    #+#             */
/*   Updated: 2022/12/10 15:15:27 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

BOOL	get_line_from_terminal(char **line);
void	free_if_exists(void **data);
void	free_token(void *data);
void	print_lkd_list(t_lkd_lst **list);

#endif
