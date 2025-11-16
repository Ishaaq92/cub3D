/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 12:30:55 by aaladeok          #+#    #+#             */
/*   Updated: 2025/11/16 19:03:09 by isahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	exit_error(t_data *data)
{
	free_map_entities(data);
	if (data->game)
		free_game_entities(data);
	if (data->player)
		free(data->player);
	free(data);
	data = NULL;
	exit (1);
}

void	free_game_entities(t_data *data)
{
	if (data->player)
		free(data->player);
	data->player = NULL;
	if (data->ray)
		free(data->ray);
	data->ray = NULL;
	if (data->zbuffer)
		free(data->zbuffer);
	data->zbuffer = NULL;
	if (data->game)
		free(data->game);
	data->game = NULL;
}

void	free_map_entities(t_data *data)
{
	int	i;

	i = -1;
	if (data->map.map)
	{
		while (data->map.map[++i])
			free(data->map.map[i]);
		free(data->map.map[i]);
	}
	if (data->map.path_to_north)
		free(data->map.path_to_north);
	if (data->map.path_to_west)
		free(data->map.path_to_west);
	if (data->map.path_to_south)
		free(data->map.path_to_south);
	if (data->map.path_to_east)
		free(data->map.path_to_east);
	if (data->map.map)
		free(data->map.map);
}

void	destroy_door_textures(void *mlx, t_door_tex *door_arr)
{
	int	i;

	i = -1;
	while (++i < DOOR_FRAMES)
	{
		if (door_arr->frames[i].img)
			mlx_destroy_image(mlx, door_arr->frames[i].img);
		door_arr->frames[i].img = NULL;
	}
}

void	free_tex_images(t_data *data)
{
	if (data->textures.west.img)
		mlx_destroy_image(data->mlx, data->textures.west.img);
	if (data->textures.east.img)
		mlx_destroy_image(data->mlx, data->textures.east.img);
	if (data->textures.north.img)
		mlx_destroy_image(data->mlx, data->textures.north.img);
	if (data->textures.south.img)
		mlx_destroy_image(data->mlx, data->textures.south.img);
	if (data->textures.door.img)
		mlx_destroy_image(data->mlx, data->textures.door.img);
	if (data->textures.floor.img)
		mlx_destroy_image(data->mlx, data->textures.floor.img);
	if (data->textures.roof.img)
		mlx_destroy_image(data->mlx, data->textures.roof.img);
	if (data->textures.gun.img)
		mlx_destroy_image(data->mlx, data->textures.gun.img);
	if (data->textures.sprite.img)
		mlx_destroy_image(data->mlx, data->textures.sprite.img);
}
