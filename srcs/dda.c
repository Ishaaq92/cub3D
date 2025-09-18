/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:10:07 by isahmed           #+#    #+#             */
/*   Updated: 2025/09/18 16:23:16 by isahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	initialise_game(t_game *game)
{
	game->player->x = 1;
	game->player->y = 1;
	game->plane_x = 0;
	game->plane_y = 0.66;
	game->dir_x = -1;
	game->dir_y = 0;
}

static void set_side_dist(t_ray *ray, t_game *game)
{
    if (ray->ray_dir_x < 0)
    {
        ray->step_x = -1;
        ray->side_dist_x = (game->player->x - ray->map_x) * ray->delta_dist_x;
    }
    else
    {
        ray->step_x = 1;
        // FIX: Assign to side_dist_x, not delta_dist_x
        ray->side_dist_x = (ray->map_x + 1.0 - game->player->x) * ray->delta_dist_x;
    }
    if (ray->ray_dir_y < 0)
    {
        ray->step_y = -1;
        ray->side_dist_y = (game->player->y - ray->map_y) * ray->delta_dist_y;
    }
    else
    {
        ray->step_y = 1;
        ray->side_dist_y = (ray->map_y + 1.0 - game->player->y) * ray->delta_dist_y;
    }
}

static void	initialise_ray(t_ray *ray, t_game *game)
{
	ray->map_x = (int)game->player->x;
	ray->map_y = (int)game->player->y;
	ray->step_x = 1;
	ray->step_y = 1;
	ray->ray_dir_x = game->dir_x + game->plane_x * game->camera_x;
	ray->ray_dir_y = game->dir_y + game->plane_y * game->camera_x;
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);

	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
}

int	perform_dda(t_ray *ray, char test_map[8][9])
{
	int		hit;
	int		side;

	hit = 0;
	while (hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			side = 1;
		}
		if (test_map[ray->map_y][ray->map_x] > '0')
			hit = 1;
	}
	if (side == 0)
		return (ray->side_dist_x - ray->delta_dist_x);
	else
		return(ray->side_dist_y - ray->delta_dist_y);
}

double dda(int x)
{
	char		test_map[8][9] =
	{
		"1111111\n",
		"1000001\n",
		"1000001\n",
		"1000001\n",
		"1000001\n",
		"1000001\n",
		"1111111\0"
	};
	t_game		game;
	t_player	player;
	t_ray		ray;

	game.player = &player;
	game.camera_x = 2 * x / (double)WIDTH - 1;
	initialise_game(&game);
	initialise_ray(&ray, &game);
	set_side_dist(&ray, &game);
	return (perform_dda(&ray, test_map));
}
