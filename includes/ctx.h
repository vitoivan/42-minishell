/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor.simoes <victor.simoes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 15:21:11 by victor            #+#    #+#             */
/*   Updated: 2023/01/29 10:57:19 by victor.simo      ###   ########.fr       */
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
void		ctx_update(t_ctx **ctx);

# define USER_SIZE 1024
# define PATH_SIZE 4096
# define HOSTNAME_SIZE 256

#endif
