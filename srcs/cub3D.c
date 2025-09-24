/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 12:40:08 by isahmed           #+#    #+#             */
/*   Updated: 2025/09/23 18:23:02 by isahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	game_loop(t_data *data)
{
	static int	frames;

	struct timeval	t1;
	struct timeval	t2;
	gettimeofday(&t1, NULL);
	render(data);
	gettimeofday(&t2, NULL);
	printf("%d\n", (int) (1 / (double)((t2.tv_usec - t1.tv_usec) / 1000000.0)));
	return (0);
}

int main(int ac, char **av)
{
	t_data		data;

	ft_bzero(&data, sizeof(data));
	data.map.celling_rgb = -1;
	data.map.floor_rgb = -1;
	if (ac != 2 || (av[1] && parser(&data, av[1])))
		return (1);
	validate_input(&data, av[1]);

	if (initialise_data(&data) == -1)
		exit(1);
	mlx_hook(data.win, DestroyNotify, NoEventMask, ft_quit, &data);
	mlx_key_hook(data.win, key_hook, &data);
	mlx_loop_hook(data.mlx, game_loop, &data);
	mlx_loop(data.mlx);
	ft_quit(&data);
}
