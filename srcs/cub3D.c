/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 12:40:08 by isahmed           #+#    #+#             */
/*   Updated: 2025/09/10 19:43:52 by isahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int main(int ac, char **av)
{
	t_data data;

	if (ac != 2)
		return (1);
	if (av[1] && parser(&data, av[1]))
		return (1);
	for (int i=0; i < data.map.map_size; i++)
		printf("- %s", data.map.map[i]);

	validate_input(&data, av[1]);
	// validate_map(data.map.map, )
	// if (initialise_data(&data) == -1)
	// 		exit(1);
	// render(&data);
	// mlx_hook(data.win, DestroyNotify, NoEventMask, ft_quit, &data);
	// mlx_key_hook(data.win, key_hook, &data);
	// mlx_loop(data.mlx);
	// ft_quit(&data);
}
