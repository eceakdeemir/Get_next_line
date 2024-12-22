/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecakdemi <ecakdemi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:31:16 by ecakdemi          #+#    #+#             */
/*   Updated: 2024/12/22 19:54:07 by ecakdemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
int reading_file(int fd, char *buffer)
{
    char *str;
    int readed;
    
    str = malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!str)
        return(1);
    readed = read(fd, str, BUFFER_SIZE);
    if (readed == 0)
        return (-1); 
    str[readed] = '\0';
    buffer = ft_strjoin(buffer, str);
    free(str);
    return (0);
}

char *getting_line(char *buffer, int fd)
{
    char *line;
    int i;

    i = 0;
    int ctrl = 0;
    ctrl = reading_file(fd, buffer);
    if (!buffer)
        return (NULL);
    while (!(ft_strchr(buffer, '\n')) && ctrl == 0)
    {
            ctrl = reading_file(fd, buffer);
    }
    while(ft_strchr(buffer, '\n') && buffer[i] != '\n' && ctrl != -1)
    {
        if (buffer[i] != '\n')
            i++;
    }
    if (ctrl == -1)
        line = ft_substr(buffer, 0, ft_strlen(buffer) + 1);
    else
        line = ft_substr(buffer, 0, i + 2);
    if (!line)
    {
        free(buffer);
        return (NULL);
    }
    return (line);
}

char *remove_line(char *buffer,char *line)
{
    int line_len;
    int buffer_len;
    char *tmp;
    
    line_len = ft_strlen(line);
    buffer_len = ft_strlen(buffer);
    tmp = malloc(sizeof(char) * (buffer_len - line_len));
    if (!tmp)
        return (NULL);
    tmp = ft_substr(buffer, line_len, (buffer_len - line_len));
    free(buffer);
    return (tmp);
}
char *get_next_line(int fd)
{
    static char *buffer;
    char *line;
    if (fd < 0 || BUFFER_SIZE < 0)
        return (NULL);
    if (!buffer)
    {
        buffer = malloc(sizeof(char) * 1);
        if (!buffer)
            return (NULL);
        *buffer = '\0';
    }
    line = getting_line(buffer, fd);
    //printf("\n\nsilinecek line: .%s. boyu: \n\n", line);
    
    buffer = remove_line(buffer, line);
    return (line);
}
