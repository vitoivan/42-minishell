/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_builder_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 07:50:01 by vivan-de          #+#    #+#             */
/*   Updated: 2023/03/16 15:07:53 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	string_builder_free_everything(void *rs, void *sb, const char *want_free)
{
	t_str_builder_real_size_internal	*aux_rs;

	(void)sb;
	aux_rs = (t_str_builder_real_size_internal *)rs;
	if (!ft_strcmp(want_free, "real_str"))
	{
		if (aux_rs)
			free(aux_rs->env_name);
		return (1);
	}
	if (!ft_strcmp(want_free, "sb_internal"))
		return (1);
	return (0);
}

static void	init_rs(t_str_builder_real_size_internal *rs)
{
	rs->value_size = 0;
	rs->env_name_len = 0;
	rs->env_value_len = 0;
	rs->i = 0;
	rs->aux = 0;
}

static int	handle_env_value(t_ctx **ctx, t_str_builder_real_size_internal *rs)
{
	if (ft_strncmp(rs->env_name, "?", 2) == 0)
		rs->env_value = ft_itoa((*ctx)->status_code);
	else
		rs->env_value = ctx_get_env(ctx, rs->env_name);
	if (rs->env_value == NULL)
		return (string_builder_free_everything((void *)rs, NULL, "real_str")
			- 2);
	return (1);
}

static void	append_lengths(t_str_builder_real_size_internal *rs)
{
	rs->env_name_len += ft_strlen(rs->env_name);
	rs->env_value_len += ft_strlen(rs->env_value);
	free(rs->env_value);
	free(rs->env_name);
}

int	real_string_size(t_ctx **ctx, char *s, int size)
{
	t_str_builder_real_size_internal	rs;

	init_rs(&rs);
	while (rs.i < size)
	{
		if (s[rs.i] == '$')
		{
			rs.i += skip_whitespace(&s, False);
			if (rs.i >= size)
				return (string_builder_free_everything((void *)&rs, NULL,
						"real_str") - 2);
			rs.ini_pos = rs.i + 1;
			while (!ft_isspace(s[rs.i]) && !ft_isquote(s[rs.i]) && s[rs.i])
				rs.i++;
			rs.env_name = ft_strndup(s + rs.ini_pos, rs.i - rs.ini_pos);
			rs.aux = handle_env_value(ctx, &rs);
			if (rs.aux != 1)
				return (rs.aux);
			append_lengths(&rs);
		}
		else
			rs.i++;
	}
	return (size - rs.env_name_len + rs.env_value_len + 1);
}
