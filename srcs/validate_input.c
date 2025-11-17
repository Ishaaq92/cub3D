/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 21:36:00 by aaladeok          #+#    #+#             */
/*   Updated: 2025/10/09 17:29:19 by isahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	map_settings_complete(t_tex_flags *flags)
{
	if (!flags->has_north)
		return (1);
	if (!flags->has_south)
		return (1);
	if (!flags->has_west)
		return (1);
	if (!flags->has_east)
		return (1);
	if (!flags->has_floor)
		return (1);
	if (!flags->has_ceiling)
		return (1);
	return (0);
}

int	file_extension_valid(char *filepath)
{
	int	len;

	len = ft_strlen(filepath);
	if (len < 4)
		return (0);
	if (ft_strncmp(filepath + len - 4, ".cub", 4) == 0)
		return (1);
	return (0);
}

void	validate_input(t_data *data)
{
	if (validate_map(data) != 0)
		exit_error(data, "Unable to validate map.");
	if (map_settings_complete(&data->map.flags) != 0)
		exit_error(data, "Map setting is not complete.");
}

void free_lines(t_line *list)
{
    t_line *next;

    while (list)
    {
        next = list->next;
        free(list->str);    // free each GNL line
        free(list);         // free node
        list = next;
    }
	printf("Entire list freed!!\n.");
}
