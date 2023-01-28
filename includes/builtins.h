#ifndef BUILTINS_H
# define BUILTINS_H

# include "define.h"

BOOL	is_builtin(char *cmd);
void pwd(void);
int cd(char *path);
int builtin_export(char *name, char *value);
#endif
