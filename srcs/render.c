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

static void	pixel_put(int x, int y, t_img *img, int colour)
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
	char	*dst;

	printf("image width is: %d\n", img->width);
	printf("image height is %d\n", img->height);
	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return (0);
	dst = img->pxls + (y * img->line_length + x * (img->bpp / 8));
	return (*(unsigned int *)dst);
}

static void	draw_pixel(t_data *data, int x, int y, int line_height)
{
	int	draw_start;
	int	draw_end;

	draw_start = -line_height / 2 + HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + HEIGHT / 2;
	if (draw_end >= HEIGHT)
		draw_end = HEIGHT - 1;
	// 0xffffff
	// 0xe6e6fa
	// 0xcbbeb5
	printf("returned color: %d\n", get_pixel_img(&data->textures.north, x, y));
	if (y > draw_start && y < draw_end)
		pixel_put(x, y, &data->img, 0xffffff);
	else if (y <= draw_start)
		pixel_put(x, y, &data->img, 0);
	else if (y >= draw_end)
		pixel_put(x, y, &data->img, data->map.floor_rgb);
	else
		pixel_put(x, y, &data->img, 0xFF0000);
}

void	render(t_data *data)
{
	int		x;
	int		y;
	double	distance;
	int		line_height;

	x = -1;
	// Iterating over the width of the display. Left to right.
	while (++x < WIDTH)
	{
		// This function calculates distance to the wall for each vertical strip of pixel.
		distance = dda(data, x);
		line_height = (int)(HEIGHT / distance);
		y = -1;
		while (++y < HEIGHT)
			draw_pixel(data, x, y, line_height);
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
}
