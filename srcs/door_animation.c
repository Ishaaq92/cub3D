# include "cub3D.h"

// static int get_frame(t_data *data, int i, int width, int height)
// {
//     char    path[256];

//     //Generate filename: "textures/door_01.xpm" to "textures/door_32.xpm"
//     snprintf(path, sizeof(path), "./assets/door/Layer-1_sprite_%02d.xpm", i + 1);
    
//     data->textures.door_arr.frames[i].img = mlx_xpm_file_to_image(
//         data->mlx, path, &width, &height);
    
//     if (!data->textures.door_arr.frames[i].img)
//     {
//         printf("Error: Failed to load %s\n", path);
//         return 0;
//     }
    
//     data->textures.door_arr.frames[i].pxls = mlx_get_data_addr(
//         data->textures.door_arr.frames[i].img,
//         &data->textures.door_arr.frames[i].bpp,
//         &data->textures.door_arr.frames[i].line_length,
//         &data->textures.door_arr.frames[i].endian);
    
//     data->textures.door_arr.frames[i].width = width;
//     data->textures.door_arr.frames[i].height = height;
//     return (1);
// }

// // Load all 32 door animation frames (numbered 01-32)
// int load_door_frames(t_data *data)
// {
//     int     i;
//     int     width;
//     int     height;

//     width = 0;
//     height = 0;
//     printf("Loading door animation frames...\n");
    
//     i = 0;
//     while (i < DOOR_FRAMES)
//     {
//         if (!get_frame(data, i, width, height))
//             return (0);
//         i++;
//     }

//     data->textures.door_arr.frame_count = DOOR_FRAMES;
//     printf("Successfully loaded %d door frames (01-32)\n", DOOR_FRAMES);
//     return 1;
// }

// // Get the appropriate door frame based on open_width
// int get_door_frame(t_door *door, int total_frames)
// {
//     int frame;
//     double eased;
    
//     // Apply easing for smooth animation
//     eased = ease_in_out_cubic(door->open_width);
    
//     // Map 0.0-1.0 to frame index 0-(total_frames-1)
//     frame = (int)(eased * (total_frames - 1));
    
//     // Clamp to valid range
//     if (frame < 0)
//         frame = 0;
//     if (frame >= total_frames)
//         frame = total_frames - 1;
    
//     return frame;
// }

static void	update_door_opening(t_door *door, double delta_time)
{
	double	speed = delta_time / DOOR_SPEED;

	door->open_width += speed;
	if (door->open_width >= 1.0)
	{
		door->open_width = 1.0;
		door->state = 2;
		door->timer = 0.0;
	}
	door->current_frame = get_door_frame(door, DOOR_FRAMES);
}

static void	update_door_closing(t_door *door, t_data *data, double delta_time)
{
	double	speed = delta_time / DOOR_CLOSE_SPEED;

	door->open_width -= speed;
	if (door->open_width <= 0.0)
	{
		door->open_width = 0.0;
		door->state = 0;
		data->map.map[door->y][door->x] = 'D';
	}
	door->current_frame = get_door_frame(door, DOOR_FRAMES);
}

static void	update_door_timer(t_door *door)
{
	door->timer += 1.0 / 60.0; // or use global delta_time if preferred
	if (door->timer >= DOOR_HOLD_TIME)
		door->state = 3;
}

static void	update_door_collision(t_door *door, t_data *data)
{
	if (door->open_width > 0.7)
		data->map.map[door->y][door->x] = '0';
	else
		data->map.map[door->y][door->x] = 'D';
}

void	update_doors(t_data *data, double delta_time)
{
	int		i;
	t_door	*door;

	i = -1;
	while (++i < data->door_count)
	{
		door = &data->doors[i];
		if (door->state == 1)
			update_door_opening(door, delta_time);
		else if (door->state == 2)
			update_door_timer(door);
		else if (door->state == 3)
			update_door_closing(door, data, delta_time);
		update_door_collision(door, data);
	}
}


// Update door animations (call every frame with delta_time)
// void update_doors(t_data *data, double delta_time)
// {
//     int     i;
//     t_door  *door;
//     double  speed;

//     i = -1;
//     while (++i < data->door_count)
//     {
//         door = &data->doors[i];
        
//         if (door->state == 1) // Opening
//         {
//             speed = delta_time / DOOR_SPEED;
//             door->open_width += speed;
            
//             if (door->open_width >= 1.0)
//             {
//                 door->open_width = 1.0;
//                 door->state = 2; // Fully open
//                 door->timer = 0.0;
//             }
            
//             // Update current frame based on open_width
//             door->current_frame = get_door_frame(door, DOOR_FRAMES);
//         }
//         else if (door->state == 3) // Closing
//         {
//             speed = delta_time / DOOR_CLOSE_SPEED;
//             door->open_width -= speed;
            
//             if (door->open_width <= 0.0)
//             {
//                 door->open_width = 0.0;
//                 door->state = 0; // Fully closed
//                 data->map.map[door->y][door->x] = 'D';
//             }
            
//             // Update current frame
//             door->current_frame = get_door_frame(door, DOOR_FRAMES);
//         }
//         else if (door->state == 2) // Fully open, waiting
//         {
//             door->timer += delta_time;
//             if (door->timer >= DOOR_HOLD_TIME)
//             {
//                 door->state = 3; // Start closing
//             }
//         }
        
//         // Update collision - door is passable when mostly open
//         if (door->open_width > 0.7)
//             data->map.map[door->y][door->x] = '0'; // Passable
//         else
//             data->map.map[door->y][door->x] = 'D'; // Solid
//     }
// }