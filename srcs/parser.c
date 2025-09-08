/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 16:13:42 by isahmed           #+#    #+#             */
/*   Updated: 2025/09/08 17:49:41 by isahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	process_wall_textures(t_data *data, char *line)
{
	static int	count;

	if (count == 4)
		return (1);
	if (ft_strncmp(line, "NO", 2) == 0)
		return (count ++, printf("north textures\n"), 0);
	else if (ft_strncmp(line, "SO", 2) == 0)
		return (count ++, printf("south textures\n"), 0);
	else if (ft_strncmp(line, "EA", 2) == 0)
		return (count ++, printf("east textures\n"), 0);
	else if (ft_strncmp(line, "WE", 2) == 0)
		return (count ++, printf("west textures\n"), 0);
	else
		return (write(2, "Error: Invalid texture\n", 24), ft_quit(data), -1);
}

int	process_other_textures(t_data *data, char *line)
{
	static int	count;

	if (count == 2)
		return (1);
	if (ft_strncmp(line, "F", 1) == 0)
		return (count ++, printf("floor texture\n"), 0);
	else if (ft_strncmp(line, "C", 1) == 0)
		return (count ++, printf("celling texture\n"), 0);
	else
		return (write(2, "Error: Invalid texture\n", 24), ft_quit(data), 1);
}

// int	process_map(t_data *data, char *filename)
// {
// }

int	parser(t_data *data, char *file)
{
	int		fd;
	char	*s;

	s = NULL;
	fd = open(file, 0);
	if (fd < 0)
		return (-1);
	while ((s = get_next_line(fd)))
		if (ft_strncmp(s, "\n", 1) && (process_wall_textures(data, s) != 1 || process_other_textures(data, s) != 1))
			continue;
	// process_map(data, file);
	return (0);
}
