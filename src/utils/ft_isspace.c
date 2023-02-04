/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor.simoes <victor.simoes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 22:02:58 by jv                #+#    #+#             */
/*   Updated: 2023/01/28 16:05:38 by victor.simo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int    ft_isspace(int c)
{
    return (((c >= 9 && c <= 13) || c == 32));
}