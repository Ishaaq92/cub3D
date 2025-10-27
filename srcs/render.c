/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 16:12:40 by isahmed           #+#    #+#             */
/*   Updated: 2025/10/09 16:58:16 by isahmed          ###   ########.fr       */
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
	// Return as 0x00RRGGBB for easier usage
	return ((dst[2] << 16) | (dst[1] << 8) | dst[0]);
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

// void	draw_ceiling(t_data *data, int x)
// {
// 	int	y;

// 	y = 0;
// 	while (y < data->ray->draw_start)
// 	{
// 		pixel_put(x, y, &data->img, data->map.ceiling_rgb);
// 		y++;
// 	}
// }

void	draw_wall_with_tex(t_data *data, t_img *texture, int x)
{
	int				y;
	t_ray			*ray;
	unsigned int	color;

	y = data->ray->draw_start;
	ray = data->ray;
	while (y < ray->draw_end)
	{
		ray->tex_y = (int)ray->tex_pos & (texture->height - 1);
		// if texture height is power of 2
		ray->tex_pos += ray->step;
		color = get_pixel_img(texture, ray->tex_x, ray->tex_y);
		pixel_put(x, y, &data->img, color);
		y++;
	}
}

// void	draw_floor(t_data *data, int x)
// {
// 	int	y;

// 	y = data->ray->draw_end;
// 	while (y < HEIGHT)
// 	{
// 		pixel_put(x, y, &data->img, data->map.floor_rgb);
// 		y++;
// 	}
// }

t_img	*choose_texture(t_data *data)
{
	t_img	*texture;

	if (data->ray->side == 0) // vertical wall (X-side)
	{
		if (data->ray->ray_dir_x < 0)
			texture = &data->textures.west;
		else
			texture = &data->textures.east;
	}
	else // horizontal wall (Y-side)
	{
		if (data->ray->ray_dir_y < 0)
			texture = &data->textures.north;
		else
			texture = &data->textures.south;
	}
	return (texture);
}

void	calculate_hitside(t_data *data)
{
	t_ray	*ray;

	ray = data->ray;
	// Calculate exact hit location on wall (for tex_x)
	if (ray->side == 0)
		ray->wall_x = data->player->y + ray->distance * ray->ray_dir_y;
	else
		ray->wall_x = data->player->x + ray->distance * ray->ray_dir_x;
	// get fractional part (0.0 to 1.0)
	ray->wall_x -= floor(ray->wall_x);
}

void	draw_vertical_line(t_data *data, int x)
{
	t_ray	*r;
	t_img	*tex;

	r = data->ray;
	// Choose texture
	tex = choose_texture(data);
	// 2. Calculate exact hit location on wall (for tex_x)
	calculate_hitside(data);
	// 3. Convert wall_x to texture x-coordinate
	r->tex_x = (int)(r->wall_x * tex->width);
	if ((r->side == 0 && r->ray_dir_x > 0) || (r->side == 1
			&& r->ray_dir_y < 0))
		r->tex_x = tex->width - r->tex_x - 1;
	// 4. Calculate step and starting position for texture y-coordinate
	r->step = 1.0 * tex->height / r->line_height;
	r->tex_pos = (r->draw_start - HEIGHT / 2 + r->line_height / 2)
		* r->step;
	draw_wall_with_tex(data, tex, x);
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

void	render(t_data *data)
{
	int x;
	// int y;
	// int call;

	x = 0;
	// call = 0;
	if (!data->ray)
		data->ray = malloc(sizeof(t_ray));
	draw_floor_and_ceiling(data);
	while (x < WIDTH)
	{
		// printf("calls count: %d\n", ++call);
		dda(data, x);
		data->ray->line_height = (int)(HEIGHT / data->ray->distance);
		calculate_wall_bounds(data);
		draw_vertical_line(data, x);
		x++;
	}
	draw_gun(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	draw_crosshair(data);
}