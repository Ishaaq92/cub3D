/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaladeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 15:12:10 by aaladeok          #+#    #+#             */
/*   Updated: 2025/11/05 15:12:14 by aaladeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	bound_checks(t_data *d)
{
	if (d->ray->tex_x >= d->textures.floor.width)
		d->ray->tex_x = d->textures.floor.width - 1;
	if (d->ray->tex_y >= d->textures.floor.height)
		d->ray->tex_y = d->textures.floor.height - 1;
}

void	get_tex_coordinate(t_data *d, t_tex_calc *tex)
{
	float	frac_x;
	float	frac_y;

	frac_x = fmod(tex->world_x, 1.0);
	frac_y = fmod(tex->world_y, 1.0);
	if (frac_x < 0)
		frac_x += 1.0;
	if (frac_y < 0)
		frac_y += 1.0;
	d->ray->tex_x = (int)(frac_x * d->textures.floor.width);
	d->ray->tex_y = (int)(frac_y * d->textures.floor.height);
}

void	compute_and_draw(t_data *d, float sx, float sy, int y)
{
	int			x;
	t_tex_calc	tex;

	x = 0;
	tex.fx = d->ray->floor_x;
	tex.fy = d->ray->floor_y;
	tex.tex_scale = 1.0;
	while (x < WIDTH)
	{
		tex.world_x = tex.fx * tex.tex_scale;
		tex.world_y = tex.fy * tex.tex_scale;
		get_tex_coordinate(d, &tex);
		bound_checks(d);
		tex.fcol = get_pixel_img(&d->textures.floor, d->ray->tex_x,
				d->ray->tex_y);
		tex.ccol = get_pixel_img(&d->textures.roof, d->ray->tex_x,
				d->ray->tex_y);
		pixel_put(x, y, &d->img, tex.fcol);
		pixel_put(x, HEIGHT - y - 1, &d->img, tex.ccol);
		tex.fx += sx;
		tex.fy += sy;
		x++;
	}
}

void	draw_floor_row(t_data *d, int y, float rdx0, float rdy0, float rdx1,
		float rdy1)
{
	float	p;
	float	step_x;
	float	step_y;

	p = (y - HEIGHT / 2.0);
	if (d->ray == NULL)
		printf("D ray is empty\n");
	d->ray->row_dist = (0.5 * HEIGHT) / p;
	d->ray->row_dist = fmin(d->ray->row_dist, 20.0);
	step_x = d->ray->row_dist * (rdx1 - rdx0) / WIDTH;
	step_y = d->ray->row_dist * (rdy1 - rdy0) / WIDTH;
	d->ray->floor_x = d->player->x + d->ray->row_dist * rdx0;
	d->ray->floor_y = d->player->y + d->ray->row_dist * rdy0;
	compute_and_draw(d, step_x, step_y, y);
}

void	draw_floor_and_ceiling(t_data *d)
{
	int		y;
	float	ray_dirx0;
	float	ray_diry0;
	float	ray_dirx1;
	float	ray_dir_y1;

	ray_dirx0 = d->game->dir_x - d->game->plane_x;
	ray_diry0 = d->game->dir_y - d->game->plane_y;
	ray_dirx1 = d->game->dir_x + d->game->plane_x;
	ray_dir_y1 = d->game->dir_y + d->game->plane_y;
	y = HEIGHT / 2 + 10;
	while (y < HEIGHT)
	{
		draw_floor_row(d, y, ray_dirx0, ray_diry0, ray_dirx1, ray_dir_y1);
		y++;
	}
}
