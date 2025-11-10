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

int	validate_input(t_data *data, char *file_name)
{
	if (!file_extension_valid(file_name))
		return (printf("Error: file must have a .cub extension\n"),
			exit_error(data), 1);
	if (validate_map(data) != 0)
		return (printf("Unable to validate map.\n"), exit_error(data), 1);
	return (0);
}