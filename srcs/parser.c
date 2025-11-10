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
		return (write(2, "Error: Invalid texture\n", 24), exit_error(data), 1);
}

static char	**add_map_line(t_data *data, char *line)
{
	char	**map;
	int		i;

	map = malloc(sizeof(char *) * (data->map.map_height + 2));
	if (!map)
		return (NULL);
	i = -1;
	while (++i < data->map.map_height)
		map[i] = data->map.map[i];
	map[i] = ft_strdup(line);
	if (!map[i])
	{
		free(map);
		return (NULL);
	}
	map[i + 1] = NULL;
	data->map.map_height++;
	free(data->map.map);
	return (map);
}

static int	process_map(t_data *data, char *line)
{
	static int	start;

	if (!line)
		return (1);
	if (start == 1 && !ft_strncmp(line, "\n", 1))
		return (2);
	data->map.map = add_map_line(data, line);
	if (!data->map.map)
	{
		free(line);
		return (1);
	}
	start = 1;
	free(line);
	return (0);
}

int	parser(t_data *data, char *file)
{
	int		fd;
	char	*s;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (printf("Unable to open file\n"), exit_error(data), 1);
	s = get_next_line(fd);
	while (s && process_textures(data, s) == 0)
	{
		free(s);
		s = get_next_line(fd);
	}
	if (!s || process_map(data, s) != 0)
	{
		free(s);
		close(fd);
		return (printf("error \n"), exit_error(data), 1);
	}
	s = get_next_line(fd);
	while (s && process_map(data, s) == 0)
		s = get_next_line(fd);
	free(s);
	data->map.map[data->map.map_height] = NULL;
	close(fd);
	return (0);
}
