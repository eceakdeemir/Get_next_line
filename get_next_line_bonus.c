/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecakdemi <ecakdemi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 14:25:40 by ecakdemi          #+#    #+#             */
/*   Updated: 2024/12/25 15:24:57 by ecakdemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*remove_line(char *buffer, char *line)
{
	char	*tmp;
	int		len;

	len = ft_strlen(line);
	tmp = ft_substr(buffer, len, ft_strlen(buffer) - len);
	free(buffer);
	return (tmp);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*result;

	if (!s1 || !s2)
		return (0);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = (char *)malloc(len1 + len2 + 1);
	if (!result)
		return (0);
	ft_memcpy(result, s1, len1);
	ft_memcpy(result + len1, s2, len2);
	free(s1);
	result[len1 + len2] = '\0';
	return (result);
}

char	*reading_loop(char *buffer, int fd)
{
	int		readed;
	char	*reading;

	readed = 1;
	while (ft_strchr(buffer, '\n') == -1 && readed != 0)
	{
		reading = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!reading)
			return (NULL);
		readed = read(fd, reading, BUFFER_SIZE);
		if (readed < 0)
		{
			free(reading);
			free(buffer);
			return (NULL);
		}
		reading[readed] = '\0';
		buffer = ft_strjoin(buffer, reading);
		free(reading);
	}
	return (buffer);
}

char	*read_and_fill_line(int fd, char **buffer)
{
	char	*line;
	int		i;

	*buffer = reading_loop(*buffer, fd);
	if (!*buffer)
		return (NULL);
	if (!**buffer)
	{
		free(*buffer);
		*buffer = NULL;
		return (NULL);
	}
	i = ft_strchr(*buffer, '\n');
	if (i == -1)
		i = ft_strlen(*buffer);
	if ((*buffer)[i] == '\n')
		i++;
	line = ft_substr(*buffer, 0, i);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer[8192];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer[fd])
	{
		buffer[fd] = malloc(sizeof(char) * 1);
		if (!buffer[fd])
			return (NULL);
		buffer[fd][0] = '\0';
	}
	line = read_and_fill_line(fd, &buffer[fd]);
	if (!line)
		return (NULL);
	buffer[fd] = remove_line(buffer[fd], line);
	return (line);
}
