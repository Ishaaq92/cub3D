#include "cub3D.h"

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

static int get_frame(t_data *data, int i, int width, int height)
{
    char    path[256];

    //Generate filename: "textures/door_01.xpm" to "textures/door_32.xpm"
    snprintf(path, sizeof(path), "./assets/door/Layer-1_sprite_%02d.xpm", i + 1);
    
    data->textures.door_arr.frames[i].img = mlx_xpm_file_to_image(
        data->mlx, path, &width, &height);
    
    if (!data->textures.door_arr.frames[i].img)
    {
        printf("Error: Failed to load %s\n", path);
        return 0;
    }
    
    data->textures.door_arr.frames[i].pxls = mlx_get_data_addr(
        data->textures.door_arr.frames[i].img,
        &data->textures.door_arr.frames[i].bpp,
        &data->textures.door_arr.frames[i].line_length,
        &data->textures.door_arr.frames[i].endian);
    
    data->textures.door_arr.frames[i].width = width;
    data->textures.door_arr.frames[i].height = height;
    return (1);
}

// Load all 32 door animation frames (numbered 01-32)
int load_door_frames(t_data *data)
{
    int     i;
    int     width;
    int     height;

    width = 0;
    height = 0;
    printf("Loading door animation frames...\n");
    
    i = 0;
    while (i < DOOR_FRAMES)
    {
        if (!get_frame(data, i, width, height))
            return (0);
        i++;
    }

    data->textures.door_arr.frame_count = DOOR_FRAMES;
    printf("Successfully loaded %d door frames (01-32)\n", DOOR_FRAMES);
    return 1;
}

// Get the appropriate door frame based on open_width
int get_door_frame(t_door *door, int total_frames)
{
    int frame;
    double eased;
    
    // Apply easing for smooth animation
    eased = ease_in_out_cubic(door->open_width);
    
    // Map 0.0-1.0 to frame index 0-(total_frames-1)
    frame = (int)(eased * (total_frames - 1));
    
    // Clamp to valid range
    if (frame < 0)
        frame = 0;
    if (frame >= total_frames)
        frame = total_frames - 1;
    
    return frame;
}