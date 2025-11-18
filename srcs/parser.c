/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaladeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 15:12:10 by aaladeok          #+#    #+#             */
/*   Updated: 2025/11/05 15:12:14 by aaladeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	is_map_line(char *line)
{
	char	*s;

	if (!line)
		return (0);
	s = skip_whitespace(line);
	if (*s == '1' || *s == '0' || *s == ' ')
		return (1);
	return (0);
}

void	parse_map(t_line *list, t_data *data)
{
	char	*line;

	while (list)
	{
		line = list->str;
		data->map.map = add_map_line(data, line);
		list = list->next;
	}
}

static int	handle_header_line(t_data *data, char *line)
{
	if (starts_with(line, "NO"))
		set_path(data, line, &data->map.path_to_north,
			&data->map.flags.has_north);
	else if (starts_with(line, "SO"))
		set_path(data, line, &data->map.path_to_south,
			&data->map.flags.has_south);
	else if (starts_with(line, "EA"))
		set_path(data, line, &data->map.path_to_east,
			&data->map.flags.has_east);
	else if (starts_with(line, "WE"))
		set_path(data, line, &data->map.path_to_west,
			&data->map.flags.has_west);
	else if (starts_with(line, "F"))
		set_rgb(data, line, &data->map.floor_rgb, &data->map.flags.has_floor);
	else if (starts_with(line, "C"))
		set_rgb(data, line, &data->map.ceiling_rgb,
			&data->map.flags.has_ceiling);
	else
		return (0);
	return (1);
}

static t_line	*skip_empty(t_line *node)
{
	while (node && !ft_strncmp(node->str, "\n", 1))
		node = node->next;
	return (node);
}

void	parse_file(t_data *data, t_line *list)
{
	t_line	*cur;
	char	*line;

	cur = skip_empty(list);
	while (cur)
	{
		line = cur->str;
		if (is_map_line(line))
			break ;
		if (!handle_header_line(data, line))
			exit_error(data, line);
		cur = skip_empty(cur->next);
	}
	parse_map(cur, data);
}
