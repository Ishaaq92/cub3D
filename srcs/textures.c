#include "cub3D.h"

t_img   load_xpm_to_img(void *mlx, char *path)
{
    t_img   tex;

    tex.img = mlx_xpm_file_to_image(mlx, path, &tex.width, &tex.height);;
    if (!tex.img)
    {
        printf("Error: unable to load XPM file: %s\n", path);
        return ((t_img){0});
    }
    tex.pxls = mlx_get_data_addr(tex.img, &tex.bpp, &tex.line_length,
                                &tex.endian);
    return (tex);
}