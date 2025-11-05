/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_animation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaladeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 15:11:47 by aaladeok          #+#    #+#             */
/*   Updated: 2025/11/05 15:11:50 by aaladeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	update_door_opening(t_door *door, double delta_time)
{
	double	speed;

	speed = delta_time / DOOR_SPEED;
	door->open_width += speed;
	if (door->open_width >= 1.0)
	{
		door->open_width = 1.0;
		door->state = 2;
		door->timer = 0.0;
	}
	door->current_frame = get_door_frame(door, DOOR_FRAMES);
}

static void	update_door_closing(t_door *door, t_data *data, double delta_time)
{
	double	speed;

	speed = delta_time / DOOR_CLOSE_SPEED;
	door->open_width -= speed;
	if (door->open_width <= 0.0)
	{
		door->open_width = 0.0;
		door->state = 0;
		data->map.map[door->y][door->x] = 'D';
	}
	door->current_frame = get_door_frame(door, DOOR_FRAMES);
}

static void	update_door_timer(t_door *door)
{
	door->timer += 1.0 / 60.0;
	if (door->timer >= DOOR_HOLD_TIME)
		door->state = 3;
}

static void	update_door_collision(t_door *door, t_data *data)
{
	if (door->open_width > 0.7)
		data->map.map[door->y][door->x] = '0';
	else
		data->map.map[door->y][door->x] = 'D';
}

void	update_doors(t_data *data, double delta_time)
{
	int		i;
	t_door	*door;

	i = -1;
	while (++i < data->door_count)
	{
		door = &data->doors[i];
		if (door->state == 1)
			update_door_opening(door, delta_time);
		else if (door->state == 2)
			update_door_timer(door);
		else if (door->state == 3)
			update_door_closing(door, data, delta_time);
		update_door_collision(door, data);
	}
}
