/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaladeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 11:24:27 by aaladeok          #+#    #+#             */
/*   Updated: 2025/11/06 11:24:31 by aaladeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

unsigned int	apply_fade(t_ray *ray, unsigned int color)
{
	double			fade;
	unsigned int	faded_color;

	if (ray->tile == 'D' && ray->door && ray->door->open_width > 0.8)
	{
		fade = 1.0 - ((ray->door->open_width - 0.8) / 0.2);
		faded_color = apply_alpha(color, fade);
		return (faded_color);
	}
	return (color);
}

// Get the correct door texture frame
t_img	*get_door_texture(t_data *data, t_door *door)
{
	int	frame;

	if (!door)
		return (&data->textures.door_arr.frames[0]);
	frame = door->current_frame;
	if (frame < 0)
		frame = 0;
	if (frame >= data->textures.door_arr.frame_count)
		frame = data->textures.door_arr.frame_count - 1;
	return (&data->textures.door_arr.frames[frame]);
}

// SIMPLIFIED choose_texture - just picks the right frame
t_img	*choose_texture(t_data *data)
{
	t_img	*texture;

	if (data->ray->tile == 'D' && data->ray->door)
	{
		return (get_door_texture(data, data->ray->door));
	}
	if (data->ray->side == 0)
	{
		if (data->ray->ray_dir_x < 0)
			texture = &data->textures.west;
		else
			texture = &data->textures.east;
	}
	else
	{
		if (data->ray->ray_dir_y < 0)
			texture = &data->textures.north;
		else
			texture = &data->textures.south;
	}
	return (texture);
}

void	calculate_wall_bounds(t_data *data)
{
	t_ray	*ray;

	ray = data->ray;
	ray->draw_start = (-ray->line_height / 2) + (HEIGHT / 2);
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = (ray->line_height / 2) + (HEIGHT / 2);
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
}

void	calculate_hitside(t_data *data)
{
	t_ray	*ray;

	ray = data->ray;
	if (ray->side == 0)
		ray->wall_x = data->player->y + ray->distance * ray->ray_dir_y;
	else
		ray->wall_x = data->player->x + ray->distance * ray->ray_dir_x;
	ray->wall_x -= floor(ray->wall_x);
}
