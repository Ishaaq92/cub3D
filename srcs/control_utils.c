/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaladeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 15:10:47 by aaladeok          #+#    #+#             */
/*   Updated: 2025/11/05 15:10:50 by aaladeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	print_controls(void)
{
	printf("\n");
	printf("Controls:\n");
    printf("  W/A/S/D - Move\n");
    printf("  Arrow Keys - Rotate camera\n");
    printf("  Mouse - Look around (click to lock/unlock)\n");
    // printf("  Shift - Sprint\n"); Did we implement sprint? current speed is actually sprinting..
    printf("  ESC - Exit\n");
}

// Smooth easing function for natural animation
double	ease_in_out_cubic(double t)
{
	double	f;

	if (t < 0.5)
		return (4.0 * t * t * t);
	else
	{
		f = (2.0 * t - 2.0);
		return (1.0 + f * f * f / 2.0);
	}
}

t_door	*find_door(t_data *data, int x, int y)
{
	int		i;
	t_door	*door;

	i = 0;
	while (i < data->door_count)
	{
		door = &data->doors[i];
		if (door->x == x && door->y == y)
			return (door);
		i++;
	}
	return (NULL);
}
