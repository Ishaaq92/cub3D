/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 16:13:42 by isahmed           #+#    #+#             */
/*   Updated: 2025/09/10 20:21:01 by isahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	set_texture_config(t_data *data, char *line, char c)
{
	if (c == 'N')
		data->map.path_to_NO = ft_strdup(ft_strchr(line, '.'));
	else if (c == 'S')
		data->map.path_to_SO = ft_strdup(ft_strchr(line, '.'));
	else if (c == 'E')
		data->map.path_to_EA = ft_strdup(ft_strchr(line, '.'));
	else if (c == 'W')
		data->map.path_to_WE = ft_strdup(ft_strchr(line, '.'));
	else if (c == 'F')
		data->map.floor_rgb = set_rgb(line);
	else if (c == 'C')
		data->map.celling_rgb = set_rgb(line);
	else
		return (1);
	return (0);
}

static	int process_textures(t_data *data, char *line)
{
	static int count;

	if (!ft_strncmp(line, "\n", 1))
		return (0);
	else if (count == 6)
		return (1);
	else if (ft_strncmp(line, "NO", 2) == 0)
		return (count++, set_texture_config(data, line, 'N'),("north textures\n"), 0);
	else if (ft_strncmp(line, "SO", 2) == 0)
		return (count++, set_texture_config(data, line, 'S'), printf("south textures\n"), 0);
	else if (ft_strncmp(line, "EA", 2) == 0)
		return (count++, set_texture_config(data, line, 'E'), printf("east textures\n"), 0);
	else if (ft_strncmp(line, "WE", 2) == 0)
		return (count++, set_texture_config(data, line, 'W'), printf("west textures\n"), 0);
	else if (ft_strncmp(line, "F", 1) == 0)
		return (count++, printf("floor texture\n"), set_texture_config(data, line, 'F'));
	else if (ft_strncmp(line, "C", 1) == 0)
		return (count++, printf("celling texture\n"), set_texture_config(data, line, 'C'));
	else
		return (write(2, "Error: Invalid texture\n", 24), exit(1), 1);
}

static char	**add_map_line(t_data *data, char **line)
{
	char	**map;
	int		i;
	
	if (data->map.map_size == 0)
	{
		map = malloc(sizeof(char *) * 1);
		map[0] = *line;
		data->map.map_size++;
		return (map);
	}
	map = malloc(sizeof(char *) * (data->map.map_size + 1));
	i = -1;
	while (++i < data->map.map_size)
		map[i] = data->map.map[i];
	map[i] = ft_strdup(*line);
	data->map.map_size++;
	free(data->map.map);
	return (map);
}

static int	process_map(t_data *data, char *line)
{
	static int	start;

	if (start == 1 && !ft_strncmp(line, "\n", 1))
		return (2);
	if (!line)
		return (1);
	data->map.map = add_map_line(data, &line);
	start = 1;
	return (0);
}

int parser(t_data *data, char *file)
{
	int fd;
	char *s;

	s = NULL;
	fd = open(file, 0);
	if (fd < 0)
		return (1);
	data->map.map_size = 0;
	while ((s = get_next_line(fd)))
		if (process_textures(data, s) == 1)
			break;
	if (process_map(data, s) != 0)
		printf("error");
	while ((s = get_next_line(fd)))
		if (process_map(data, s) != 0)
			printf("error");
	return (0);
}
