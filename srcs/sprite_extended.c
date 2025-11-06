/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_extended.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaladeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 09:28:00 by aaladeok          #+#    #+#             */
/*   Updated: 2025/11/06 09:28:05 by aaladeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	pixel_put(int x, int y, t_img *img, int colour)
{
	char	*pixel;

	if (x >= 0 && y >= 0 && x < WIDTH && y < HEIGHT)
	{
		pixel = img->pxls + (y * img->line_length + x * (img->bpp / 8));
		*(unsigned int *)pixel = colour;
	}
}

unsigned int	get_pixel_img(t_img *img, int x, int y)
{
	unsigned char	*dst;
	int				offset;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return (0);
	offset = y * img->line_length + x * (img->bpp / 8);
	dst = (unsigned char *)img->pxls + offset;
	return ((dst[2] << 16) | (dst[1] << 8) | dst[0]);
}

// Calculate sprite distances to player
void	update_sprite_distances(t_data *data)
{
	int		i;
	double	dx;
	double	dy;

	i = -1;
	while (++i < data->sprite_count)
	{
		dx = data->player->x - data->sprites[i].x;
		dy = data->player->y - data->sprites[i].y;
		data->sprites[i].distance = dx * dx + dy * dy;
	}
}

// Calculate distance from player to sprite
static double	calc_sprite_distance(t_data *data, t_sprite *sprite)
{
	double	dx;
	double	dy;

	dx = data->player->x - sprite->x;
	dy = data->player->y - sprite->y;
	return (dx * dx + dy * dy);
}

// Sort sprites by distance (back to front)
void	sort_sprites(t_data *data)
{
	int i;
	int j;
	t_sprite temp;
	double dist_i;
	double dist_j;

	i = -1;
	while (++i < data->sprite_count - 1)
	{
		j = i;
		while (++j < data->sprite_count)
		{
			dist_i = calc_sprite_distance(data, &data->sprites[i]);
			dist_j = calc_sprite_distance(data, &data->sprites[j]);
			if (dist_i < dist_j)
			{
				temp = data->sprites[i];
				data->sprites[i] = data->sprites[j];
				data->sprites[j] = temp;
			}
		}
	}
}
