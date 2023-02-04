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
BOOL		cmd_exec(char *line, char **envp);
BOOL		cmd_try_run(t_ctx **ctx, char *line);
BOOL		await_cmd_run(char *binary_path, char **args, char **envp);

#endif
