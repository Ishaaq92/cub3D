/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 16:12:40 by isahmed           #+#    #+#             */
/*   Updated: 2025/10/09 16:58:16 by isahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	pixel_put(int x, int y, t_img *img, int colour)
{
	char	*pixel;

	if (x >= 0 && y >= 0 && x < WIDTH && y < HEIGHT)
	{
		pixel = img->pxls + (y * img->line_length + x * (img->bpp / 8));
		*(unsigned int *)pixel = colour;
	}
}

unsigned int	get_pixel_img(t_img *img, int x, int y)
{
	unsigned char	*dst;
	int				offset;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return (0);
	offset = y * img->line_length + x * (img->bpp / 8);
	dst = (unsigned char *)img->pxls + offset;
	// Return as 0x00RRGGBB for easier usage
	return ((dst[2] << 16) | (dst[1] << 8) | dst[0]);
}

void	calculate_wall_bounds(t_data *data)
{
	t_ray	*ray;

	ray = data->ray;
	ray->draw_start = (-ray->line_height / 2) + (HEIGHT / 2);
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = (ray->line_height / 2) + (HEIGHT / 2);
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
}

// Helper function for alpha blending (optional fade effect)
unsigned int apply_alpha(unsigned int color, double alpha)
{
    if (alpha >= 1.0)
        return color;
    if (alpha <= 0.0)
        return 0; // Fully transparent
    
    int r = ((color >> 16) & 0xFF) * alpha;
    int g = ((color >> 8) & 0xFF) * alpha;
    int b = (color & 0xFF) * alpha;
    
    return (r << 16) | (g << 8) | b;
}
// Modified wall rendering to handle sliding door texture
void calculate_door_texture(t_ray *ray, t_img *texture)
{
    t_door *door = ray->door;
    
    if (!door || door->open_width <= 0.0)
    {
        // Normal texture calculation
        ray->tex_x = (int)(ray->wall_x * texture->width);
        if ((ray->side == 0 && ray->ray_dir_x > 0) || 
            (ray->side == 1 && ray->ray_dir_y < 0))
            ray->tex_x = texture->width - ray->tex_x - 1;
        ray->is_door_visible = 1;
        return;
    }
    
    // Apply easing
    double eased_amount = ease_in_out_cubic(door->open_width);
    
    // Calculate texture with slide
    double tex_x_f = ray->wall_x + eased_amount;
    
    // If less than 90% open, still render the door
    if (door->open_width < 0.9)
    {
        ray->is_door_visible = 1;
        ray->tex_x = (int)(tex_x_f * texture->width);
        
        if ((ray->side == 0 && ray->ray_dir_x > 0) || 
            (ray->side == 1 && ray->ray_dir_y < 0))
            ray->tex_x = texture->width - ray->tex_x - 1;
        
        if (ray->tex_x < 0)
            ray->tex_x = 0;
        if (ray->tex_x >= texture->width)
            ray->tex_x = texture->width - 1;
    }
    else
    {
        // Door is 90%+ open - don't render it
        // (the DDA will have already found the wall behind it)
        ray->is_door_visible = 0;
    }
}

void	calculate_hitside(t_data *data)
{
	t_ray	*ray;

	ray = data->ray;
	// Calculate exact hit location on wall (for tex_x)
	if (ray->side == 0)
		ray->wall_x = data->player->y + ray->distance * ray->ray_dir_y;
	else
		ray->wall_x = data->player->x + ray->distance * ray->ray_dir_x;
	// get fractional part (0.0 to 1.0)
	ray->wall_x -= floor(ray->wall_x);
}

t_img	*choose_texture(t_data *data)
{
	t_img	*texture;

	if (data->ray->tile == 'D')
		texture = &data->textures.door;
	else if (data->ray->side == 0) // vertical wall (X-side)
	{
		if (data->ray->ray_dir_x < 0)
			texture = &data->textures.west;
		else
			texture = &data->textures.east;
	}
	else // horizontal wall (Y-side)
	{
		if (data->ray->ray_dir_y < 0)
			texture = &data->textures.north;
		else
			texture = &data->textures.south;
	}
	return (texture);
}

void draw_wall_with_tex(t_data *data, t_img *texture, int x)
{
    int             y;
    t_ray           *ray;
    unsigned int    color;

    ray = data->ray;
    
    // If it's a door and not visible (slid away), don't draw
    if (ray->tile == 'D' && ray->door)
    {
        calculate_door_texture(ray, texture);
        
        if (!ray->is_door_visible)
            return; // Door has slid completely away
    }
    
    y = ray->draw_start;
    while (y < ray->draw_end)
    {
        ray->tex_y = (int)ray->tex_pos & (texture->height - 1);
        ray->tex_pos += ray->step;
        color = get_pixel_img(texture, ray->tex_x, ray->tex_y);
        
        // Optional: Add transparency effect as door opens
        if (ray->tile == 'D' && ray->door && ray->door->open_width > 0.7)
        {
            // Fade out near full open
            double fade = (1.0 - ray->door->open_width) / 0.3;
            color = apply_alpha(color, fade);
        }
        
        pixel_put(x, y, &data->img, color);
        y++;
    }
}

void	draw_vertical_line(t_data *data, int x)
{
	t_ray	*r;
	t_img	*tex;

	r = data->ray;
	// Choose texture
	tex = choose_texture(data);
	// 2. Calculate exact hit location on wall (for tex_x)
	calculate_hitside(data);
	// 3. Convert wall_x to texture x-coordinate
	r->tex_x = (int)(r->wall_x * tex->width);
	if ((r->side == 0 && r->ray_dir_x > 0) || (r->side == 1
			&& r->ray_dir_y < 0))
		r->tex_x = tex->width - r->tex_x - 1;
	// 4. Calculate step and starting position for texture y-coordinate
	r->step = 1.0 * tex->height / r->line_height;
	r->tex_pos = (r->draw_start - HEIGHT / 2 + r->line_height / 2)
		* r->step;
	draw_wall_with_tex(data, tex, x);
}

void	draw_crosshair(t_data *data)
{
	int	x;
	int	y;

	x = WIDTH / 2 - 9;
	while (++x < (WIDTH / 2 + 10))
		pixel_put(x, HEIGHT / 2, &data->img, 0xFFFFFF);
	y = HEIGHT / 2 - 9;
	while (++y < (HEIGHT / 2 + 10))
		pixel_put(WIDTH / 2, y, &data->img, 0xFFFFFF);
}


void render(t_data *data)
{
    if (!data->ray)
        data->ray = malloc(sizeof(t_ray)); // consider moving this to init()

    draw_floor_and_ceiling(data);
    for (int x = 0; x < WIDTH; x++)
    {
        t_ray *r = data->ray;

        // Reset per-column values
        r->tile = '0';
        r->door = NULL;

        dda(data, x);
        r->line_height = (int)(HEIGHT / r->distance);
        calculate_wall_bounds(data);
        draw_vertical_line(data, x);
    }
    draw_gun(data);
    mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
    draw_crosshair(data);
}
