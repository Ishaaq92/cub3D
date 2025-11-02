#include "cub3D.h"

// Smooth easing function for natural animation
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

// Trigger doo->state
void open_door(t_data *data, int map_x, int map_y)
{
    t_door *door = find_door(data, map_x, map_y);
    
    if (door && door->state != 1 && door->state != 2)
    {
        door->state = 1; // Star->state
        door->timer = 0.0;
    }
    else if (door && door->state == 2)
    {
        // If already open, reset the timer
        door->timer = 0.0;
    }
}

t_door *find_door(t_data *data, int x, int y)
{
    int i;
    t_door  *door;

    i = 0;
    while (i < data->door_count)
    {
        door = &data->doors[i];
        if (door->x == x && door->y == y)
            return (door);
        i++;
    }
    return (NULL);
}

void    check_doors(t_data *data)
{
    int i;
    double	dx;
	double	dy;
    t_door  *door;
    double  dist;

    i = -1;
    while (++i < data->door_count)
    {
        door = &data->doors[i];
        dx = (door->x + 0.5) - data->player->x;
        dy = (door->y + 0.5) - data->player->y;
        dist = sqrt(dx * dx + dy * dy);
        if (dist < 2.0 && door->open_width == 0.0)
        {
            door->state = 1;
            door->timer = 0;
        }
    }
}

void    update_doors(t_data *data, double delta_time)
{
    int i;
    t_door  *door;

    i = -1;
    while (++i < data->door_count)
    {
        door = &data->doors[i];
        if (door->state == 1)
        {
            door->open_width += delta_time / DOOR_SPEED;
            if (door->open_width >= 1.0)
            {
                door->open_width = 1.0;
                door->state = 0;
                door->timer = 0;
            }
        }
        else if (door->state == -1)
        {
            door->open_width -= delta_time / 0.5;
            if (door->open_width <= 0.0)
            {
                door->open_width = 0.0;
                door->state = 0;
            }
        }
        else if (door->open_width > 0.0)
        {
            door->timer += delta_time;
            if (door->timer > 3.0)
                door->state = -1;
        }
        if (door->open_width > 0.5)
            data->map.map[door->y][door->x] = '0';
        else
            data->map.map[door->y][door->x] = 'D';
    }
}

// void    check_doors(t_data *data)
// {
//     int y;
//     int x;
//     double	dx;
// 	double	dy;
// 	double	dist;
//     int player_x = (int)data->player->x;
//     int player_y = (int)data->player->y;

//     y = player_y - 1;
//     while (y <= player_y + 1)
//     {
//         x = player_x - 1;
//         while (x < player_x + 1)
//         {
//             if (y < 0 || x < 0 || !data->map.map[y] || !data->map.map[y][x])
//                 continue;
//             if (data->map.map[y][x] == 'D')
//             {
//                 dx = (x + 0.5) - data->player->x;
//                 dy = (y + 0.5) - data->player->y;
//                 dist = sqrt(dx * dx + dy * dy);
//                 if (dist < 1.0)
//                     data->map.map[y][x] = '0'; //instan->state.
//             }
//             x++;
//         }
//         y++;
//     }
// }

int mouse_move(int x, int y, t_data *data)
{
    int delta_x;
    double  rot;
    double  old_dir_x;
    double  old_plane_x;

    (void)y;
    if (!data->mouse_locked)
        return (0);
    delta_x = x - data->mouse_x;
    rot = -delta_x * MOUSE_SENSITIVITY;
    old_dir_x = data->game->dir_x;
    data->game->dir_x = data->game->dir_x * cos(rot) - 
                        data->game->dir_y * sin(rot);
    data->game->dir_y = old_dir_x * sin(rot) + data->game->dir_y * cos(rot);
    old_plane_x = data->game->plane_x;
    data->game->plane_x = data->game->plane_x * cos(rot) - 
                        data->game->plane_y * sin(rot);
    data->game->plane_y = old_plane_x * sin(rot) + 
                            data->game->plane_y * cos(rot);
    data->mouse_x = WIDTH / 2;
    data->mouse_y = HEIGHT / 2;
    mlx_mouse_move(data->mlx, data->win, data->mouse_x, data->mouse_y);
    return (0);
}

int mouse_click(int button, int x, int y, t_data *data)
{
    (void)x;
    (void)y;
    
    if (button == 1)
    {
        data->mouse_locked = !data->mouse_locked;
        if (data->mouse_locked)
        {
            mlx_mouse_hide(data->mlx, data->win);
            data->mouse_x = WIDTH / 2;
            data->mouse_y = HEIGHT / 2;
            mlx_mouse_move(data->mlx, data->win, data->mouse_x, data->mouse_y);
        }
        else
            mlx_mouse_show(data->mlx, data->win);
    }
    return (0);
}