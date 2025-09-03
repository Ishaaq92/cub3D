/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaladeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 22:39:36 by aaladeok          #+#    #+#             */
/*   Updated: 2024/04/11 09:24:48 by aaladeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*buff_d;
	char	*buff_s;

	i = 0;
	buff_d = (char *)dest;
	buff_s = (char *)src;
	while (i < n)
	{
		buff_d[i] = buff_s[i];
		i++;
	}
	return (dest);
}
