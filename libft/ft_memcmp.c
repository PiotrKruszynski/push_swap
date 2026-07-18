/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwlodars <kwlodars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/25 11:53:01 by kwlodars          #+#    #+#             */
/*   Updated: 2026/07/05 14:17:18 by kwlodars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*st1;
	const unsigned char	*st2;

	if (n == 0)
		return (0);
	st1 = (const unsigned char *)s1;
	st2 = (const unsigned char *)s2;
	while (n > 0)
	{
		if (*st1 != *st2)
		{
			return (*st1 - *st2);
		}
		st1++;
		st2++;
		n--;
	}
	return (0);
}
