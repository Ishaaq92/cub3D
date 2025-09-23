/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 12:40:08 by isahmed           #+#    #+#             */
/*   Updated: 2025/09/23 16:49:22 by isahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
	mlx_loop_hook(data.mlx, render, &data);
	mlx_loop(data.mlx);
	ft_quit(&data);
}
