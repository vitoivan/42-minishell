#ifndef BUILTINS_H
# define BUILTINS_H

# include "ctx.h"
# include "define.h"

BOOL	is_builtin(char *cmd);
void	pwd(t_ctx **ctx, char *line);
int		cmd_cd(char *line);
int		cmd_export(t_ctx **ctx, char *line);
void	builtin_main(t_ctx **ctx, char *line);
void	unset(t_ctx **ctx, char *line);
int		validate_if_env_already_exists(t_ctx **ctx, char *name);

#endif
