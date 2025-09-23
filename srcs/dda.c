/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:10:07 by isahmed           #+#    #+#             */
/*   Updated: 2025/09/17 15:54:13 by isahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// double dda(int x)
// {
// 	char	test_map[8][9] =
// 	{
// 		"1111111\n",
// 		"1000001\n",
// 		"10S0001\n",
// 		"1000001\n",
// 		"1000001\n",
// 		"1000001\n",
// 		"1111111\0"
// 	};
// 	t_player	p;
// 	int	step_x;
// 	int	step_y;
// 	double	ray_dir_x ;
// 	double	ray_dir_y;
// // 
// 	double	delta_dist_x;
// 	double	delta_dist_y;
// // 
// 	double	side_dist_x = 0;
// 	double	side_dist_y = 0;
// // 
// 	int	hit = 0;
// 	int	side;
// // 
// 	p.x = 2;
// 	p.y = 2;
// 	p.dir_x = -1;
// 	p.dir_y = 0;
// 	p.plane_x = 0;
// 	p.plane_y = 0.66;
// // 
// 	int	map_x = (int) p.x;
// 	int	map_y = (int) p.y;
// // 
// 	p.camera_x = 2 * x / (double) WIDTH - 1;
// 	ray_dir_x = p.dir_x + p.plane_x * p.camera_x;
// 	ray_dir_y = p.dir_y + p.plane_y * p.camera_x;
// // 
// 	if (ray_dir_x != 0)
// 		delta_dist_x = fabs(1 / ray_dir_x);
// 	else
// 		delta_dist_x = 1e30;
// // 
// 	if (ray_dir_y != 0)
// 		delta_dist_y = fabs(1 / ray_dir_y);
// 	else
// 		delta_dist_y = 1e30;
// // 
// 	if (ray_dir_x < 0)
// 	{
// 		step_x = -1;
// 		side_dist_x = (p.x - map_x) * delta_dist_x;
// 	}
// 	else
// 	{
// 		step_x = 1;
// 		side_dist_x = (map_x + 1.0 - p.x) * delta_dist_x;
// 	}
// 	if (ray_dir_y < 0)
// 	{
// 		step_y = -1;
// 		side_dist_y = (p.y - map_y) * delta_dist_y;
// 	}
// 	else
// 	{
// 		step_y = 1;
// 		side_dist_y = (map_y + 1.0 - p.y) * delta_dist_y;
// 	}
// // 
// 	while (hit == 0)
// 	{
// 		if (side_dist_x < side_dist_y)
// 		{
// 			side_dist_x += delta_dist_x;
// 			map_x += step_x;
// 			side = 0;
// 		}
// 		else
// 		{
// 			side_dist_y += delta_dist_y;
// 			map_y += step_y;
// 			side = 1;
// 		}
// 		printf("%d, %d\n", map_x, map_y);
// 		if (test_map[map_y][map_x] > '0')
// 			hit = 1;
// 	}
// 	if (side == 0)
// 		return (side_dist_x - delta_dist_x);
// 	else
// 		return (side_dist_y - delta_dist_y);
// }

// void	initialise_game(t_game *game)
// {
// 	// game->player->x = 4.2;
// 	// game->player->y = 4.2;
// 	game->plane_x = 0;
// 	game->plane_y = 0.66;
// 	game->dir_x = -1;
// 	game->dir_y = 0;
// }

// t_ray	*initialise_ray(t_ray *ray)
// {
// 	ray->delta_dist_x = ;
// 	ray->delta_dist_y;
// 	ray->ray_dir_x;
// 	ray->ray_dir_y;
// 	ray->side_dist_x;
// 	ray->side_dist_y;
// }

/*Miscellenous function*/
// void	printPlayerData(t_player *player)
// {
// 	if (player)
// 	{
// 		printf("Player x: %f\n", player->x);
// 		printf("Player y: %f\n", player->y);
// 		printf("Player orientation: %c\n", player->orientation);
// 	}
// }


void dda(t_data *data, int x)
{
	t_ray		*ray;
	double		camera_x = 2 * x / (double)WIDTH - 1;
	int			hit = 0; 
	int			side;
	// char		test_map[8][9] =
	// {
	// 	"1111111\n",
	// 	"1000001\n",
	// 	"10S0001\n",
	// 	"1000001\n",
	// 	"1000001\n",
	// 	"1000001\n",
	// 	"1111111\0"
	// };
	// game.player = (data->player);
	// printPlayerData(game.player);
	// initialise_game(&game);
	ray = data->ray;

	ray->map_x = (int)data->player->x;
	ray->map_y = (int)data->player->y;

	ray->ray_dir_x = data->player->dir_x + data->player->plane_x * camera_x;
	ray->ray_dir_y = data->player->dir_y + data->player->plane_y * camera_x;

	//Which box of the map are we in?
	ray->map_x = (int)data->player->x;
	ray->map_y = (int)data->player->y;

	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);

	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);


	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (data->player->x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->delta_dist_x = (ray->map_x + 1.0 - data->player->x) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->delta_dist_y = (data->player->y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - data->player->y) * ray->delta_dist_y;
	}
	while (hit == 0)
	{
		// jump to next map square, either in x-direction, or in y-direction
		if (ray->side_dist_x < ray->delta_dist_y)
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
		if (data->map.map[ray->map_y][ray->map_x] > '0')
			hit = 1;
		// if (test_map[ray->map_x][ray->map_y] > '0')
		// 	hit = 1;
	}
	if (side == 0)
		ray->distance = (ray->side_dist_x - ray->delta_dist_x);
	else
		ray->distance = (ray->side_dist_y - ray->delta_dist_y);
	// return (ray->distance);
}
