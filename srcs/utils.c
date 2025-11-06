/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 16:13:13 by isahmed           #+#    #+#             */
/*   Updated: 2025/10/09 17:34:09 by isahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_crosshair(t_data *data)
{
	int	x;
	int	y;

	x = WIDTH / 2 - 9;
	while (++x < (WIDTH / 2 + 10))
		pixel_put(x, HEIGHT / 2, &data->img, 0xFFFFFF);
	y = HEIGHT / 2 - 9;
	while (++y < (HEIGHT / 2 + 10))
		pixel_put(WIDTH / 2, y, &data->img, 0xFFFFFF);
}

char	*set_path(char *line)
{
	char	*path;
	char	*tmp1;

	tmp1 = ft_strtrim(ft_strchr(line, '.'), "\n ");
	path = ft_strdup(tmp1);
	if (access(path, 0) == -1)
		return (exit(1), NULL);
	free(tmp1);
	return (path);
}

int	ft_quit(t_data *data)
{
	if (!data || !data->mlx)
		return (-1);
	if (data->img.img)
		mlx_destroy_image(data->mlx, data->img.img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	free(data->map.path_to_east);
	free(data->map.path_to_north);
	free(data->map.path_to_west);
	free(data->map.path_to_south);
	exit(0);
	return (0);
}

int	set_rgb(char *line)
{
	int	colour;
	int	rgb;
	int	i;

	i = 0;
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
	return (rgb);
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
