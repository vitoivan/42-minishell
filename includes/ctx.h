/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor.simoes <victor.simoes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 15:21:11 by victor            #+#    #+#             */
/*   Updated: 2023/02/04 20:38:00 by victor.simo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CTX_H
# define CTX_H

# include "./define.h"

typedef struct s_ctx
{
	char	*user;
	char	*path;
	char	*hostname;
	int		argc;
	char	**env;
	char	**argv;
	AstNode	*root_cmd;
}			t_ctx;

t_ctx		*ctx_init(int argc, char **argv, char **envp);
void		ctx_free(t_ctx **ctx);
void		ctx_update(t_ctx **ctx);

# define USER_SIZE 1024
# define PATH_SIZE 4096
# define HOSTNAME_SIZE 256

#endif
