/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor.simoes <victor.simoes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 15:21:11 by victor            #+#    #+#             */
/*   Updated: 2023/04/01 11:29:03 by victor.simo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CTX_H
# define CTX_H

# include "./define.h"

typedef struct s_ctx
{
	char		*user;
	char		*path;
	char		*hostname;
	int			pid;
	int			*pids;
	int			status_code;
	int			argc;
	t_lkd_lst	*env;
	char		**env_vector;
	char		**argv;
	char		*buffer;
	t_lkd_lst	*cmdlist;

}				t_ctx;

t_ctx			*ctx_init(int argc, char **argv, char **envp);
void			ctx_free(t_ctx **ctx);
void			ctx_update(t_ctx **ctx);
void			ctx_populate_buffer(t_ctx **ctx, char *data);
t_lkd_lst		*ctx_parse_env(char **envp);
char			**parse_ldk_lst_to_char_array(t_lkd_lst *list);

# define USER_SIZE 1024
# define PATH_SIZE 4096
# define HOSTNAME_SIZE 256
# define PIPE_BUFFER 500000

#endif
