/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 11:11:51 by victor            #+#    #+#             */
/*   Updated: 2022/12/10 14:03:49 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static size_t	get_line_len(char *line)
{
	size_t	size;

	size = 0;
	while (line[size] && line[size] != '\n' && line[size] != '\0')
		size++;
	return (size);
}

static char	*linedup(char **rest, size_t size)
{
	char	*line;
	size_t	i;

	i = 0;
	line = (char *)malloc(sizeof(char) + size + 1);
	if (!line)
	{
		free(*rest);
		return (NULL);
	}
	while (i <= size)
	{
		line[i] = (*rest)[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*get_line(char **rest)
{
	size_t	size;
	char	*tmp;
	char	*line;

	tmp = NULL;
	size = get_line_len(*rest);
	line = linedup(rest, size);
	if ((*rest)[size] != '\0')
	{
		tmp = ft_strdup(*(rest) + (size + 1));
		free(*rest);
		*rest = tmp;
	}
	else
	{
		free(*rest);
		*rest = NULL;
	}
	if (ft_strlen(line) == 0)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

static char	*return_line(ssize_t bytes_read, char **rest, char **buffer,
		int free_rest)
{
	char	*line;

	free(*buffer);
	if (*rest != NULL)
	{
		if (bytes_read >= 0)
		{
			line = get_line(rest);
			if (free_rest && *rest)
			{
				free(*rest);
				*rest = NULL;
			}
			return (line);
		}
	}
	return (NULL);
}

char	*get_next_line(int fd, int buffer_size, int free_rest)
{
	char		*buffer;
	ssize_t		bytes_read;
	static char	*rest;
	char		*aux;

	buffer = malloc(buffer_size + 1);
	if (!buffer)
		return (NULL);
	bytes_read = read(fd, buffer, buffer_size);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		if (rest == NULL)
			rest = ft_strdup(buffer);
		else
		{
			aux = ft_strjoin(rest, buffer);
			free(rest);
			rest = aux;
		}
		if (ft_strchr(buffer, '\n'))
			break ;
		bytes_read = read(fd, buffer, buffer_size);
	}
	return (return_line(bytes_read, &rest, &buffer, free_rest));
}
