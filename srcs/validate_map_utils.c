/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 21:36:25 by aaladeok          #+#    #+#             */
/*   Updated: 2025/11/10 14:19:07 by isahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_cell(char **map, int row, int col, int max_rows)
{
	static const char	*exp_chars = "01NEWSDG";

	if (row < 0 || row >= max_rows)
		return (1);
	if (col < 0 || (size_t)col >= ft_strlen(map[row]))
		return (1);
	if (map[row][col] == ' ' || !ft_strchr(exp_chars, map[row][col]))
		return (1);
	return (0);
}

int	is_valid(char **map, int i, int j, int len)
{
	if (check_cell(map, i - 1, j, len))
		return (1);
	if (check_cell(map, i + 1, j, len))
		return (1);
	if (check_cell(map, i, j - 1, len))
		return (1);
	if (check_cell(map, i, j + 1, len))
		return (1);
	return (0);
}

int	check_details(char **map, int rows, int r, int c)
{
	char	ch;

	ch = map[r][c];
	if (ch == '1' || ch == ' ' || ch == '\n')
		return (0);
	if (ch == '\0')
		return (0);
	if (r == 0 || c == 0 || r == rows - 1 || c >= (int)ft_strlen(map[r]) - 1)
	{
		printf("Map error at row %d, col %d.\n", r, c);
		return (1);
	}
	if (is_valid(map, r, c, rows))
	{
		printf("Map error at row %d, col %d.\n", r, c);
		return (1);
	}
	return (0);
}

int	check_walls(char **map, int map_height)
{
	int	row;
	int	col;

	row = 0;
	while (row < map_height)
	{
		col = 0;
		while (map[row][col])
		{
			if (check_details(map, map_height, row, col))
				return (1);
			++col;
		}
		row++;
	}
	return (0);
}
