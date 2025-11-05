/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaladeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 15:12:47 by aaladeok          #+#    #+#             */
/*   Updated: 2025/11/05 15:12:51 by aaladeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void    draw_gun(t_data *data)
{
    int x;
    int y;
    int gun_x;
    int gun_y;
    unsigned int    color;

    gun_x = (WIDTH - data->textures.gun.width) / 2;
    gun_y = HEIGHT - data->textures.gun.height;
    y = 0;
    while (y < data->textures.gun.height)
    {
        x = 0;
        while (x < data->textures.gun.width)
        {
            color = get_pixel_img(&data->textures.gun, x, y);
            // optional: handle transparency in the .xpm color
            if ((color & 0x00FFFFFF) != 0x000000) // skip pure black
                pixel_put(gun_x + x, gun_y + y, &data->img, color);
            x++;
        }
        y++;
    }
}
