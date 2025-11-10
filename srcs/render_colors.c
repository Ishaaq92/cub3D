/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_colors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 13:15:45 by aaladeok          #+#    #+#             */
/*   Updated: 2025/11/10 13:48:46 by isahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_floor_column(t_data *data, int x, int draw_start)
{
	int	y;

	if (data->floor_mode == 1)
	{
		y = draw_start;
		while (y < HEIGHT)
		{
			pixel_put(x, y, &data->img, data->map.floor_rgb);
			y++;
		}
	}
}

void	draw_ceiling_column(t_data *data, int x, int draw_end)
{
	int	y;

	if (data->floor_mode == 1)
	{
		y = 0;
		while (y < draw_end)
		{
			pixel_put(x, y, &data->img, data->map.ceiling_rgb);
			y++;
		}
	}
}

void	update_user_interface(t_data *data)
{
	update_sprite_distances(data);
	render_sprites(data);
	draw_gun(data);
	draw_minimap(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	draw_crosshair(data);
}
