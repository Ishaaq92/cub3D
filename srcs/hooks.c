/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 16:11:05 by isahmed           #+#    #+#             */
/*   Updated: 2025/10/09 17:15:33 by isahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	rotate(t_data *data, double rot_speed)
{
	double	old_dir_x = data->game->dir_x;

    data->game->dir_x = data->game->dir_x * cos(-rot_speed) - data->game->dir_y * sin(-rot_speed);
    data->game->dir_y = old_dir_x * sin(-rot_speed) + data->game->dir_y * cos(-rot_speed);
    double oldPlaneX = data->game->plane_x;
    data->game->plane_x = data->game->plane_x * cos(-rot_speed) - data->game->plane_y * sin(-rot_speed);
    data->game->plane_y = oldPlaneX * sin(-rot_speed) + data->game->plane_y * cos(-rot_speed);
}

int	wall_detection(t_data *data, double new_x, double new_y)
{
	double	gap;

	gap = 0.2;
	if (data->map.map[(int)(new_y)][(int)(new_x - gap)] == '1')
		return (1);
	else if (data->map.map[(int)(new_y)][(int)(new_x + gap)] == '1')
		return (1);
	else if (data->map.map[(int)(new_y - gap)][(int)(new_x)] == '1')
		return (1);
	else if (data->map.map[(int)(new_y + gap)][(int)(new_x)] == '1')
		return (1);
	else 
		return(0);
}

void	walk(t_data *data, char dir, double scale)
{
	double	new_x;	
	double	new_y;	

	if (dir == 'f' || dir == 'b')
	{
		new_x = data->player->x + (data->game->dir_x * scale);
		new_y = data->player->y + (data->game->dir_y * scale);
	}
	else if (dir == 'l' || dir == 'r')
	{
		new_x = data->player->x + (data->game->plane_x * scale);
		new_y = data->player->y + (data->game->plane_y * scale);
	}
	if (wall_detection(data, new_x, new_y) == 1)
		return ;
	data->player->x = new_x;
	data->player->y = new_y;
}

int	key_hook(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		ft_quit(data);
	else if (keycode == XK_w || keycode == XK_W)
	 	walk(data, 'f', 0.1);
	else if (keycode == XK_a || keycode == XK_A)
	 	walk(data, 'r', 0.1);
	else if (keycode == XK_s || keycode == XK_S)
	 	walk(data, 'b', -0.1);
	else if (keycode == XK_d || keycode == XK_D)
	 	walk(data, 'l', -0.1);
	else if (keycode == XK_Right)
		rotate(data, -0.1);
	else if (keycode == XK_Left)
		rotate(data, 0.1);
	else
		return (1);
	// render(data);
	return (0);
}
