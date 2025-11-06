/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaladeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 11:27:03 by aaladeok          #+#    #+#             */
/*   Updated: 2025/11/06 11:27:08 by aaladeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Calculate texture step and position
void	init_texture_calc(t_tex_info *tex, t_sprite_draw *draw, int height)
{
	double	sprite_height_diff;

	tex->step = 1.0 * height / (draw->draw_end_y - draw->draw_start_y);
	sprite_height_diff = (draw->draw_end_y - draw->draw_start_y) / 2;
	tex->tex_pos = (draw->draw_start_y - HEIGHT / 2 + sprite_height_diff);
	tex->tex_pos *= tex->step;
}

// Clamp drawing boundaries to screen
void	clamp_draw_bounds(t_sprite_draw *draw, t_tex_info *tex)
{
	if (draw->draw_start_y < 0)
	{
		tex->tex_pos += -draw->draw_start_y * tex->step;
		draw->draw_start_y = 0;
	}
	if (draw->draw_end_y > HEIGHT)
	{
		draw->draw_end_y = HEIGHT;
	}
}
