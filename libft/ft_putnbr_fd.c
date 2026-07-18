/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwlodars <kwlodars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/25 11:53:46 by kwlodars          #+#    #+#             */
/*   Updated: 2026/07/10 11:25:22 by kwlodars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

static void	ft_write_nbr(unsigned int nbr, int fd)
{
	char	c;

	if (nbr >= 10)
		ft_write_nbr(nbr / 10, fd);
	c = (nbr % 10) + '0';
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	nbr;

	if (n < 0)
	{
		write(fd, "-", 1);
		nbr = (unsigned int)n;
		nbr = -nbr;
	}
	else
	{
		nbr = (unsigned int)n;
	}
	ft_write_nbr(nbr, fd);
}
