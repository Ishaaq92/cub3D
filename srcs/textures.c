#include "cub3D.h"

t_img	load_xpm_to_img(void *mlx, char *path)
{
	t_img	tex;

	tex.img = mlx_xpm_file_to_image(mlx, path, &tex.width, &tex.height);
	if (!tex.img)
	{
		printf("Error: unable to load XPM file: %s\n", path);
		return ((t_img){0});
	}
	tex.pxls = mlx_get_data_addr(tex.img, &tex.bpp, &tex.line_length,
			&tex.endian);
	return (tex);
}

void    check_fractions(float *frac_x, float *frac_y)
{
    if (*frac_x < 0)
		*frac_x += 1.0;
	if (*frac_y < 0)
		*frac_y += 1.0;
}

void    bound_checks(t_data *d)
{
    if (d->ray->tex_x >= d->textures.floor.width)
		d->ray->tex_x = d->textures.floor.width - 1;
	if (d->ray->tex_y >= d->textures.floor.height)
	    d->ray->tex_y = d->textures.floor.height - 1;
}

void    get_tex_coordinate(t_data *d, t_tex_calc *tex)
{
    d->ray->tex_x = (int)(tex->frac_x * d->textures.floor.width) 
		% d->textures.floor.width;
	d->ray->tex_y = (int)(tex->frac_y * d->textures.floor.height) 
		% d->textures.floor.height;
}

void	compute_and_draw(t_data *d, float sx, float sy, int y)
{
	int				x;
    t_tex_calc          tex;

	x = 0;
	tex.fx = d->ray->floor_x;
	tex.fy = d->ray->floor_y;
	while (x < WIDTH)
	{
		tex.cell_x = (int)floor(tex.fx); // Get the map cell (floor to integer)
		tex.cell_y = (int)floor(tex.fy);
		tex.frac_x = tex.fx - tex.cell_x; // Get fractional part (always 0.0 to 1.0)
		tex.frac_y = tex.fy - tex.cell_y;
		check_fractions(&tex.frac_x, &tex.frac_y); // Make sure fractions are positive
		get_tex_coordinate(d, &tex); // Calculate texture coordinates
		d->ray->tex_x = abs(d->ray->tex_x);// Absolute value to ensure positive
		d->ray->tex_y = abs(d->ray->tex_y);
		bound_checks(d); 	// Additional safety bounds check
		tex.fcol = get_pixel_img(&d->textures.floor, d->ray->tex_x, d->ray->tex_y);
		tex.ccol = get_pixel_img(&d->textures.roof, d->ray->tex_x, d->ray->tex_y);
		pixel_put(x, y, &d->img, tex.fcol);
		pixel_put(x, HEIGHT - y - 1, &d->img, tex.ccol);
		tex.fx += sx;
		tex.fy += sy;
		x++;
	}
}

void	draw_floor_row(t_data *d, int y, float rdx0, float rdy0, float rdx1)
{
	float	step_x;
	float	step_y;

	d->ray->row_dist = (0.5 * HEIGHT) / (y - HEIGHT / 2.0);
	// d->ray->row_dist = fmin(d->ray->row_dist, 50.0);
	step_x = d->ray->row_dist * (rdx1 - rdx0) / WIDTH;
	step_y = d->ray->row_dist * (d->ray->rdy1 - rdy0) / WIDTH;
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

	ray_dirx0 = d->game->dir_x - d->game->plane_x;
	ray_diry0 = d->game->dir_y - d->game->plane_y;
	ray_dirx1 = d->game->dir_x + d->game->plane_x;
	d->ray->rdy1 = d->game->dir_y + d->game->plane_y;
	y = HEIGHT / 2 + 1; //or + 5
	while (y < HEIGHT)
	{
		draw_floor_row(d, y, ray_dirx0, ray_diry0, ray_dirx1);
		y++;
	}
}

// I am leaving this version here for you to understand how the entire thing works..
// void	draw_floor_and_ceiling(t_data *data)
// {
// 	int y;
// 	int x;
// 	int cell_x;
// 	int cell_y;
// 	int tex_x;
// 	int tex_y;
// 	float p;
// 	float pos_z;
// 	float step_x;
// 	float step_y;
// 	float floor_x;
// 	float floor_y;
// 	float row_dist;
// 	float ray_dir_x0;
// 	float ray_dir_x1;
// 	float ray_dir_y0;
// 	float ray_dir_y1;
// 	unsigned int floor_color;
// 	unsigned int ceil_color;

// 	ray_dir_x0 = data->game->dir_x - data->game->plane_x;
// 	ray_dir_y0 = data->game->dir_y - data->game->plane_y;
// 	ray_dir_x1 = data->game->dir_x + data->game->plane_x;
// 	ray_dir_y1 = data->game->dir_y + data->game->plane_y;

// 	// Distance from camera to floor
// 	y = HEIGHT / 2 + 1;
// 	while (y < HEIGHT)
// 	{
// 		p = y - HEIGHT / 2;
// 		pos_z = 0.5 * HEIGHT; // camera height
// 		row_dist = pos_z / p;

// 		// Step vectors across the screen
// 		step_x = row_dist * (ray_dir_x1 - ray_dir_x0) / WIDTH;
// 		step_y = row_dist * (ray_dir_y1 - ray_dir_y0) / WIDTH;

// 		// starting world coordinates
// 		floor_x = data->player->x + row_dist * ray_dir_x0;
// 		floor_y = data->player->y + row_dist * ray_dir_y0;
// 		x = 0;
// 		while (x < WIDTH)
// 		{
// 			cell_x = (int)floor_x;
// 			cell_y = (int)floor_y;

// 			tex_x = (int)(data->textures.floor.width * (floor_x - cell_x))
// 				% data->textures.floor.width;
// 			tex_y = (int)(data->textures.floor.height * (floor_y - cell_y))
// 				% data->textures.floor.height;
// 			floor_x += step_x;
// 			floor_y += step_y;

// 			// sample floor texture
// 			floor_color = get_pixel_img(&data->textures.floor, tex_x, tex_y);
// 			pixel_put(x, y, &data->img, floor_color);

// 			// Ceiling texture
// 			ceil_color = get_pixel_img(&data->textures.roof, tex_x, tex_y);
// 			pixel_put(x, HEIGHT - y, &data->img, ceil_color);
// 			x++;
// 		}
// 		y++;
// 	}
// }