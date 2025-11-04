#include "cub3D.h"

// Calculate sprite distances to player
void update_sprite_distances(t_data *data)
{
    int i;
    double dx, dy;
    
    i = -1;
    while (++i < data->sprite_count)
    {
        dx = data->player->x - data->sprites[i].x;
        dy = data->player->y - data->sprites[i].y;
        // Store squared distance (faster, still works for sorting)
        data->sprites[i].distance = dx * dx + dy * dy;
    }
}

void    sort_sprites(t_data *data)
{
    int     i;
    int     j;
    t_sprite    tmp;

    i = -1;
    while (++i < data->sprite_count)
    {
        j = i;
        while (++j < data->sprite_count)
        {
            if (data->sprites[i].distance < data->sprites[j].distance)
            {
                tmp = data->sprites[i];
                data->sprites[i] = data->sprites[j];
                data->sprites[j] = tmp;
            }
        }
    }
}

// Draw a single sprite stripe (vertical column)
void draw_sprite_stripe(t_data *data, t_sprite *sprite, int x, 
                        int draw_start_y, int draw_end_y, int tex_x, double depth)
{
    int y;
    int tex_y;
    double step;
    double tex_pos;
    unsigned int color;
    
    // Check if sprite is behind wall at this x coordinate
    if (x < 0 || x >= WIDTH || depth >= data->zbuffer[x])
        return;
    
    // Calculate step and starting texture position
    step = 1.0 * data->textures.sprite.height / (draw_end_y - draw_start_y);
    tex_pos = (draw_start_y - HEIGHT / 2 + (draw_end_y - draw_start_y) / 2) * step;
    
    // Clamp to screen bounds
    if (draw_start_y < 0)
    {
        tex_pos += -draw_start_y * step;
        draw_start_y = 0;
    }
    if (draw_end_y > HEIGHT)
        draw_end_y = HEIGHT;
    
    y = draw_start_y - 1;
    while (++y < draw_end_y)
    {
        tex_y = (int)tex_pos & (data->textures.sprite.height - 1);
        tex_pos += step;
        
        color = get_pixel_img(&data->textures.sprite, tex_x, tex_y);
        
        // Check for transparency (black or specific color key)
        // Using 0x00FFFFFF mask checks if color is not pure black
        if ((color & 0x00FFFFFF) != 0)
        {
            pixel_put(x, y, &data->img, color);
        }
    }
}

// Project and render all sprites
void render_sprites(t_data *data)
{
    int i, x;
    t_sprite *sprite;
    double sprite_x, sprite_y;
    double inv_det;
    double transform_x, transform_y;
    int sprite_screen_x;
    int sprite_height, sprite_width;
    int draw_start_y, draw_end_y;
    int draw_start_x, draw_end_x;
    int tex_x;
    
    i = -1;
    while (++i < data->sprite_count)
    {
        sprite = &data->sprites[i];
        
        // Translate sprite position relative to camera
        sprite_x = sprite->x - data->player->x;
        sprite_y = sprite->y - data->player->y;
        
        // Transform sprite with inverse camera matrix
        // [ planeX   dirX ] [ spriteX ]
        // [ planeY   dirY ] [ spriteY ]
        inv_det = 1.0 / (data->game->plane_x * data->game->dir_y - 
                         data->game->dir_x * data->game->plane_y);
        
        transform_x = inv_det * (data->game->dir_y * sprite_x - 
                                 data->game->dir_x * sprite_y);
        transform_y = inv_det * (-data->game->plane_y * sprite_x + 
                                 data->game->plane_x * sprite_y);
        
        // Sprite is behind player
        if (transform_y <= 0.1)
            continue;
        
        // Calculate sprite screen position
        sprite_screen_x = (int)((WIDTH / 2) * (1 + transform_x / transform_y));
        
        // Calculate sprite height and width
        sprite_height = abs((int)(HEIGHT / transform_y));
        sprite_width = abs((int)(HEIGHT / transform_y)); // Square sprites
        
        // Calculate draw boundaries
        draw_start_y = -sprite_height / 2 + HEIGHT / 2;
        draw_end_y = sprite_height / 2 + HEIGHT / 2;
        
        draw_start_x = -sprite_width / 2 + sprite_screen_x;
        draw_end_x = sprite_width / 2 + sprite_screen_x;
        
        // Clamp to screen width
        if (draw_start_x < 0)
            draw_start_x = 0;
        if (draw_end_x > WIDTH)
            draw_end_x = WIDTH;
        
        // Draw each vertical stripe of the sprite
        x = draw_start_x - 1;
        while (++x < draw_end_x)
        {
            // Calculate texture X coordinate
            tex_x = (int)(256 * (x - (-sprite_width / 2 + sprite_screen_x)) * 
                         data->textures.sprite.width / sprite_width) / 256;
            
            // Ensure tex_x is within bounds
            if (tex_x < 0)
                tex_x = 0;
            if (tex_x >= data->textures.sprite.width)
                tex_x = data->textures.sprite.width - 1;
            
            // Draw this stripe if not occluded by walls
            draw_sprite_stripe(data, sprite, x, draw_start_y, draw_end_y, 
                             tex_x, transform_y);
        }
    }
}

// // Modified render function
// void render(t_data *data)
// {
//     int x;
//     t_ray *r;
    
//     x = 0;
//     r = data->ray;
    
//     // 1. Draw floor and ceiling
//     draw_floor_and_ceiling(data);
    
//     // 2. Draw walls and fill zbuffer
//     while (x < WIDTH)
//     {
//         r->tile = '0';
//         r->door = NULL;
//         dda(data, x);
//         r->line_height = (int)(HEIGHT / r->distance);
//         calculate_wall_bounds(data);
//         draw_vertical_line(data, x);
        
//         // Store distance for sprite occlusion testing
//         data->zbuffer[x] = r->distance;
//         x++;
//     }
    
//     // 3. Calculate sprite distances and sort
//     update_sprite_distances(data);
//     sort_sprites(data);
    
//     // 4. Draw sprites (back to front)
//     render_sprites(data);
    
//     // 5. Draw gun/weapon
//     draw_gun(data);
    
//     // 6. Draw minimap
//     draw_minimap(data);
    
//     // 7. Display everything
//     mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
    
//     // 8. Draw crosshair on top
//     draw_crosshair(data);
// }

