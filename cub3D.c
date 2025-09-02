/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 12:40:08 by isahmed           #+#    #+#             */
/*   Updated: 2025/09/02 18:13:28 by isahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// 	void	*img;
// 	char	*pxls;
// 	int		bpp;
// 	int		line_length;
// 	int		endian;
// }	t_img;
// 
// typedef struct s_data
// {
// 	void		*mlx;
// 	void		*win;
// 	t_img		*img;
// 	double		zoom;
// }	t_data;

void	pixel_put(int x, int y, t_img *img, int colour)
{
	char	*pixel;

	if (x >= 0 && y >= 0 && x < WIDTH  && y < HEIGHT)
	{
		pixel = img->pxls + (y * img->line_length + x * (img->bpp / 8));
		*(unsigned int *)pixel = colour;
	}
}

void	render(t_data *data)
{
	int	x;
	int	y;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			pixel_put(x, y, data->img, 200);
		}
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img->img, 0, 0);
}

int	initialise_data(t_data *data)
{
	data->mlx = mlx_init();

	if (!data->mlx)
		return(-1);
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "CUB3D");
	if (!data->win)
		return (-1);
		// mlx_destroy_display(data->mlx);
		// free(data->mlx);
	data->img->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->img->img)
		return (-1);
		// ft_quit(data);
	data->img->pxls = mlx_get_data_addr(data->img->img, &data->img->bpp,
			&data->img->line_length,
			&data->img->endian);
	data->zoom = 1.0;
	return (0);
}

void	ft_quit(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img->img);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
}

int		main(void)
{
	t_data	data;
	
	if (initialise_data(&data) == -1)
		exit(1);
	render(&data);
	mlx_loop(data.mlx);
	ft_quit(&data);
}

