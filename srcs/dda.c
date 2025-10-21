/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:10:07 by isahmed           #+#    #+#             */
/*   Updated: 2025/10/09 17:09:43 by isahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	set_side_dist(t_ray *ray, t_data *data)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (data->player->x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - data->player->x)
			* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (data->player->y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - data->player->y)
			* ray->delta_dist_y;
	}
}

static void	initialise_ray(t_data *data)
{
	t_game	*game;
	t_ray	*ray;

	
	ray = data->ray;
	game = data->game;
	data->ray->map_x = (int)data->player->x;
	ray->map_y = (int)data->player->y;
	ray->step_x = 1;
	ray->step_y = 1;
	ray->ray_dir_x = game->dir_x + (game->plane_x * game->camera_x);
	ray->ray_dir_y = game->dir_y + (game->plane_y * game->camera_x);
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
}

double	perform_dda(t_ray *ray, char **map)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (map[ray->map_y][ray->map_x] == '1')
			hit = 1;
	}
	if (ray->side == 0)
		return (ray->side_dist_x - ray->delta_dist_x);
	else
		return (ray->side_dist_y - ray->delta_dist_y);
}

double	dda(t_data *data, int x)
{
	x = WIDTH - x;
	data->game->camera_x = (2 * x) / (double)WIDTH - 1;
	initialise_ray(data);
	set_side_dist(data->ray, data);
	return (perform_dda(data->ray, data->map.map));
}
