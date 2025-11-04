#include "cub3D.h"

// Smooth easing function for natural animation
double ease_in_out_cubic(double t)
{
    if (t < 0.5)
        return (4.0 * t * t * t);
    else
    {
        double f = (2.0 * t - 2.0);
        return (1.0 + f * f * f / 2.0);
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