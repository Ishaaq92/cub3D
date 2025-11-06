/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaladeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 15:12:25 by aaladeok          #+#    #+#             */
/*   Updated: 2025/11/05 15:12:27 by aaladeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Calculate drawing boundaries
static void	calc_draw_bounds(t_sprite_draw *draw)
{
	draw->draw_start_y = -draw->sprite_height / 2 + HEIGHT / 2;
	draw->draw_end_y = draw->sprite_height / 2 + HEIGHT / 2;
	draw->draw_start_x = -draw->sprite_width / 2 + draw->sprite_screen_x;
	draw->draw_end_x = draw->sprite_width / 2 + draw->sprite_screen_x;
	if (draw->draw_start_x < 0)
		draw->draw_start_x = 0;
	if (draw->draw_end_x > WIDTH)
		draw->draw_end_x = WIDTH;
}

// Draw one vertical stripe of sprite
static void	draw_sprite_stripe(t_data *data, int x, t_stripe_data *stripe)
{
	t_sprite_draw	draw;
	t_tex_info		tex;
	int				y;
	unsigned int	color;

	if (x < 0 || x >= WIDTH)
		return ;
	if (stripe->depth >= data->zbuffer[x])
		return ;
	draw.draw_start_y = stripe->draw_start_y;
	draw.draw_end_y = stripe->draw_end_y;
	init_texture_calc(&tex, &draw, data->textures.sprite.height);
	clamp_draw_bounds(&draw, &tex);
	y = draw.draw_start_y - 1;
	while (++y < draw.draw_end_y)
	{
		tex.tex_y = (int)tex.tex_pos & (data->textures.sprite.height - 1);
		tex.tex_pos += tex.step;
		color = get_pixel_img(&data->textures.sprite, stripe->tex_x, tex.tex_y);
		if ((color & 0x00FFFFFF) != 0)
		{
			pixel_put(x, y, &data->img, color);
		}
	}
}

// Draw all vertical stripes of one sprite
static void	draw_sprite_stripes(t_data *data, t_sprite_draw *draw, double depth)
{
	int				x;
	int				tex_x;
	int				offset;
	int				tex_width;
	t_stripe_data	stripe;

	stripe.draw_start_y = draw->draw_start_y;
	stripe.draw_end_y = draw->draw_end_y;
	stripe.depth = depth;
	tex_width = data->textures.sprite.width;
	x = draw->draw_start_x - 1;
	while (++x < draw->draw_end_x)
	{
		offset = -draw->sprite_width / 2 + draw->sprite_screen_x;
		tex_x = (int)(256 * (x - offset) * tex_width / draw->sprite_width)
			/ 256;
		if (tex_x < 0)
			tex_x = 0;
		if (tex_x >= tex_width)
			tex_x = tex_width - 1;
		stripe.tex_x = tex_x;
		draw_sprite_stripe(data, x, &stripe);
	}
}

// Process and render single sprite
static void	render_single_sprite(t_data *data, t_sprite *sprite)
{
	t_transform		t;
	t_sprite_draw	draw;
	double			det;

	t.sprite_x = sprite->x - data->player->x;
	t.sprite_y = sprite->y - data->player->y;
	det = data->game->plane_x * data->game->dir_y;
	det -= data->game->dir_x * data->game->plane_y;
	t.inv_det = (1.0 / det);
	t.transform_x = t.inv_det * (data->game->dir_y * t.sprite_x);
	t.transform_x -= t.inv_det * (data->game->dir_x * t.sprite_y);
	t.transform_y = t.inv_det * (-data->game->plane_y * t.sprite_x);
	t.transform_y += t.inv_det * (data->game->plane_x * t.sprite_y);
	if (t.transform_y <= 0.1)
		return ;
	draw.sprite_height = abs((int)(HEIGHT / t.transform_y));
	draw.sprite_width = abs((int)(HEIGHT / t.transform_y));
	draw.sprite_screen_x = (int)((WIDTH / 2) * (1 + t.transform_x
				/ t.transform_y));
	calc_draw_bounds(&draw);
	draw_sprite_stripes(data, &draw, t.transform_y);
}

// Project and render all sprites
void	render_sprites(t_data *data)
{
	int		i;

	sort_sprites(data);
	i = -1;
	while (++i < data->sprite_count)
	{
		render_single_sprite(data, &data->sprites[i]);
	}
}
