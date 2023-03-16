/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_builder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 07:50:01 by vivan-de          #+#    #+#             */
/*   Updated: 2023/03/16 15:11:59 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static int	handle_status_var(t_ctx **ctx, t_str_builder_internal *sb,
		const char *s, int size)
{
	if (sb->i + 1 < size && s[sb->i] == '$' && s[sb->i + 1] == '?')
	{
		sb->env_value = ft_itoa((*ctx)->status_code);
		sb->env_len = ft_strlen(sb->env_value);
		ft_strlcpy(sb->new_str + sb->j, sb->env_value, sb->env_len + 1);
		free(sb->env_value);
		sb->j += sb->env_len;
		sb->i += 2;
		return (1);
	}
	return (0);
}

static int	handle_var(t_ctx **ctx, t_str_builder_internal *sb, const char *s)
{
	sb->env_name = ft_strndup(s + sb->ini_pos, sb->i - sb->ini_pos);
	sb->env_value = ctx_get_env(ctx, sb->env_name);
	free(sb->env_name);
	sb->env_len = ft_strlen(sb->env_value);
	if (!sb->env_value)
		if (string_builder_free_everything(NULL, (void *)&sb, "sb_internal"))
			return (-1);
	ft_strlcpy(sb->new_str + sb->j, sb->env_value, sb->env_len + 1);
	free(sb->env_value);
	sb->j += sb->env_len;
	return (1);
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
		if (handle_status_var(ctx, &sb, s, size) == 1)
			continue ;
		else if (s[sb.i] == '$' && !sb.single_quote)
		{
			sb.ini_pos = sb.i + 1;
			while (!ft_isspace(s[sb.i]) && !ft_is_double_quote(s[sb.i])
				&& s[sb.i])
				sb.i++;
			if (handle_var(ctx, &sb, s) == -1)
				return (NULL);
		}
		else
			sb.new_str[sb.j++] = s[sb.i++];
	}
	return (mk_string_builder(sb.new_str, sb.j));
}
