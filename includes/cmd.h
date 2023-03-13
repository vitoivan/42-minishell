#ifndef CMD_H
# define CMD_H

# include "./define.h"

typedef struct s_cmd
{
	char	*cmd;
	char	**args;
}			t_cmd;

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
