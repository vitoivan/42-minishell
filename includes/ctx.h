/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 15:21:11 by victor            #+#    #+#             */
/*   Updated: 2022/12/26 15:46:12 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CTX_H
# define CTX_H

typedef struct s_ctx
{
	char	*user;
	char	*path;
	char	*hostname;
}			t_ctx;

t_ctx		*ctx_init(void);
void		ctx_free(t_ctx **ctx);

# define USER_SIZE 1024
# define PATH_SIZE 4096
# define HOSTNAME_SIZE 256

#endif
