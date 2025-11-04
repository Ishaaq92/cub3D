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

void    check_side_dist(t_ray *ray)
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
}

void    check_ray_dist(t_data *data, t_ray *ray)
{
    if (ray->side == 0)
        ray->distance = (ray->map_x - data->player->x + 
                        (1 - ray->step_x) / 2) / ray->ray_dir_x;
    else
        ray->distance = (ray->map_y - data->player->y + 
                        (1 - ray->step_y) / 2) / ray->ray_dir_y;
}

void    dda_cycle(t_data *data, t_ray *ray, char **map, int *hit, t_door *door)
{
    while (*hit == 0)
    {
        check_side_dist(ray);
        ray->tile = map[ray->map_y][ray->map_x];
        if (ray->tile == 'D')
        {
            door = find_door(data, ray->map_x, ray->map_y); 
            // If door is 30% or more open, raycast through it
            if (door && door->open_width >= 0.3)
                continue; // Keep raycasting to find wall behind
            else
            {
                *hit = 1;
                // ray->tile = tile;
                ray->door = door;
            }
        }
        else if (ray->tile == '1')
        {
            *hit = 1;
            // ray->tile = tile;
            ray->door = NULL;
        }
    }
}

// Modified DDA to handle open doors
void perform_dda(t_ray *ray, char **map, t_data *data)
{
    int         hit;
    t_door      *door;

    hit = 0;
    door = NULL;
    dda_cycle(data, ray, map, &hit, door);
    // Calculate ray distance
    check_ray_dist(data, ray);
}


void	dda(t_data *data, int x)
{
	data->game->camera_x = (2 * x) / (double)WIDTH - 1;
	initialise_ray(data);
	set_side_dist(data->ray, data);
	perform_dda(data->ray, data->map.map, data);
}
