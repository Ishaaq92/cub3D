/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 16:12:40 by isahmed           #+#    #+#             */
/*   Updated: 2025/09/17 15:56:10 by isahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	pixel_put(int x, int y, t_img *img, int colour)
{
	char	*pixel;

	if (x >= 0 && y >= 0 && x < WIDTH  && y < HEIGHT)
	{
		pixel = img->pxls + (y * img->line_length + x * (img->bpp / 8));
		*(unsigned int *)pixel = colour;
	}
}

void	set_player_dir(t_player *player, char dir)
{
	if (dir == 'N')
	{
		player->dir_x = 0;
		player->dir_y = -1;
	}
	else if (dir == 'S')
	{
		player->dir_x = 0;
		player->dir_y = 1;
	}
	else if (dir == 'E')
	{
		player->dir_x = 1;
		player->dir_y = 0;
	}
	else if (dir == 'W')
	{
		player->dir_x = -1;
		player->dir_y = 0;
	}

	//Camera Plan calc..
	player->plane_x = -player->dir_y * FOV; //0.66 see header file
	player->plane_y = player->dir_x * FOV;
}

void	render(t_data *data)
{
	int			x;
	int			y;
	// double		distance;
	// int			line_height;
	// int			draw_start;
	// int			draw_end;
	t_ray	ray;

	x = -1;
	set_player_dir(data->player, data->player->orientation);
	data->ray = &ray;
	while (++x < WIDTH)
	{
		y = -1;
		// ray.distance = dda(data, x);
		dda(data, x);
		ray.line_height = (int) (HEIGHT / ray.distance);
		printf("|%d|", ray.line_height);
		if (ray.line_height < 0)
		 	ray.line_height = ray.line_height % HEIGHT;
		while (++y < HEIGHT)
		{
			ray.draw_start = -ray.line_height / 2 + HEIGHT / 2;
  		    if(ray.draw_start < 0)
				ray.draw_start = 0;
   			ray.draw_end = ray.line_height / 2 + HEIGHT / 2;
    		if(ray.draw_end >= HEIGHT)
				ray.draw_end = HEIGHT - 1;

			if (y > ray.draw_start && y < ray.draw_end)
				pixel_put(x, y, &data->img, 0Xff00FF);
			else if (y < ray.draw_start)
				pixel_put(x, y, &data->img, 300);
			else if (y > ray.draw_end)
				pixel_put(x, y, &data->img, 100);
			else
				pixel_put(x, y, &data->img, 0x00FF0F);
		}
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
}
