#include <math.h>
#include <stdio.h>

#define DOOR_FRAMES 32       // Number of door animation frames
#define DOOR_SPEED 0.8       // Seconds to fully open
#define DOOR_HOLD_TIME 3.0   // Seconds door stays open
#define DOOR_CLOSE_SPEED 0.5 // Seconds to fully close

// Door texture structure - holds all animation frames
typedef struct s_door_tex {
    t_img   frames[DOOR_FRAMES];  // Array of 32 door frames
    int     frame_count;           // Should be 32
} t_door_tex;

// Updated door structure
typedef struct s_door {
    int     x;
    int     y;
    double  open_amount;      // 0.0 = closed, 1.0 = fully open (replaces open_width)
    int     state;            // 0=closed, 1=opening, 2=open, 3=closing
    double  timer;
    int     current_frame;    // Current animation frame (0-31)
} t_door;

// Smooth easing function for natural acceleration/deceleration
double ease_in_out_cubic(double t)
{
    if (t < 0.5)
        return 4.0 * t * t * t;
    else
    {
        double f = (2.0 * t - 2.0);
        return 1.0 + f * f * f / 2.0;
    }
}

// Load all 32 door animation frames
int load_door_frames(t_data *data)
{
    char    path[256];
    int     i;
    int     width, height;
    
    printf("Loading door animation frames...\n");
    
    i = 0;
    while (i < DOOR_FRAMES)
    {
        // Generate filename: "textures/door_00.xpm", "textures/door_01.xpm", etc.
        snprintf(path, sizeof(path), "textures/door_%02d.xpm", i);
        
        data->textures.door_arr.frames[i].img = mlx_xpm_file_to_image(
            data->mlx, path, &width, &height);
        
        if (!data->textures.door_arr.frames[i].img)
        {
            printf("Error: Failed to load %s\n", path);
            return 0;
        }
        
        data->textures.door_arr.frames[i].addr = mlx_get_data_addr(
            data->textures.door_arr.frames[i].img,
            &data->textures.door_arr.frames[i].bpp,
            &data->textures.door_arr.frames[i].line_len,
            &data->textures.door_arr.frames[i].endian);
        
        data->textures.door_arr.frames[i].width = width;
        data->textures.door_arr.frames[i].height = height;
        
        i++;
    }
    
    data->textures.door_arr.frame_count = DOOR_FRAMES;
    printf("Successfully loaded %d door frames\n", DOOR_FRAMES);
    return 1;
}

// Get the appropriate door frame based on open_amount
int get_door_frame(t_door *door, int total_frames)
{
    int frame;
    double eased;
    
    // Apply easing for smooth animation
    eased = ease_in_out_cubic(door->open_amount);
    
    // Map 0.0-1.0 to frame index 0-(total_frames-1)
    frame = (int)(eased * (total_frames - 1));
    
    // Clamp to valid range
    if (frame < 0)
        frame = 0;
    if (frame >= total_frames)
        frame = total_frames - 1;
    
    return frame;
}

// Update door animations (call every frame with delta_time)
void update_doors(t_data *data, double delta_time)
{
    int     i;
    t_door  *door;
    double  speed;

    i = -1;
    while (++i < data->door_count)
    {
        door = &data->doors[i];
        
        if (door->state == 1) // Opening
        {
            speed = delta_time / DOOR_SPEED;
            door->open_amount += speed;
            
            if (door->open_amount >= 1.0)
            {
                door->open_amount = 1.0;
                door->state = 2; // Fully open
                door->timer = 0.0;
            }
            
            // Update current frame based on open_amount
            door->current_frame = get_door_frame(door, DOOR_FRAMES);
        }
        else if (door->state == 3) // Closing
        {
            speed = delta_time / DOOR_CLOSE_SPEED;
            door->open_amount -= speed;
            
            if (door->open_amount <= 0.0)
            {
                door->open_amount = 0.0;
                door->state = 0; // Fully closed
                data->map.map[door->y][door->x] = 'D';
            }
            
            // Update current frame
            door->current_frame = get_door_frame(door, DOOR_FRAMES);
        }
        else if (door->state == 2) // Fully open, waiting
        {
            door->timer += delta_time;
            if (door->timer >= DOOR_HOLD_TIME)
            {
                door->state = 3; // Start closing
            }
        }
        
        // Update collision - door is passable when mostly open
        if (door->open_amount > 0.7)
            data->map.map[door->y][door->x] = '0'; // Passable
        else
            data->map.map[door->y][door->x] = 'D'; // Solid
    }
}

