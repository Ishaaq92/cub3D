/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaladeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 15:10:25 by aaladeok          #+#    #+#             */
/*   Updated: 2025/11/05 15:10:29 by aaladeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void open_door(t_data *data, int map_x, int map_y)
{
    t_door *door = find_door(data, map_x, map_y);
    
    if (door)
    {
        if (door->state == 0 || door->state == 3) // Closed or closing
        {
            door->state = 1; // Start opening
            door->timer = 0.0;
        }
        else if (door->state == 2) // Already open
        {
            door->timer = 0.0; // Reset timer
        }
    }
}

void check_auto_doors(t_data *data)
{
    int         i;
    t_door      *door;
    double      dx; 
    double      dy;
    double      dist;
    
    i = -1;
    while (++i < data->door_count)
    {
        door = &data->doors[i];
        // Calculate distance from player to door center
        dx = door->x + 0.5 - data->player->x;
        dy = door->y + 0.5 - data->player->y;
        dist = sqrt(dx * dx + dy * dy); 
        // Auto-open if player is within 2 units and door is closed
        if (dist < 2.0 && door->state == 0)
        {
            door->state = 1;  // Start opening
            door->timer = 0.0;
            printf("Door at (%d, %d) opening automatically\n", door->x, door->y);
        }
        // If player moves away while door is open, let it auto-close
        // (the timer in update_doors handles this)
    }
}

int mouse_move(int x, int y, t_data *data)
{
    int delta_x;
    double  rot;
    double  old_dir_x;
    double  old_plane_x;

    (void)y;
    if (!data->mouse_locked)
        return (0);
    delta_x = x - data->mouse_x;
    rot = -delta_x * MOUSE_SENSITIVITY;
    old_dir_x = data->game->dir_x;
    data->game->dir_x = data->game->dir_x * cos(rot) - 
                        data->game->dir_y * sin(rot);
    data->game->dir_y = old_dir_x * sin(rot) + data->game->dir_y * cos(rot);
    old_plane_x = data->game->plane_x;
    data->game->plane_x = data->game->plane_x * cos(rot) - 
                        data->game->plane_y * sin(rot);
    data->game->plane_y = old_plane_x * sin(rot) + 
                            data->game->plane_y * cos(rot);
    data->mouse_x = WIDTH / 2;
    data->mouse_y = HEIGHT / 2;
    mlx_mouse_move(data->mlx, data->win, data->mouse_x, data->mouse_y);
    return (0);
}

int mouse_click(int button, int x, int y, t_data *data)
{
    (void)x;
    (void)y;
    
    if (button == 1)
    {
        data->mouse_locked = !data->mouse_locked;
        if (data->mouse_locked)
        {
            mlx_mouse_hide(data->mlx, data->win);
            data->mouse_x = WIDTH / 2;
            data->mouse_y = HEIGHT / 2;
            mlx_mouse_move(data->mlx, data->win, data->mouse_x, data->mouse_y);
        }
        else
            mlx_mouse_show(data->mlx, data->win);
    }
    return (0);
}
