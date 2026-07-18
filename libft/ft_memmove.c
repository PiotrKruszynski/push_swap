/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwlodars <kwlodars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/25 11:53:15 by kwlodars          #+#    #+#             */
/*   Updated: 2026/07/05 14:17:28 by kwlodars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*dst;
	const unsigned char	*sr;

	if (!dest && !src)
		return (NULL);
	if (dest == src)
		return (dest);
	dst = (unsigned char *)dest;
	sr = (const unsigned char *)src;
	if (dst > sr)
	{
		while (n--)
			dst[n] = sr[n];
	}
	else
	{
		while (n--)
			*dst++ = *sr++;
	}
	return (dest);
}
