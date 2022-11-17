/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <victor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 16:10:04 by victor            #+#    #+#             */
/*   Updated: 2021/08/26 18:42:51 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	ind;

	if (!s || !f)
		return ;
	ind = 0;
	while (s[ind])
	{
		f(ind, s + ind);
		ind++;
	}
}
