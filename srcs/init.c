/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 16:10:24 by isahmed           #+#    #+#             */
/*   Updated: 2025/10/09 20:23:44 by isahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// generate_floor_texture(data); //Tested generated floor tiles.
void	load_textures(t_data *data)
{
	data->textures.north = load_xpm_to_img(data->mlx, data->map.path_to_north);
	data->textures.south = load_xpm_to_img(data->mlx, data->map.path_to_south);
	data->textures.west = load_xpm_to_img(data->mlx, data->map.path_to_west);
	data->textures.east = load_xpm_to_img(data->mlx, data->map.path_to_east);
	data->textures.roof = load_xpm_to_img(data->mlx, "./assets/ceiling/0.xpm");
	data->textures.floor = load_xpm_to_img(data->mlx, "./assets/floor/0.xpm");
	data->textures.gun = load_xpm_to_img(data->mlx,
			"./assets/weapon/shotgun/SHT2D0.xpm");
	data->textures.door = load_xpm_to_img(data->mlx,
			"./assets/door/Layer-1_sprite_02.xpm");
	data->textures.sprite = load_xpm_to_img(data->mlx, "./assets/goomba.xpm");
}

static void	reset_movement(t_data *data)
{
	data->player->forward = false;
	data->player->back = false;
	data->player->right = false;
	data->player->left = false;
	data->player->rotate_left = false;
	data->player->rotate_right = false;
}

void	set_orientation(t_data *data)
{
	data->game->dir_x = 0;
	data->game->dir_y = 0;
	data->game->plane_x = 0;
	data->game->plane_y = 0;
	if (data->player->orientation == 'N')
	{
		data->game->dir_y = -1;
		data->game->plane_x = -0.66;
	}
	if (data->player->orientation == 'S')
	{
		data->game->dir_y = 1;
		data->game->plane_x = 0.66;
	}
	if (data->player->orientation == 'W')
	{
		data->game->dir_x = -1;
		data->game->plane_y = 0.66;
	}
	if (data->player->orientation == 'E')
	{
		data->game->dir_x = 1;
		data->game->plane_y = -0.66;
	}
}

int	initialize_mlx_window(t_data *data)
{
	data->ray = malloc(sizeof(t_ray));
	ft_bzero(data->ray, sizeof(t_ray));
	if (!data->ray)
	{
		printf("Error: Failed to load door animation frames\n");
		exit(1);
	}
	if (!data->mlx)
		return (1);
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "CUB3D");
	if (!data->win)
		return (1);
	data->img.img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->img.img)
		return (1);
	data->img.pxls = mlx_get_data_addr(data->img.img, &data->img.bpp,
			&data->img.line_length, &data->img.endian);
	data->zbuffer = malloc(sizeof(double) * WIDTH);
	ft_memset(data->zbuffer, 0, sizeof(double) * WIDTH);
	if (!data->zbuffer)
	{
		printf("zbuffer allocation failed\n");
		return (1);
	}
	return (0);
}

int	initialise_data(t_data *data)
{
	reset_movement(data);
	data->mlx = mlx_init();
	data->game = malloc(sizeof(t_game));
	ft_bzero(data->game, sizeof(t_game));
	data->game->plane_x = 0;
	data->game->plane_y = 0.66;
	data->prev_time = get_time_in_ms();
	if (!load_door_frames(data))
	{
		printf("Error: Failed to load door animation frames\n");
		exit(1);
	}
	init_doors(data);
	init_sprites(data);
	set_orientation(data);
	if (initialize_mlx_window(data))
	{
		printf("Error while initializing.\n");
		exit(1);
	}
	load_textures(data);
	printf("Finished init..\n");
	return (0);
}
