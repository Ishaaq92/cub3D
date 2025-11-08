/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 16:43:22 by aaladeok          #+#    #+#             */
/*   Updated: 2025/11/06 18:29:21 by isahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_sprites(t_data *data)
{
	int			x;
	int			y;
	t_sprite	*sprite;

	y = -1;
	data->sprite_count = 0;
	while (data->map.map[++y])
	{
		x = -1;
		while (data->map.map[y][++x])
		{
			if (data->map.map[y][x] == 'G')
			{
				if (data->door_count < MAX_SPRITE)
				{
					sprite = &data->sprites[data->sprite_count++];
					sprite->x = x + 0.5;
					sprite->y = y + 0.5;
					sprite->tex_id = 0;
					sprite->distance = 0.0;
				}
			}
		}
	}
	printf("Initialized %d sprites\n", data->sprite_count);
}

void	count_doors(t_data *data)
{
	int	y;
	int	x;
	int	count;

	count = 0;
	y = -1;
	while (data->map.map[++y] != 0)
	{
		x = -1;
		while (data->map.map[y][++x] != '\0')
		{
			if (data->map.map[y][x] == 'D')
				count++;
		}
	}
	data->door_count = count;
	printf("Found %d doors\n", count);
}

static void	inititialize_doors(t_data *data)
{
	int		x;
	int		y;
	int		count;
	t_door	*door;

	count = 0;
	y = -1;
	while (data->map.map[++y])
	{
		x = -1;
		while (data->map.map[y][++x])
		{
			if (data->map.map[y][x] == 'D')
			{
				door = &data->doors[count];
				door->x = x;
				door->y = y;
				door->open_width = 0.0;
				door->state = 0;
				door->timer = 0.0;
				door->current_frame = 0;
				count++;
			}
		}
	}
}

void	init_doors(t_data *data)
{
	count_doors(data);
	inititialize_doors(data);
}
