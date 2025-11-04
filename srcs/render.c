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
    double easedopen_width = ease_in_out_cubic(door->open_width);
    
    // Calculate texture with slide
    double tex_x_f = ray->wall_x + easedopen_width;
    
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

// Get the correct door texture frame
t_img *get_door_texture(t_data *data, t_door *door)
{
    int frame;
    
    if (!door)
        return &data->textures.door_arr.frames[0]; // Fallback to closed
    
    frame = door->current_frame;
    
    // Validate frame index
    if (frame < 0)
        frame = 0;
    if (frame >= data->textures.door_arr.frame_count)
        frame = data->textures.door_arr.frame_count - 1;
    
    return &data->textures.door_arr.frames[frame];
}

// SIMPLIFIED choose_texture - just picks the right frame
t_img *choose_texture(t_data *data)
{
    t_img *texture;
    
    // If it's a door, return the appropriate animation frame
    if (data->ray->tile == 'D' && data->ray->door)
    {
        return get_door_texture(data, data->ray->door);
    }
    
    // Regular wall texture selection
    if (data->ray->side == 0) // vertical wall (X-side)
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
    return texture;
}

// SIMPLIFIED draw_wall_with_tex - no texture shifting needed!
void draw_wall_with_tex(t_data *data, t_img *texture, int x)
{
    int             y;
    t_ray           *ray;
    unsigned int    color;

    ray = data->ray;
    // Check if door is visible (>90% open means see-through)
    if (ray->tile == 'D' && ray->door && ray->door->open_width >= 0.9)
        return; // Door is transparent, wall behind it was already rendered.
    y = ray->draw_start;
    while (y < ray->draw_end)
    {
        ray->tex_y = (int)ray->tex_pos & (texture->height - 1);
        ray->tex_pos += ray->step;
        color = get_pixel_img(texture, ray->tex_x, ray->tex_y);
        // Skip black pixels - they're transparent
        if ((color & 0x00FFFFFF) == 0)
        {
            y++;
            continue; // Don't draw, show floor/ceiling behind
        }
        // Optional: Add slight fade as door becomes nearly open
        if (ray->tile == 'D' && ray->door && ray->door->open_width > 0.8)
        {
            double fade = 1.0 - ((ray->door->open_width - 0.8) / 0.2);
            color = apply_alpha(color, fade);
        }
        
        pixel_put(x, y, &data->img, color);
        y++;
    }
}

// Simplified draw_vertical_line - no door-specific code needed!
void draw_vertical_line(t_data *data, int x)
{
    t_ray   *r;
    t_img   *tex;

    r = data->ray;
    
    // Choose texture (automatically handles door frames)
    tex = choose_texture(data);
    
    // Calculate exact hit location on wall (for tex_x)
    calculate_hitside(data);
    
    // Convert wall_x to texture x-coordinate
    r->tex_x = (int)(r->wall_x * tex->width);
    if ((r->side == 0 && r->ray_dir_x > 0) || 
        (r->side == 1 && r->ray_dir_y < 0))
        r->tex_x = tex->width - r->tex_x - 1;
    
    // Calculate step and starting position for texture y-coordinate
    r->step = 1.0 * tex->height / r->line_height;
    r->tex_pos = (r->draw_start - HEIGHT / 2 + r->line_height / 2) * r->step;
    
    // Draw the wall/door
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


// Modified render function
void render(t_data *data)
{
    int x;
    t_ray *r;
    
    x = 0;
    r = data->ray;
    
    // 1. Draw floor and ceiling
    draw_floor_and_ceiling(data);
    
    // 2. Draw walls and fill zbuffer
    while (x < WIDTH)
    {
        r->tile = '0';
        r->door = NULL;
        dda(data, x);
        r->line_height = (int)(HEIGHT / r->distance);
        calculate_wall_bounds(data);
        draw_vertical_line(data, x);
        
        // Store distance for sprite occlusion testing
        data->zbuffer[x] = r->distance;
        x++;
    }
    
    // 3. Calculate sprite distances and sort
    update_sprite_distances(data);
    sort_sprites(data);
    
    // 4. Draw sprites (back to front)
    render_sprites(data);
    
    // 5. Draw gun/weapon
    draw_gun(data);
    
    // 6. Draw minimap
    draw_minimap(data);
    
    // 7. Display everything
    mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
    
    // 8. Draw crosshair on top
    draw_crosshair(data);
}

