/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor.simoes <victor.simoes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 15:21:11 by victor            #+#    #+#             */
/*   Updated: 2023/01/29 10:57:24 by victor.simo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libs/libft/includes/libft.h"
# include "./builtins.h"
# include "./define.h"
# include "./utils.h"
# include "cmd.h"
# include "ctx.h"
# include "pipes.h"
# include "utils.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>

#endif
