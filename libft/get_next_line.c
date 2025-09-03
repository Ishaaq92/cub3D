/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaladeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 19:37:28 by aaladeok          #+#    #+#             */
/*   Updated: 2024/05/03 19:37:45 by aaladeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*extract_line(char *big_buff)
{
	char	*line;
	int		i;

	i = 0;
	if (!big_buff[i])
		return (NULL);
	while (big_buff[i] && big_buff[i] != '\n')
		i++;
	line = malloc(sizeof(char) * i + 2);
	if (!line)
		return (NULL);
	i = 0;
	while (big_buff[i] && big_buff[i] != '\n')
	{
		line[i] = big_buff[i];
		i++;
	}
	if (big_buff[i] && big_buff[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*get_rem(char *buff)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	while (buff[i] && buff[i] != '\n')
		i++;
	if (!buff[i])
	{
		free(buff);
		return (NULL);
	}
	line = ft_calloc((ft_strlen(buff) - i + 1), sizeof(char));
	i++;
	j = 0;
	while (buff[i])
		line[j++] = buff[i++];
	free(buff);
	return (line);
}

static char	*read_from_file(char *big_buff, int fd)
{
	int		bytes_read;
	char	*small_buff;

	if (!big_buff)
		big_buff = ft_calloc(1, sizeof(char));
	small_buff = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!small_buff)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, small_buff, BUFFER_SIZE);
		if (bytes_read < 1)
			break;
		small_buff[bytes_read] = '\0';
		big_buff = append_buff(big_buff, small_buff);
		if (ft_strchr(big_buff, '\n'))
			break ;
	}
	free(small_buff);
	return (big_buff);
}

char	*get_next_line(int fd)
{
	static char *big_buff;
	char *line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	big_buff = read_from_file(big_buff, fd);
	if (!big_buff)
		return (NULL);
	line = extract_line(big_buff);
	big_buff = get_rem(big_buff);
	return (line);
}
