/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_builder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 07:50:01 by vivan-de          #+#    #+#             */
/*   Updated: 2023/03/12 15:09:15 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	free_everything(void *rs, void *sb, const char *want_free)
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

static int	real_string_size(t_ctx **ctx, char *s, int size)
{
	t_str_builder_real_size_internal	rs;

	rs.value_size = 0;
	rs.env_name_len = 0;
	rs.env_value_len = 0;
	rs.i = 0;
	while (rs.i < size)
	{
		if (s[rs.i] == '$')
		{
			rs.i += skip_whitespace(&s, False);
			if (rs.i >= size)
				return (free_everything((void *)&rs, NULL, "real_str") - 2);
			rs.ini_pos = rs.i + 1;
			while (!ft_isspace(s[rs.i]) && !ft_isquote(s[rs.i]) && s[rs.i])
				rs.i++;
			rs.env_name = ft_strndup(s + rs.ini_pos, rs.i - rs.ini_pos);
			if (ft_strncmp(rs.env_name, "?", 2) == 0)
				rs.env_value = ft_itoa((*ctx)->status_code);
			else
				rs.env_value = ctx_get_env(ctx, rs.env_name);
			if (rs.env_value == NULL)
				return (free_everything((void *)&rs,
										NULL,
										"real_str") -
						2);
			rs.env_name_len += ft_strlen(rs.env_name);
			rs.env_value_len += ft_strlen(rs.env_value);
			free(rs.env_value);
			free(rs.env_name);
		}
		else
			rs.i++;
	}
	return (size - rs.env_name_len + rs.env_value_len + 1);
}
static t_str_builder	*mk_string_builder(char *s, int size)
{
	t_str_builder	*sb;

	sb = (t_str_builder *)ft_calloc(1, sizeof(t_str_builder));
	if (!sb)
		return (NULL);
	sb->size = size;
	sb->start = s;
	return (sb);
}

static BOOL	populate_str_builder_internal(t_ctx **ctx,
											t_str_builder_internal *sb,
											const char *s,
											int size)
{
	sb->i = 0;
	sb->j = 0;
	sb->single_quote = 0;
	sb->real_size = real_string_size(ctx, (char *)s, size);
	if (sb->real_size < 0)
		return (False);
	sb->new_str = ft_calloc(sb->real_size + 1, sizeof(char));
	if (!sb->new_str)
		return (False);
	return (True);
}

t_str_builder	*string_builder(t_ctx **ctx, const char *s, int size)
{
	t_str_builder_internal	sb;

	if (!populate_str_builder_internal(ctx, &sb, s, size))
		return (NULL);
	while (sb.i < size)
	{
		if (ft_is_single_quote(s[sb.i]))
			sb.single_quote = !sb.single_quote;
		if (sb.i + 1 < size && s[sb.i] == '$' && s[sb.i + 1] == '?')
		{
			sb.env_value = ft_itoa((*ctx)->status_code);
			sb.env_len = ft_strlen(sb.env_value);
			ft_strlcpy(sb.new_str + sb.j, sb.env_value, sb.env_len + 1);
			free(sb.env_value);
			sb.j += sb.env_len;
			sb.i += 2;
		}
		else if (s[sb.i] == '$' && !sb.single_quote)
		{
			sb.ini_pos = sb.i + 1;
			while (!ft_isspace(s[sb.i]) && !ft_is_double_quote(s[sb.i]))
				sb.i++;
			sb.env_name = ft_strndup(s + sb.ini_pos, sb.i - sb.ini_pos);
			sb.env_value = ctx_get_env(ctx, sb.env_name);
			ft_printf("env_name: %s, env_value %s\n", sb.env_name,
					sb.env_value);
			free(sb.env_name);
			sb.env_len = ft_strlen(sb.env_value);
			if (!sb.env_value)
				if (free_everything(NULL, (void *)&sb, "sb_internal"))
					return (NULL);
			ft_strlcpy(sb.new_str + sb.j, sb.env_value, sb.env_len + 1);
			free(sb.env_value);
			sb.j += sb.env_len;
		}
		else
			sb.new_str[sb.j++] = s[sb.i++];
	}
	return (mk_string_builder(sb.new_str, sb.j));
}
