#include "cub3D.h"

// // Draw one vertical stripe of sprite
// static void	draw_sprite_stripe(t_data *data, int x, t_stripe_data *stripe)
// {
// 	t_sprite_draw	draw;
// 	t_tex_info		tex;
// 	int				y;

// 	if (x < 0 || x >= WIDTH)
// 		return ;
// 	if (stripe->depth >= data->zbuffer[x])
// 		return ;
// 	draw.draw_start_y = stripe->draw_start_y;
// 	draw.draw_end_y = stripe->draw_end_y;
// 	init_texture_calc(&tex, &draw, data->textures.sprite.height);
// 	clamp_draw_bounds(&draw, &tex);
// 	y = draw.draw_start_y - 1;
// 	while (++y < draw.draw_end_y)
// 	{
// 		tex.tex_y = (int)tex.tex_pos & (data->textures.sprite.height - 1);
// 		tex.tex_pos += tex.step;
// 		draw_pixel_if_visible(data, x, y, stripe->tex_x, tex.tex_y);
// 	}
// }

// Calculate inverse determinant for transformation
// static double	calc_inv_det(t_data *data)
// {
// 	double	det;

// 	det = data->game->plane_x * data->game->dir_y;
// 	det -= data->game->dir_x * data->game->plane_y;
// 	return (1.0 / det);
// }

// Transform sprite position to camera space
// static void	transform_sprite(t_transform *t, t_data *data)
// {
// 	double	det;

// 	det = data->game->plane_x * data->game->dir_y;
// 	det -= data->game->dir_x * data->game->plane_y;
// 	t->inv_det = (1.0 / det);
// 	// t->inv_det = calc_inv_det(data);
// 	t->transform_x = t->inv_det * (data->game->dir_y * t->sprite_x);
// 	t->transform_x -= t->inv_det * (data->game->dir_x * t->sprite_y);
// 	t->transform_y = t->inv_det * (-data->game->plane_y * t->sprite_x);
// 	t->transform_y += t->inv_det * (data->game->plane_x * t->sprite_y);
// }

// Translate sprite relative to camera
// static void	translate_sprite(t_transform *t, t_data *data, t_sprite *sprite)
// {
// 	t->sprite_x = sprite->x - data->player->x;
// 	t->sprite_y = sprite->y - data->player->y;
// }

// Calculate sprite dimensions on screen
// static void	calc_sprite_dimensions(t_sprite_draw *draw, t_transform *t)
// {
// 	draw->sprite_height = abs((int)(HEIGHT / t->transform_y));
// 	draw->sprite_width = abs((int)(HEIGHT / t->transform_y));
// 	draw->sprite_screen_x = (int)((WIDTH / 2) * (1 + t->transform_x
// 				/ t->transform_y));
// }