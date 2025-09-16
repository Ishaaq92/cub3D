/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:10:07 by isahmed           #+#    #+#             */
/*   Updated: 2025/09/16 20:25:52 by isahmed          ###   ########.fr       */
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

void	initialise_position(t_data *data)
{
	t_game	*game;

	game->player->x = 4.2;
	game->player->y = 4.2;
	game->plane_x = 0;
	game->plane_y = 0.66;
	game->dir_x = -1;
	game->dir_y = 0;
	
}

double dda(t_data *data, int x)
{
	char	test_map[8][9] =
	{
		"1111111\n",
		"1000001\n",
		"10S0001\n",
		"1000001\n",
		"1000001\n",
		"1000001\n",
		"1111111\0"
	};
	// initialise_position(data);
	double posX = 4.2, posY = 4.2;
	double dirX = -1, dirY = 0;
	double planeX = 0, planeY = 0.66; 

	double cameraX = 2 * x / (double)WIDTH - 1;
	double rayDirX = dirX + planeX * cameraX;
	double rayDirY = dirY + planeY * cameraX;

	int mapX = (int)posX;
	int mapY = (int)posY;

	double sideDistX;
	double sideDistY;

	double deltaDistX;
	double deltaDistY;

	double perpWallDist;

	int stepX;
	int stepY;
	int hit = 0; 
	int side;
	if (rayDirX == 0)
		deltaDistX = 1e30;
	else
		deltaDistX = fabs(1 / rayDirX);

	if (rayDirY == 0)
		deltaDistY = 1e30;
	else
		deltaDistY = fabs(1 / rayDirY);


	if (rayDirX < 0)
	{
		stepX = -1;
		sideDistX = (posX - mapX) * deltaDistX;
	}
	else
	{
		stepX = 1;
		sideDistX = (mapX + 1.0 - posX) * deltaDistX;
	}
	if (rayDirY < 0)
	{
		stepY = -1;
		sideDistY = (posY - mapY) * deltaDistY;
	}
	else
	{
		stepY = 1;
		sideDistY = (mapY + 1.0 - posY) * deltaDistY;
	}
	while (hit == 0)
	{
		// jump to next map square, either in x-direction, or in y-direction
		if (sideDistX < sideDistY)
		{
			sideDistX += deltaDistX;
			mapX += stepX;
			side = 0;
		}
		else
		{
			sideDistY += deltaDistY;
			mapY += stepY;
			side = 1;
		}
		if (test_map[mapX][mapY] > '0')
			hit = 1;
	}
	if (side == 0)
		perpWallDist = (sideDistX - deltaDistX);
	else
		perpWallDist = (sideDistY - deltaDistY);
	return (perpWallDist);
}
