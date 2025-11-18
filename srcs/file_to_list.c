/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_to_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaladeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 21:35:28 by aaladeok          #+#    #+#             */
/*   Updated: 2025/09/10 21:35:34 by aaladeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	set_path(t_data *data, char *line, char **dest, int *flag)
{
	char	*tmp;
	char	*path;

	if (*flag)
		exit_error(data, "Double texture path.");
	if (!texture_path_complete(&data->map.flags))
		exit_error(data, "Excess texture paths...exiting.");
	tmp = ft_strchr(line, '.');
	if (!tmp)
		exit_error(data, "Empty texture path.");
	tmp = ft_strtrim(tmp, "\n ");
	path = ft_strdup(tmp);
	free(tmp);
	if (access(path, F_OK) == -1)
	{
		printf("Issues with this texture path: %s\n", path);
		free(path);
		exit_error(data, "Unable to open texture path.");
	}
	*dest = path;
	*flag = 1;
}

char	**add_map_line(t_data *data, char *line)
{
	char	**new_map;
	int		i;

	new_map = malloc(sizeof(char *) * (data->map.map_height + 2));
	if (!new_map)
		return (NULL);
	i = -1;
	while (++i < data->map.map_height)
		new_map[i] = data->map.map[i];
	new_map[i] = ft_strdup(line);
	if (!new_map[i])
	{
		free(new_map);
		return (NULL);
	}
	new_map[i + 1] = NULL;
	if (data->map.map)
		free(data->map.map);
	data->map.map_height++;
	return (new_map);
}

int	append_line(t_line **list, char *str)
{
	t_line	*new;
	t_line	*tmp;

	new = malloc(sizeof(t_line));
	if (!new)
		return (1);
	new->str = ft_strdup(str);
	new->next = NULL;
	if (!*list)
	{
		*list = new;
		return (0);
	}
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (0);
}

// Read entire file into list
t_line	*read_file(int fd)
{
	t_line	*list;
	char	*line;

	list = NULL;
	line = get_next_line(fd);
	while (line)
	{
		append_line(&list, line);
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	return (list);
}

int	parser(t_data *data, char *filename)
{
	int	fd;

	ft_bzero(&data->map.flags, sizeof(t_tex_flags));
	if (!file_extension_valid(filename))
		return (exit_error(data, "file must have a .cub extension."));
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (exit_error(data, "Unable to open file"));
	data->list = read_file(fd);
	close(fd);
	parse_file(data, data->list);
	validate_input(data);
	return (0);
}
