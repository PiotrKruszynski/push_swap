/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwlodars <kwlodars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/25 11:55:18 by kwlodars          #+#    #+#             */
/*   Updated: 2026/07/05 14:19:43 by kwlodars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char			*lst;
	unsigned char	chr;

	lst = NULL;
	chr = (unsigned char)c;
	while (*s)
	{
		if ((unsigned char)*s == chr)
		{
			lst = (char *)s;
		}
		s++;
	}
	if ((unsigned char)*s == chr)
	{
		lst = (char *)s;
	}
	return (lst);
}
