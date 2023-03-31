/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 13:53:32 by vivan-de          #+#    #+#             */
/*   Updated: 2023/03/30 22:25:27 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int get_status_from_line(char *line)
{
	int status;
	int len;
	char *t;

	status = 0;
	len = ft_strlen(line);
	if (len > 5)
	{
		t = line + 5;
		while (*t)
		{
			if (!ft_isdigit(*t))
				return (-1);
			t++;
		}
		t = line + 5;
		skip_whitespace(&t, False);
		status = ft_atoi(t);
	}

	return (status);
}

void	custom_exit(char *line, int status)
{
	ft_printf("exit\n");
	if (status == -1)
		status = get_status_from_line(line);
	if (status == -1)
	{
		ft_printf("exit : numeric argument required : %s\n", line + 4);
		status = 2;
	}
	ctx_free(&g_ctx);
	exit(status);
}
