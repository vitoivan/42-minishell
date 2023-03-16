/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:35:14 by vivan-de          #+#    #+#             */
/*   Updated: 2023/03/16 15:35:14 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "ctx.h"
# include "define.h"

BOOL	is_builtin(char *cmd);
void	pwd(t_ctx **ctx, char *line);
int		cmd_cd(t_ctx **ctx, char *line);
int		cmd_export(t_ctx **ctx, char *line);
void	builtin_main(t_ctx **ctx, char *line);
void	unset(t_ctx **ctx, char *line);
int		validate_if_env_already_exists(t_ctx **ctx, char *name);
void	echo(t_ctx **ctx, char *line);

#endif
