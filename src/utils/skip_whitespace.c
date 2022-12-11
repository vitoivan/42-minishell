/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_whitespace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 10:54:35 by vivan-de          #+#    #+#             */
/*   Updated: 2022/12/11 10:09:50 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	skip_whitespace(char **line, int always_skip_one)
{
	int	count;

	count = 0;
	while (**line == ' ')
	{
		count++;
		(*line)++;
	}
	if (!count && always_skip_one)
		(*line)++;
}
