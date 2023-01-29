/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor.simoes <victor.simoes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 15:21:11 by victor            #+#    #+#             */
/*   Updated: 2023/01/29 10:57:28 by victor.simo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPES_H
# define PIPES_H

# include "ctx.h"

void	pipe_close_read(int pipefd[2]);
void	pipe_close_write(int pipefd[2]);
void	pipe_close_both(int pipefd[2]);

#endif
