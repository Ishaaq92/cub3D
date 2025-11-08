/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 16:13:42 by isahmed           #+#    #+#             */
/*   Updated: 2025/11/06 19:10:14 by isahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	set_texture_config(t_data *data, char *line, char c)
{
	if (c == 'N')
		data->map.path_to_north = set_path(line);
	else if (c == 'S')
		data->map.path_to_south = set_path(line);
	else if (c == 'E')
		data->map.path_to_east = set_path(line);
	else if (c == 'W')
		data->map.path_to_west = set_path(line);
	else if (c == 'F')
		data->map.floor_rgb = set_rgb(line);
	else if (c == 'C')
		data->map.ceiling_rgb = set_rgb(line);
	else
		return (write(2, "Error: Invalid texture\n", 24), exit(1), 1);
	return (0);
}

/*At the end of the this function can you exit and return at thesame time??*/
static int	process_textures(t_data *data, char *line)
{
	static int	count;

	if (!ft_strncmp(line, "\n", 1))
		return (0);
	else if (count == 6)
		return (1);
	else if (ft_strncmp(line, "NO", 2) == 0 && !data->map.path_to_north)
		return (count++, set_texture_config(data, line, 'N'), 0);
	else if (ft_strncmp(line, "SO", 2) == 0 && !data->map.path_to_south)
		return (count++, set_texture_config(data, line, 'S'), 0);
	else if (ft_strncmp(line, "EA", 2) == 0 && !data->map.path_to_east)
		return (count++, set_texture_config(data, line, 'E'), 0);
	else if (ft_strncmp(line, "WE", 2) == 0 && !data->map.path_to_west)
		return (count++, set_texture_config(data, line, 'W'), 0);
	else if (ft_strncmp(line, "F", 1) == 0 && data->map.floor_rgb == -1)
		return (count++, set_texture_config(data, line, 'F'));
	else if (ft_strncmp(line, "C", 1) == 0 && data->map.ceiling_rgb == -1)
		return (count++, set_texture_config(data, line, 'C'));
	else
		return (write(2, "Error: Invalid texture\n", 24), exit(1), 1);
}

static char	**add_map_line(t_data *data, char *line)
{
	char	**map;
	int		i;

	map = malloc(sizeof(char *) * (data->map.map_height + 2));
	i = -1;
	while (++i < data->map.map_height)
		map[i] = data->map.map[i];
	map[i] = ft_strdup(line);
	data->map.map_height++;
	// printf("Map size: %d\n", data->map.map_height);
	free(data->map.map);
	// print_map(map, data->map.map_height);
	// printf("|%s|\n", line);
	return (map);
}

static int	process_map(t_data *data, char *line)
{
	static int	start;

	if (start == 1 && !ft_strncmp(line, "\n", 1))
		return (2);
	if (!line)
		return (1);
	data->map.map = add_map_line(data, line);
	start = 1;
	return (0);
}

int	parser(t_data *data, char *file)
{
	int		fd;
	char	*s;

	s = NULL;
	fd = open(file, 0);
	if (fd < 0)
		return (1);
	s = get_next_line(fd);
	while (s && process_textures(data, s) == 0)
	{
		free(s);
		s = get_next_line(fd);
	}
	if (process_map(data, s) != 0)
		return (printf("error"), 1);
	s = get_next_line(fd);
	while (s && process_map(data, s) == 0)
	{
		free(s);
		s = get_next_line(fd);
	}
	data->map.map[data->map.map_height] = 0;
	close(fd);
	return (0);
}
