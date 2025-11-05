/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaladeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 15:11:27 by aaladeok          #+#    #+#             */
/*   Updated: 2025/11/05 15:11:29 by aaladeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_minimap_tile(t_data *data, int x, int y, int color)
{
	int	i;
	int	j;
	int	px;
	int	py;

	i = -1;
	while (++i < MMAP_SCALE)
	{
		j = -1;
		while (++j < MMAP_SCALE)
		{
			px = MMAP_MARGIN + x * MMAP_SCALE + j;
			py = MMAP_MARGIN + y * MMAP_SCALE + i;
			pixel_put(px, py, &data->img, color);
		}
	}
}

// Will use this for dynamic map..
// px = MMAP_MARGIN + MINIMAP_CENTER;
// py = MMAP_MARGIN + MINIMAP_CENTER;
void	draw_minimap_player(t_data *data)
{
	int	i;
	int	j;
	int	px;
	int	py;

	px = MMAP_MARGIN + (int)(data->player->x * MMAP_SCALE);
	py = MMAP_MARGIN + (int)(data->player->y * MMAP_SCALE);
	i = -2;
	while (++i <= 2)
	{
		j = -2;
		while (++j <= 2)
			pixel_put(px + j, py + i, &data->img, MMAP_PLAYER_COLOR);
	}
}

void	draw_minimap(t_data *data)
{
	int		x;
	int		y;
	char	**map;

	map = data->map.map;
	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] == '1')
				draw_minimap_tile(data, x, y, MMAP_WALL_COLOR);
			else if (map[y][x] == 'D')
				draw_minimap_tile(data, x, y, MMAP_DOOR_COLOR);
		}
	}
	draw_minimap_player(data);
}

//Not in use but can be used...lines more than 25...
// void	draw_minimap_dynamic(t_data *data)
// {
// 	int	dx;
// 	int	dy;
// 	int	mx;
// 	int	my;
// 	int	color;

// 	dy = -MINIMAP_RADIUS - 1;
// 	while (++dy <= MINIMAP_RADIUS)
// 	{
// 		dx = -MINIMAP_RADIUS - 1;
// 		while (++dx <= MINIMAP_RADIUS)
// 		{
// 			mx = (int)(data->player->x + dx);
// 			my = (int)(data->player->y + dy);
// 			if (my < 0 || mx < 0 || !data->map.map[my])
// 				continue ;
// 			if (data->map.map[my][mx] == '1')
// 				color = 0x444444;
// 			else if (data->map.map[my][mx] == 'D')
// 				color = 0xAA8800;
// 			else
// 				continue ;
// 			draw_minimap_tile(data, dx + MINIMAP_RADIUS, dy + MINIMAP_RADIUS,
// 				color);
// 		}
// 	}
// 	draw_minimap_player(data);
// }
