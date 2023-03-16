/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:34:52 by vivan-de          #+#    #+#             */
/*   Updated: 2023/03/16 15:34:52 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

# include "./define.h"

typedef struct s_await_cmd_run_props
{
	int		status;
	int		parent_write_pipe[2];
	int		child_write_pipe[2];
	int		read_ret;
	char	buffer[PIPE_BUFFER];
	char	**env;
}			t_await_cmd_run_props;

char		*get_cmd_binary_path(char *cmd);
char		**get_path(void);
BOOL		cmd_is_valid(char *cmd);
BOOL		cmd_exec(char *line, t_ctx **ctx);
BOOL		cmd_try_run(t_ctx **ctx, char *line);
BOOL		await_cmd_run(t_ctx **ctx, char *binary_path, char **args);
void		cmd_get_args(char ***args, char *line);
void		cmd_free_args(char ***args);
char		*get_cmd_from_line(char *line);
void		cmd_redirect(char *filepath, int mode, t_ctx **ctx);

#endif
