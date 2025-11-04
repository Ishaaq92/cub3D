/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 16:13:13 by isahmed           #+#    #+#             */
/*   Updated: 2025/10/09 17:34:09 by isahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_sprites(t_data *data)
{
	int		x;
	int		y;
	t_sprite	*sprite;
	
	y = -1;
	data->sprite_count = 0;
	while (data->map.map[++y])
	{
		x = -1;
		while (data->map.map[y][++x])
		{
			if (data->map.map[y][x] == 'G')
			{
				if (data->door_count < MAX_SPRITE)
				{
					sprite = &data->sprites[data->sprite_count++];
					sprite->x = x + 0.5;
					sprite->y = y + 0.5;
					sprite->tex_id = 0;
					sprite->distance = 0.0;
				}
			}
		}
	}
    printf("Initialized %d sprites\n", data->sprite_count);
}

void	count_doors(t_data *data)
{
	int		x;
	int		y;
	t_door	*door;
	
	y = -1;
	while (data->map.map[++y])
	{
		x = -1;
		while (data->map.map[y][++x])
		{
			if (data->map.map[y][x] == 'D')
			{
				if (data->door_count < MAX_DOORS)
				{
					door = &data->doors[data->door_count++];
					door->x = x;
					door->y = y;
				}
			}
		}
	}
}

void	init_doors(t_data *data)
{
	int	i;

	i = -1;
	while (++i < MAX_DOORS)
	{
		data->doors[i].x = -1;
		data->doors[i].y = -1;
		data->doors[i].open_width = 0.0;
		data->doors[i].state = 0;
		data->doors[i].timer = 0.0;
		data->doors[i].is_vertical = 0;
	}
	data->door_count = 0;
}

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
	free(data->map.path_to_EA);
	free(data->map.path_to_NO);
	free(data->map.path_to_WE);
	free(data->map.path_to_SO);
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
