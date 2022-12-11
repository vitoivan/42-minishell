/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 15:21:11 by victor            #+#    #+#             */
/*   Updated: 2022/12/10 15:45:30 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

# define BOOL int

enum	e_bool
{
	False = 0,
	True = 1
};

enum	e_erros
{
	UNQUOTED_STRING_ERROR,
	MEMORY_ALLOC_ERROR
};

# define BUFFER_SIZE 4096
# define uint unsigned int
# define byte unsigned char
# define SINGLE_QUOTE 39
# define DOUBLE_QUOTE 34

#endif
