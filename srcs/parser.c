/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaladeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 15:12:10 by aaladeok          #+#    #+#             */
/*   Updated: 2025/11/05 15:12:14 by aaladeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int texture_path_complete(t_tex_flags *flags)
{
    if (!flags->has_north) //0 0r 1
        return (1);
    if (!flags->has_south)
        return (1);
    if (!flags->has_west)
        return (1);
    if (!flags->has_east)
        return (1);
    return (0);
}

int starts_with(const char *str, const char *prefix)
{
    int i;

    i = 0;
    while (*str == ' ' || *str == '\t')
        str++;
    while(prefix[i])
    {
        if (str[i] != prefix[i])
            return (0);
        i++;
    }
    return (1);
}

void set_path(t_data *data, char *line, char **dest, int *flag)
{
    char *tmp;
    char *path;

    printf("Was called for texture.\n");
    if (*flag)
        exit_error(data, "Double texture path.");
    if (!texture_path_complete(&data->map.flags))
        exit_error(data, "Excess texture paths...exiting.");
    tmp = ft_strchr(line, '.');
    if (!tmp)
        exit_error(data, "Empty texture path."); // list and everything else is freed inside
    tmp = ft_strtrim(tmp, "\n ");
    path = ft_strdup(tmp);
    free(tmp);
    if (access(path, F_OK) == -1)
    {
        printf("Issues with this texture path: %s", path);
        free(path);
        exit_error(data, "Unable to open texture path.");
    }
    *dest = path;
    *flag = 1;
}

// Skip whitespace and tabs
char *skip_whitespace(char *str)
{
    while (*str && (*str == ' ' || *str == '\t'))
        str++;
    return str;
}

int is_map_line(char *line)
{
    char *s;
    
    if (!line)
        return 0;
    s = skip_whitespace(line);
    if (*s == '1' || *s == '0' || *s == ' ')
        return 1;
    return 0;
}

void    parse_map(t_line *list, t_data *data)
{
    char *line;

    while (list)
    {
        line = list->str;
        data->map.map = add_map_line(data, line);
        list = list->next;
    }
}

void parse_file(t_data *data, t_line *list)
{
    t_line  *cur;
    char    *line;
    
    cur = list;
    while (cur)
    {
        line = cur->str;
        if (starts_with(line, "NO"))
            set_path(data, line, &data->map.path_to_north, &data->map.flags.has_north);
        else if (starts_with(line, "SO"))
            set_path(data, line, &data->map.path_to_south, &data->map.flags.has_south);
        else if (starts_with(line, "EA"))
            set_path(data, line, &data->map.path_to_east, &data->map.flags.has_east);
        else if (starts_with(line, "WE"))
            set_path(data, line, &data->map.path_to_west, &data->map.flags.has_west);
        else if (starts_with(line, "F"))
            set_rgb(data, line, &data->map.floor_rgb);
        else if (starts_with(line, "C"))
            set_rgb(data, line, &data->map.ceiling_rgb);
        else if (is_map_line(line))
        {
            printf("Did we hit a map line???");
            printf("Line is: %s\n", line);
            break;
        }
        cur = cur->next;
    }
    parse_map(cur, data);
    print_map(data->map.map, data->map.map_height);
}



//Testing
    // if (data->map.floor_rgb)
    //     printf("Floor RGB: %d\n", data->map.floor_rgb);
    //  if (data->map.ceiling_rgb)
    //     printf("Ceiling RGB: %d\n", data->map.ceiling_rgb);
    // if (data->map.path_to_east)
    //     printf("path to East: %s\n", data->map.path_to_east);
    //  if (data->map.path_to_west)
    //     printf("path to West: %s\n", data->map.path_to_west);
    //  if (data->map.path_to_north)
    //     printf("path to North: %s\n", data->map.path_to_north);
    //  if (data->map.path_to_south)
    //     printf("path to South: %s\n", data->map.path_to_south);