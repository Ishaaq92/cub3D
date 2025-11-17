/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaladeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 21:35:28 by aaladeok          #+#    #+#             */
/*   Updated: 2025/09/10 21:35:34 by aaladeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// void free_lines(t_line *list)
void	free_entities(t_data *data)
{
	if (data->list)
		free_lines(data->list);
	free_map_entities(data);
	if (data->game)
		free_game_entities(data);
	if (data->player)
		free(data->player);
	data->player = NULL;
	free(data);
	data = NULL;
}

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

int	ft_quit(t_data *data)
{
	if (!data || !data->mlx)
		return (0);
	free_tex_images(data);
	destroy_door_textures(data->mlx, &data->textures.door_arr);
	if (data->img.img)
	{
		mlx_destroy_image(data->mlx, data->img.img);
		data->img.img = NULL;
	}
	if (data->win)
	{
		mlx_destroy_window(data->mlx, data->win);
		data->win = NULL;
	}
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	data->mlx = NULL;
	free_entities(data);
	exit(0);
	return (0);
}

void	print_map(char **map, int map_size)
{
	int	i;

	i = 0;
	if (!map)
		printf("No map here?\n");
	while (i < map_size)
	{
		printf("line[%d]: %s", i, map[i]);
		i++;
	}
	printf("\n");
}

