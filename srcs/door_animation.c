# include "cub3D.h"

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