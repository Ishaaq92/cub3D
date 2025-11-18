/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 16:13:13 by isahmed           #+#    #+#             */
/*   Updated: 2025/11/10 19:14:39 by isahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	free_colours(char **colours)
{
	int	i;

	i = -1;
	while (colours[++i])
		free(colours[i]);
	free(colours);
}

static int	is_whitespace(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

int	validate_colours(t_data *data, char *line)
{
	char	**colours;
	int		i;
	int		j;

	colours = ft_split(++line, ',');
	i = -1;
	while (colours[++i])
		continue ;
	if (i != 3)
		return (free_colours(colours), exit_error(data,
				"Invalid texture color"));
	i = -1;
	while (colours[++i])
	{
		j = -1;
		while (colours[i][++j])
			if (!ft_isdigit(colours[i][j]) && !(is_whitespace(colours[i][j])))
				return (free_colours(colours), exit_error(data,
						"Invalid texture color"));
	}
	free_colours(colours);
	return (0);
}

void	set_rgb(t_data *data, char *line, int *map_color, int *flag)
{
	int	colour;
	int	rgb;
	int	i;

	i = 0;
	if (*flag)
		exit_error(data, "Double texture rgb.");
	validate_colours(data, line);
	while (!ft_isdigit(line[i]))
		i++;
	colour = ft_atoi(&line[i]);
	rgb = (colour << 16);
	line = ft_strchr(line, ',') + 1;
	colour = ft_atoi(line);
	rgb = rgb + (colour << 8);
	line = ft_strchr(line, ',') + 1;
	colour = ft_atoi(line);
	rgb = rgb + colour;
	*map_color = rgb;
	*flag = 1;
}

int	check_allowed_chars(char **map, int map_size)
{
	int			i;
	int			j;
	const char	*expected_chars = "10NSEWDG ";

	i = 0;
	while (i < map_size)
	{
		j = 0;
		while (map[i][j])
		{
			if ((map[i][j] != '\n') && !ft_strchr(expected_chars, map[i][j]))
			{
				printf("Map error at row %d, col %d.\n", i, j);
				return (1);
			}
			++j;
		}
		++i;
	}
	return (0);
}
