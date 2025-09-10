/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 16:13:42 by isahmed           #+#    #+#             */
/*   Updated: 2025/09/10 15:18:08 by isahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	set_rgb(char *line)
{
	int		colour;
	int		rgb;
	int		i;

	i = 0;
	while (!ft_isdigit(line[i]))
		i ++;
	colour = ft_atoi(&line[i]);
	rgb = (colour << 16);
	line = ft_strchr(line, ',') + 1;
	colour = ft_atoi(line);
	rgb = rgb + (colour << 8);
	line = ft_strchr(line, ',') + 1;
	colour = ft_atoi(line);
	rgb = rgb + colour;
	return (rgb);
}

int	set_texture_config(t_data *data, char *line, char c)
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

int process_textures(t_data *data, char *line)
{
  static int count;

  if (count == 6)
	return (1);
  if (ft_strncmp(line, "NO", 2) == 0)
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
	return (write(2, "Error: Invalid texture\n", 24), ft_quit(data), -1);
}

int	process_map(t_data *data, char *line)
{
	static int	index = 0;

	if (!line || !data->map.map)
		return (1);
	// printf("-%s\n", (char *)&config);
	data->map.map[index] = ft_strdup(line);
	return (0);
}

int parser(t_data *data, char *file)
{
	int fd;
	char *s;

	s = NULL;
	fd = open(file, 0);
	if (fd < 0)
		return (-1);
	while ((s = get_next_line(fd)))
	{
		if (!ft_strncmp(s, "\n", 1) || process_textures(data, s) == 0)
			continue;
		else if (process_textures(data, s) == 1)
		{
			// printf("%s", s);
			// while ((s = get_next_line(fd)) && !ft_strncmp(s, "\n", 1))
			// 	continue;
			break;
		}
	}
	if (process_map(data, s) == 1)
		printf("error");
	// while ((s = get_next_line(fd)))
	// 	process_map(data, s);
	return (0);
}
