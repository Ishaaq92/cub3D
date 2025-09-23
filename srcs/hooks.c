/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 16:11:05 by isahmed           #+#    #+#             */
/*   Updated: 2025/09/23 15:23:46 by isahmed          ###   ########.fr       */
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
	printf("rotate\n");
}

int	key_hook(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		ft_quit(data);
	else if (keycode == XK_w || keycode == XK_W)
		data->game->player->x += 0.1;
	else if (keycode == XK_a || keycode == XK_A)
		data->game->player->y -= 0.1;
	else if (keycode == XK_s || keycode == XK_S)
		data->game->player->x -= 0.1;
	else if (keycode == XK_d || keycode == XK_D)
		data->game->player->y += 0.1;
	else if (keycode == XK_Right)
		rotate(data, 2);
	else if (keycode == XK_Left)
		rotate(data, -2);
	else
		return (1);
	return (0);
}
