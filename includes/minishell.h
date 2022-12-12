/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 15:21:11 by victor            #+#    #+#             */
/*   Updated: 2022/12/10 14:34:19 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libs/libft/includes/libft.h"
# include "./define.h"
# include "./utils.h"
# include <readline/readline.h>
# include <stdio.h>


typedef struct s_node {
  t_lkd_lst *commads;
  byte status;
} c_node;

typedef struct s_cmd {
  c_node *left;
  c_node *right;
  byte   operator;
} CommandTree; 

t_lkd_lst	*ft_tokenizer(char *cmd_line);

#endif
