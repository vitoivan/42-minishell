#ifndef BUILTINS_H
# define BUILTINS_H

# include "ctx.h"
# include "define.h"

BOOL	is_builtin(char *cmd);
void	pwd(void);
int		cmd_cd(char *line);
int		cmd_export(t_ctx **ctx, char *line);
#endif
