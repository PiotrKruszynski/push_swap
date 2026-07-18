/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkruszyn <pkruszyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/25 11:54:07 by kwlodars          #+#    #+#             */
/*   Updated: 2026/07/18 12:53:49 by pkruszyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_words(char const *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			count++;
			while (*s && *s != c)
				s++;
		}
	}
	return (count);
}

static char	**free_all(char **tab, size_t i)
{
	while (i > 0)
	{
		i--;
		free(tab[i]);
	}
	free(tab);
	return (NULL);
}

static char	*get_word(char const *s, char c, size_t *i)
{
	size_t	len;
	char	*word;

	while (s[*i] && s[*i] == c)
		(*i)++;
	len = 0;
	while (s[*i + len] && s[*i + len] != c)
		len++;
	word = ft_substr(s, *i, len);
	*i += len;
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	size_t	words;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	words = ft_words(s, c);
	tab = (char **)malloc(sizeof(char *) * (words + 1));
	if (!tab)
		return (NULL);
	i = 0;
	j = 0;
	while (j < words)
	{
		tab[j] = get_word(s, c, &i);
		if (!tab[j])
			return (free_all(tab, j));
		j++;
	}
	tab[j] = NULL;
	return (tab);
}