// Modified DDA to handle open doors
void perform_dda(t_ray *ray, char **map, t_data *data)
{
    int     hit;
    t_door  *door;

    hit = 0;
    while (hit == 0)
    {
        if (ray->side_dist_x < ray->side_dist_y)
        {
            ray->side_dist_x += ray->delta_dist_x;
            ray->map_x += ray->step_x;
            ray->side = 0;
        }
        else
        {
            ray->side_dist_y += ray->delta_dist_y;
            ray->map_y += ray->step_y;
            ray->side = 1;
        }

        char tile = map[ray->map_y][ray->map_x];
        
        if (tile == 'D')
        {
            door = find_door(data, ray->map_x, ray->map_y);
            
            // If door is 90% or more open, raycast through it
            if (door && door->open_amount >= 0.9)
            {
                continue; // Keep raycasting to find wall behind
            }
            else
            {
                hit = 1;
                ray->tile = tile;
                ray->door = door;
            }
        }
        else if (tile == '1')
        {
            hit = 1;
            ray->tile = tile;
            ray->door = NULL;
        }
    }

    // Calculate distance (unchanged)
    if (ray->side == 0)
        ray->distance = (ray->map_x - data->player->x + 
                        (1 - ray->step_x) / 2) / ray->ray_dir_x;
    else
        ray->distance = (ray->map_y - data->player->y + 
                        (1 - ray->step_y) / 2) / ray->ray_dir_y;
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
    if (ray->tile == 'D' && ray->door && ray->door->open_amount >= 0.9)
    {
        return; // Door is transparent, wall behind it was already rendered
    }
    
    y = ray->draw_start;
    while (y < ray->draw_end)
    {
        ray->tex_y = (int)ray->tex_pos & (texture->height - 1);
        ray->tex_pos += ray->step;
        color = get_pixel_img(texture, ray->tex_x, ray->tex_y);
        
        // Optional: Add slight fade as door becomes nearly open
        if (ray->tile == 'D' && ray->door && ray->door->open_amount > 0.8)
        {
            double fade = 1.0 - ((ray->door->open_amount - 0.8) / 0.2);
            color = apply_alpha(color, fade);
        }
        
        pixel_put(x, y, &data->img, color);
        y++;
    }
}

// Helper function for alpha blending
unsigned int apply_alpha(unsigned int color, double alpha)
{
    int r, g, b;
    
    if (alpha >= 1.0)
        return color;
    if (alpha <= 0.0)
        return 0;
    
    r = ((color >> 16) & 0xFF) * alpha;
    g = ((color >> 8) & 0xFF) * alpha;
    b = (color & 0xFF) * alpha;
    
    return (r << 16) | (g << 8) | b;
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

// Automatic door opening - checks proximity to player
void check_auto_doors(t_data *data)
{
    int     i;
    t_door  *door;
    double  dx, dy, dist;
    
    i = -1;
    while (++i < data->door_count)
    {
        door = &data->doors[i];
        
        // Calculate distance from player to door center
        dx = door->x + 0.5 - data->player->x;
        dy = door->y + 0.5 - data->player->y;
        dist = sqrt(dx * dx + dy * dy);
        
        // Auto-open if player is within 2 units and door is closed
        if (dist < 2.0 && door->state == 0)
        {
            door->state = 1;  // Start opening
            door->timer = 0.0;
            printf("Door at (%d, %d) opening automatically\n", door->x, door->y);
        }
        // If player moves away while door is open, let it auto-close
        // (the timer in update_doors handles this)
    }
}

// Optional: Manual trigger if you want to add it later
void open_door(t_data *data, int map_x, int map_y)
{
    t_door *door = find_door(data, map_x, map_y);
    
    if (door)
    {
        if (door->state == 0 || door->state == 3) // Closed or closing
        {
            door->state = 1; // Start opening
            door->timer = 0.0;
        }
        else if (door->state == 2) // Already open
        {
            door->timer = 0.0; // Reset timer
        }
    }
}

// Initialize doors with new fields
void init_doors(t_data *data)
{
    int     x, y, count;
    t_door  *door;
    
    // Count doors
    count = 0;
    y = -1;
    while (++y < data->map.height)
    {
        x = -1;
        while (++x < data->map.width)
        {
            if (data->map.map[y][x] == 'D')
                count++;
        }
    }
    
    data->door_count = count;
    printf("Found %d doors\n", count);
    
    // Initialize each door
    count = 0;
    y = -1;
    while (++y < data->map.height)
    {
        x = -1;
        while (++x < data->map.width)
        {
            if (data->map.map[y][x] == 'D')
            {
                door = &data->doors[count];
                door->x = x;
                door->y = y;
                door->open_amount = 0.0;     // NEW: replaces open_width
                door->state = 0;             // NEW: replaces opening
                door->timer = 0.0;
                door->current_frame = 0;     // NEW: starts at frame 0 (closed)
                count++;
            }
        }
    }
}

// Call this in your main initialization
void init_game(t_data *data)
{
    // ... existing MLX initialization ...
    
    // Load wall textures
    // load_wall_textures(data);
    
    // Load all 32 door animation frames
    if (!load_door_frames(data))
    {
        printf("Error: Failed to load door animation frames\n");
        exit(1);
    }
    
    // Initialize doors
    init_doors(data);
    
    // ... rest of initialization ...
}

// In your game loop - this is the most important part!
int game_loop(t_data *data)
{
    double current_time = get_time();
    double delta_time = current_time - data->prev_time;
    data->prev_time = current_time;
    
    update_movement(data);
    check_auto_doors(data);      // ← CHECK DOORS EVERY FRAME!
    update_doors(data, delta_time);  // Update door animations
    render(data);
    
    return 0;
}