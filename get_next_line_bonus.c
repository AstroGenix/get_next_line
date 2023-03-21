/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberehov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 09:22:12 by dberehov          #+#    #+#             */
/*   Updated: 2022/12/06 09:22:13 by dberehov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
• Develop get_next_line() using only one static variable.
• Your get_next_line() can manage multiple file descriptors at the same time.
For example, if you can read from the file descriptors 3, 4 and 5, you should
be able to read from a different fd per call without losing the reading thread
of each file descriptor or returning a line from another fd.
It means that you should be able to call get_next_line() to read from fd 3,
then fd 4, then 5, then once again 3, once again 4, and so forth.
*/

#include "get_next_line_bonus.h"

char	*after_line(char *buffer)
{
	char	*next;
	int		i;
	int		j;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	next = malloc(sizeof(char) * ((ft_strlen(buffer) - i) + 1));
	if (!next)
		return (NULL);
	i++;
	j = 0;
	while (buffer[i])
		next[j++] = buffer[i++];
	next[j] = '\0';
	free(buffer);
	return (next);
}

char	*write_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] && buffer[i] == '\n')
		line[i++] = '\n';
	return (line);
}

char	*join_free(char *buffer, char *buffer_append)
{
	char	*temp_string;

	temp_string = ft_strjoin(buffer, buffer_append);
	free(buffer);
	return (temp_string);
}

char	*read_line(int fd, char *buffer_output)
{
	char	*text_buffer;
	int		bytes_read;

	if (!buffer_output)
		buffer_output = (char *)ft_calloc(1, sizeof(char));
	text_buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!text_buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, text_buffer, BUFFER_SIZE);
		if (bytes_read == -1 || (bytes_read == 0 && buffer_output == NULL))
		{
			free(buffer_output);
			free(text_buffer);
			return (NULL);
		}
		text_buffer[bytes_read] = '\0';
		buffer_output = join_free(buffer_output, text_buffer);
		if (ft_strchr(text_buffer, '\n'))
			break ;
	}
	free(text_buffer);
	return (buffer_output);
}

char	*get_next_line(int fd)
{
	static char	*buffer_stash[FOPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > FOPEN_MAX)
		return (NULL);
	buffer_stash[fd] = read_line(fd, buffer_stash[fd]);
	if (!buffer_stash[fd])
		return (NULL);
	line = write_line(buffer_stash[fd]);
	buffer_stash[fd] = after_line(buffer_stash[fd]);
	return (line);
}

/*
int	main(void)
{
	char	*line;
	int		i;
	int		fd1;
	fd1 = open("text/beescript.txt", O_RDONLY);
	i = 1;
	while (i < 17)
	{
		line = get_next_line(fd1);
		printf("line [%02d]: %s", i, line);
		free(line);
		i++;
	}
	printf("\n");
	close(fd1);
	return (0);
}
*/