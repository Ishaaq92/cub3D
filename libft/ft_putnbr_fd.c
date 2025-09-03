/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaladeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 08:31:48 by aaladeok          #+#    #+#             */
/*   Updated: 2024/04/18 09:22:59 by aaladeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_write_num(int num, int fd)
{
	char	*numbers;

	numbers = "0123456789";
	num = (unsigned int)num;
	if ((num / 10) > 0)
		ft_write_num(num / 10, fd);
	write(fd, &numbers[num % 10], 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	int	num;

	num = 0;
	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else
	{
		num = n;
		if (n < 0)
		{
			write(fd, "-", 1);
			num = n * -1;
		}
		ft_write_num(num, fd);
	}
}
/*
int	main(void)
{
	ft_putnbr_fd(-2147483648, 1);
	write(1, "\n", 1);
	ft_putnbr_fd(2147483647, 1);
	write(1, "\n", 1);
	ft_putnbr_fd(2, 1);	
}
*/
