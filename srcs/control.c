#include "cub3D.h"

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