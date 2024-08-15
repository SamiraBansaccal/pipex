/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbansacc <sbansacc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 23:34:14 by sbansacc          #+#    #+#             */
/*   Updated: 2024/03/30 15:38:21 by sbansacc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*join_and_free(char *old_stash, char *buf)
{
	char	*new_stash;

	if (!old_stash || !buf)
		return (NULL);
	new_stash = ft_strjoin(old_stash, buf);
	free(old_stash);
	return (new_stash);
}

char	*read_and_stash(int fd, char *stash)
{
	char	*buf;
	int		byte_read;

	if (!stash)
		stash = ft_calloc(1, sizeof(char));
	if (!stash)
		return (NULL);
	buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buf)
		return (free_stash(&stash), NULL);
	byte_read = 1;
	while (byte_read > 0)
	{
		byte_read = read(fd, buf, BUFFER_SIZE);
		if (byte_read < 0)
			return (free(buf), free_stash(&stash), NULL);
		buf[byte_read] = 0;
		stash = join_and_free(stash, buf);
		if (!stash)
			return (free(buf), NULL);
		if (found_new_line(stash))
			break ;
	}
	return (free(buf), stash);
}

char	*clean_stash(char *stash)
{
	int		i;
	int		j;
	char	*new_stash;

	i = 0;
	j = 0;
	if (!stash)
		return (free_stash(&stash), NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
		return (free(stash), NULL);
	new_stash = ft_calloc((ft_strlen(stash) - i + 1), sizeof(char));
	if (!new_stash)
		return (free_stash(&stash));
	i++;
	j = 0;
	while (stash[i + j])
	{
		new_stash[j] = stash[i + j];
		j++;
	}
	free(stash);
	return (new_stash);
}

char	*ft_get_line(char *stash)
{
	char	*line;
	int		i;

	i = 0;
	if (!stash || !stash[i])
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	line = ft_calloc(i + 1, sizeof(char));
	if (!line)
		return (0);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] || stash[i] == '\n')
		line[i] = stash[i];
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT32_MAX
		|| read(fd, 0, 0) < 0)
	{
		if (stash)
			free_stash(&stash);
		stash = 0;
		return (NULL);
	}
	if (stash && found_new_line(stash) == 1)
	{
		line = ft_get_line(stash);
		stash = clean_stash(stash);
	}
	else
	{
		stash = read_and_stash(fd, stash);
		line = ft_get_line(stash);
		stash = clean_stash(stash);
	}
	if (!line)
		return (free_stash(&stash), NULL);
	return (line);
}
