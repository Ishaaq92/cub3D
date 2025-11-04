#include "cub3D.h"

void	set_side_dist(t_ray *ray, t_data *data)
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

void	initialise_ray(t_data *data)
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
