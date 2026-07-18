/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwlodars <kwlodars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/25 11:55:11 by kwlodars          #+#    #+#             */
/*   Updated: 2026/07/05 14:19:37 by kwlodars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t n)
{
	size_t	little_len;
	size_t	i;

	little_len = ft_strlen(little);
	if (*little == '\0')
		return ((char *)big);
	while (n >= little_len && *big != '\0')
	{
		i = 0;
		while (i < little_len && big[i] == little[i])
			i++;
		if (i == little_len)
			return ((char *)big);
		big++;
		n--;
	}
	return (NULL);
}
