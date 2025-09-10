/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 16:13:13 by isahmed           #+#    #+#             */
/*   Updated: 2025/09/10 18:01:45 by isahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_quit(t_data *data)
{
	if (!data || !data->mlx)
		return (-1);
	if (data->img.img)
		mlx_destroy_image(data->mlx, data->img.img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(0);
	return (0);
}

int	set_rgb(char *line)
{
	int		colour;
	int		rgb;
	int		i;

	i = 0;
	while (!ft_isdigit(line[i]))
		i ++;
	colour = ft_atoi(&line[i]);
	rgb = (colour << 16);
	line = ft_strchr(line, ',') + 1;
	colour = ft_atoi(line);
	rgb = rgb + (colour << 8);
	line = ft_strchr(line, ',') + 1;
	colour = ft_atoi(line);
	rgb = rgb + colour;
	return (rgb);
}
