#include "cub3D.h"

int file_extension_valid(char* filepath)
{
    int len;

    len = ft_strlen(filepath);
    if (len < 4)
        return (0);
    if (ft_strncmp(filepath + len - 4, ".cub", 4) == 0)
        return (1);
    return (0);
}

t_list* read_file_to_list(const char* path)
{
    int fd;
    char* line;
    t_list* new;
    t_list* map_list;

    map_list = NULL;
    fd = open(path, O_RDONLY);
    if (fd < 0)
        return NULL;
    line = get_next_line(fd);
    while (line)
    {
        new = ft_lstnew(line);
        if (!new)
        {
            free(line);
            free_list_and_exit(&map_list);
        }                    
        ft_lstadd_back(&map_list, new);
        line = get_next_line(fd);
    }
    close(fd);
    return (map_list);
}

char** list_to_array(t_list* list)
{
    int i;
    char** arr;
    t_list* temp;
    int list_len;

    i = 0;
    temp = list;
    list_len = ft_lstsize(list);
    arr = malloc(sizeof(char *) * (list_len + 1));
    if (!arr)
        return (NULL);
    while(i < list_len)
    {
        arr[i] = dup_line(temp->content);
        if (!arr[i])
        {
            free_array(arr);
            return (NULL);
        }
        temp = temp->next;
        i++;
    }
    arr[i] = NULL;
    return (arr);
}

int validate_input(t_data *data, char* file_name)
{
    if (!file_extension_valid(file_name))
    {
        printf("Error: file must have a .cub extension\n");
        return (1);
    }
    data->map.map_list = read_file_to_list(file_name);
    if (!data->map.map_list)
    {
        printf("Error: unable to read file\n");
        return (1);
    }
    // *map = list_to_array(*map_list);
    // if (!map)
    // {
    //     printf("Error: malloc failed in the list_to_array\n");
    //     return (1);
    // }
    // *game = malloc(sizeof(t_game));
    // if (!*game)
    // {
    //     printf("Error: unabe to malloc sizeof t_game\n");
    // }
    if (validate_map(data) != 0)
        return (1);
    print_map(data->map.map, data->map.map_size);
    return (0);
}