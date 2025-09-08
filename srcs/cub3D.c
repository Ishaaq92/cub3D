/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 12:40:08 by isahmed           #+#    #+#             */
/*   Updated: 2025/09/08 15:07:52 by isahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	process_map(char *filename)
{
	int		fd;
	char	*s;

	fd = open(filename, 0);
	if (fd < 0)
		return (-1);
	while ((s = get_next_line(fd)))
		printf("%s\n", s);
	return (1);
}

int		main(int ac, char **av)
{
	t_data	data;

	if (ac >= 2)
		return (1);
	if (av[1])
		process_map(av[1]);
	if (initialise_data(&data) == -1)
		exit(1);
	render(&data);

	mlx_hook(data.win, DestroyNotify, NoEventMask, ft_quit, &data.mlx);
	mlx_key_hook(data.win, key_hook, &data);
	mlx_loop(data.mlx);
	ft_quit(&data);
}

