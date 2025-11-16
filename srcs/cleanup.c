/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 12:30:55 by aaladeok          #+#    #+#             */
/*   Updated: 2025/11/10 18:07:25 by isahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// void free_lines(t_line *list)
void	free_entities(t_data *data)
{
	if (data->list)
		free_lines(data->list);
	free_map_entities(data);
	if (data->game)
		free_game_entities(data);
	if (data->player)
		free(data->player);
	data->player = NULL;
	free(data);
	data = NULL;
}

int	exit_error(t_data *data, char *str)
{
	if (str)
		printf("Error: %s\n", str);
	free_entities(data);
	exit(1);
}

void	free_game_entities(t_data *data)
{
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

void free_map_entities(t_data *data)
{
    int i;

    if (!data)
        return;
    if (data->map.map)
    {
        i = 0;
        while (data->map.map[i])
            free(data->map.map[i++]);
        free(data->map.map);
        data->map.map = NULL;
    }
    free(data->map.path_to_north);
	data->map.path_to_north = NULL;
    free(data->map.path_to_south);
	data->map.path_to_south = NULL;
    free(data->map.path_to_east);
	data->map.path_to_east  = NULL;
    free(data->map.path_to_west);
    data->map.path_to_west = NULL;
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
