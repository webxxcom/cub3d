/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 11:02:29 by phutran           #+#    #+#             */
/*   Updated: 2026/02/07 16:02:35 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int is_delim(char c, const char *delims)
{
    while (*delims)
        if (*delims++ == c)
            return (1);
    return (0);
}

static size_t	ft_count_words(const char *str, const char *delims)
{
	size_t	count;
	int		in_word;

	count = 0;
	in_word = 0;
	while (*str)
	{
		if (!is_delim(*str, delims) && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (is_delim(*str, delims))
			in_word = 0;
		str++;
	}
	return (count);
}

static char	*ft_strndup(const char *str, size_t count)
{
	char *const dup = ft_calloc(count + 1, sizeof(*dup));
	size_t		i;

	if (!dup)
		return (NULL);
	i = 0;
	while (i < count && str[i])
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

static char	**ft_split_words(
		char **arr, const char *str, const char *delims, size_t count)
{
	size_t	i;
	size_t	word_len;
	
	i = 0;
	while (i < count)
	{
		while (*str && is_delim(*str, delims))
			str++;
		word_len = 0;
		while (str[word_len] && !is_delim(str[word_len], delims))
			word_len++;
		arr[i] = ft_strndup(str, word_len);
		if (!arr[i])
			return (ft_free_matrix(arr), NULL);
		str += word_len;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

char	**ft_split(const char *str, const char *delims)
{
	char	**words;
	size_t	word_count;

	if (!str)
		return (NULL);
	word_count = ft_count_words(str, delims);
	words = ft_calloc((word_count + 1),  sizeof(*words));
	if (!words)
		return (NULL);
	words = ft_split_words(words, str, delims, word_count);
	if (!words)
		return (NULL);
	return (words);
}
