/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwlodars <kwlodars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/25 11:53:07 by kwlodars          #+#    #+#             */
/*   Updated: 2026/07/05 14:17:23 by kwlodars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const unsigned char	*sr;
	unsigned char		*dst;

	dst = (unsigned char *)dest;
	sr = (const unsigned char *)src;
	if (!dest && !src)
		return (NULL);
	if (dest == src)
		return (dest);
	while (n--)
		*dst++ = *sr++;
	return (dest);
}
