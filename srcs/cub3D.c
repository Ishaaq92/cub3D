/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 12:40:08 by isahmed           #+#    #+#             */
/*   Updated: 2025/11/06 18:59:58 by isahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

double	get_time_in_ms(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((double)(t.tv_sec * 1000 + t.tv_usec / 1000));
}

void	mouse_setup(t_data *data)
{
	data->mouse_x = WIDTH / 2;
	data->mouse_y = HEIGHT / 2;
	data->mouse_locked = 0;
}

void	reset_map(t_data *data)
{
	data->map.map_height = 0;
	data->map.map = 0;
	data->map.ceiling_rgb = -1;
	data->map.floor_rgb = -1;
	data->map.path_to_east = 0;
	data->map.path_to_west = 0;
	data->map.path_to_north = 0;
	data->map.path_to_south = 0;
}

void	setup_hooks(t_data *data)
{
	mlx_hook(data->win, DestroyNotify, 0, ft_quit, data);
	mlx_hook(data->win, KeyPress, KeyPressMask, key_press_hold, data);
	mlx_hook(data->win, KeyRelease, KeyReleaseMask, key_release, data);
	mlx_hook(data->win, MotionNotify, PointerMotionMask, mouse_move, data);
	mlx_hook(data->win, ButtonPress, ButtonPressMask, mouse_click, data);
	mlx_loop_hook(data->mlx, game_loop, data);
	mlx_loop(data->mlx);
}

/*We need an interactive message, when game initiated without args*/
int	main(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	ft_bzero(data, sizeof(t_data));
	reset_map(data);
	if (ac != 2)
	{
		printf("Usage: ./cub3d <map.cub>\n");
		return (1);
	}
	if (av[1] && parser(data, av[1]))
		return (1);
	validate_input(data, av[1]);
	if (initialise_data(data) == -1)
		exit(1);
	print_controls();
	mouse_setup(data);
	setup_hooks(data);
	return (0);
}
