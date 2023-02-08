/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpecci <gpecci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:05:13 by gpecci            #+#    #+#             */
/*   Updated: 2023/02/08 17:05:59 by gpecci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_mine(int fd, char *buf, char *tmp)
{
	int		ret;
	char	*char_tmp;

	ret = 1;
	while (ret != '\0')
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret == -1)
			return (NULL);
		else if (ret == 0)
			break ;
		buf[ret] = '\0';
		if (!tmp)
			tmp = ft_strdup("");
		char_tmp = tmp;
		tmp = ft_strjoin(char_tmp, buf);
		free(char_tmp);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (tmp);
}

static char	*take(char *line)
{
	size_t	i;
	char	*tmp;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == '\0' || line[1] == '\0')
		return (NULL);
	tmp = ft_substr(line, i + 1, ft_strlen(line) - i);
	if (*tmp == '\0')
	{
		free (tmp);
		tmp = NULL;
	}
	line[i + 1] = '\0';
	return (tmp);
}

char	*get_next_line(int fd)
{
	char		*buf;
	char		*line;
	static char	*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = (char *) malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	line = read_mine(fd, buf, tmp);
	free (buf);
	buf = NULL;
	if (!line)
		return (NULL);
	tmp = take(line);
	return (line);
}
