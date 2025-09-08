/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 16:13:42 by isahmed           #+#    #+#             */
/*   Updated: 2025/09/08 16:15:34 by isahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	process_map(char *filename)
{
	int		fd;
	char	*s;

	s = NULL;
	fd = open(filename, 0);
	if (fd < 0)
		return (-1);
	while ((s = get_next_line(fd)))
		if (ft_strncmp(s, "\n", 1))
			printf("%s", s);
	return (1);
}

int	parser(t_data *data, char *file)
{
	(void) data;
	process_map(file);
	return (0);
}
