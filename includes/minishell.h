/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 15:21:11 by victor            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/03/12 14:53:14 by jv               ###   ########.fr       */
=======
/*   Updated: 2023/03/12 19:56:23 by vivan-de         ###   ########.fr       */
>>>>>>> 6256aaa (feat: signals)
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
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>

t_ctx	*g_ctx;

#endif
