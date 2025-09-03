/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaladeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 04:08:02 by aaladeok          #+#    #+#             */
/*   Updated: 2024/04/24 17:31:11 by aaladeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_get_nlen(long num)
{
	size_t	len;

	len = 0;
	if (num < 0)
	{
		len++;
		num *= -1;
	}
	else if (num == 0)
		return (1);
	while (num > 0)
	{
		len++;
		num /= 10;
	}
	return (len);
}

static char	*ft_num_to_str(size_t len, unsigned int num)
{
	char	*str;

	str = malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (num > 0)
	{
		str[--len] = num % 10 + '0';
		num /= 10;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char			*str;
	unsigned int	num;
	size_t			len;

	len = ft_get_nlen(n);
	if (n == INT_MIN)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	if (n < 0)
	{
		num = -n;
		str = ft_num_to_str(len, num);
		if (!str)
			return (NULL);
		str[0] = '-';
	}
	else
	{
		num = n;
		str = ft_num_to_str(len, num);
		if (!str)
			return (NULL);
	}
	return (str);
}
