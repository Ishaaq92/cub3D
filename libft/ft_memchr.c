/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaladeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 07:36:21 by aaladeok          #+#    #+#             */
/*   Updated: 2024/04/11 09:28:50 by aaladeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*mem_buff;

	i = 0;
	mem_buff = (unsigned char *)s;
	while (i < n)
	{
		if (mem_buff[i] == (unsigned char)c)
			return ((void *)mem_buff + i);
		i++;
	}
	return (NULL);
}
