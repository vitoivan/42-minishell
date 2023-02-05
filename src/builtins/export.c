/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 13:53:32 by vivan-de          #+#    #+#             */
/*   Updated: 2023/02/05 15:27:15 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	builtin_export(char *name, char *value)
{
	char	*value_to_be_setted;
	size_t	str_len;
	int		return_value;

	value_to_be_setted = NULL;
	return_value = True;
	if (ft_is_double_quote(value[0]))
	{
		str_len = ft_strlen(value) - 1;
		value_to_be_setted = calloc(str_len, sizeof(char));
		if (value_to_be_setted == NULL)
			return (False);
		ft_strlcpy(value_to_be_setted, value + 1, str_len);
	}
	else
		value_to_be_setted = ft_strdup(value);
	if (setenv(name, value_to_be_setted, 1) == -1)
		return_value = False;
	free(value_to_be_setted);
	return (return_value);
}

int	cmd_export(t_ctx **ctx, char *line)
{
	char	*args;
	char	**splitted;
	int		i;
	int		status;

	(void)ctx;
	args = line + 7;
	i = 0;
	splitted = ft_split(args, '=');
	skip_whitespace(&splitted[1], False);
	status = builtin_export(splitted[0], splitted[1]);
	while (splitted[i])
		free(splitted[i++]);
	free(splitted);
	return (status);
}
