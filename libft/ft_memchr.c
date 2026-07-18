/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwlodars <kwlodars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/25 11:52:53 by kwlodars          #+#    #+#             */
/*   Updated: 2026/07/05 14:17:13 by kwlodars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*st;
	unsigned char		chr;

	st = (const unsigned char *)s;
	chr = (unsigned char)c;
	while (n > 0)
	{
		if (*st == chr)
			return ((void *)st);
		st++;
		n--;
	}
	return (NULL);
}
