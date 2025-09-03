/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 12:40:08 by isahmed           #+#    #+#             */
/*   Updated: 2025/09/03 16:15:58 by isahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
int		main(void)
{
	t_data	data;
	
	if (initialise_data(&data) == -1)
		exit(1);
	render(&data);
	mlx_key_hook(data.win, key_hook, &data);
	mlx_loop(data.mlx);
	ft_quit(&data);
}
