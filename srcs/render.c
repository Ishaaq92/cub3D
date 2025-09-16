/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 16:12:40 by isahmed           #+#    #+#             */
/*   Updated: 2025/09/16 20:14:14 by isahmed          ###   ########.fr       */
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

// get_side_dist_x()

void	render(t_data *data)
{
	int			x;
	int			y;
	double		distance;
	int			line_height;
	int			draw_start;
	int			draw_end;

	x = -1;
	while (++x < WIDTH)
	{
		y = -1;
		distance = dda(data, x);
		line_height = (int) (HEIGHT / distance);
		printf("|%f|", distance);
		if (line_height < 0)
		 	line_height = line_height % HEIGHT;
			// printf("LESS THAN 0 \n");
		while (++y < HEIGHT)
		{
			draw_start = -line_height / 2 + HEIGHT / 2;
  		    if(draw_start < 0)
				draw_start = 0;
   			draw_end = line_height / 2 + HEIGHT / 2;
    		if(draw_end >= HEIGHT)
				draw_end = HEIGHT - 1;

			if (y > draw_start && y < draw_end)
				pixel_put(x, y, &data->img, 0Xff00FF);
			else if (y < draw_start)
				pixel_put(x, y, &data->img, 300);
			else if (y > draw_end)
				pixel_put(x, y, &data->img, 100);
			else
				pixel_put(x, y, &data->img, 0x00FF0F);
		}
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
}
