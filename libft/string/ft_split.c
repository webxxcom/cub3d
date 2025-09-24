/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phutran <phutran@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 11:02:29 by phutran           #+#    #+#             */
/*   Updated: 2025/05/24 17:05:53 by phutran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_words(const char *str, char ch)
{
	size_t	count;
	int		in_word;

	count = 0;
	in_word = 0;
	while (*str)
	{
		if (*str != ch && in_word == 0)
		{
			in_word = 1;
			count++;
		}
		else if (*str == ch)
			in_word = 0;
		str++;
	}
	return (count);
}

static char	*ft_strndup(const char *str, size_t count)
{
	char	*dup;
	size_t	i;

	dup = malloc((count + 1) * sizeof(*dup));
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

static void	ft_free_arr(char **arr, size_t i)
{
	while (i > 0)
	{
		i--;
		free(arr[i]);
	}
	free(arr);
}

static char	**ft_split_words(char **arr, const char *str, char ch, size_t count)
{
	size_t	i;
	size_t	word_len;

	i = 0;
	while (i < count)
	{
		while (*str && *str == ch)
			str++;
		word_len = 0;
		while (str[word_len] && str[word_len] != ch)
			word_len++;
		arr[i] = ft_strndup(str, word_len);
		if (!arr[i])
		{
			ft_free_arr(arr, i);
			return (NULL);
		}
		str = str + word_len;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

char	**ft_split(const char *str, char ch)
{
	char	**words;
	size_t	word_count;

	if (!str)
		return (NULL);
	word_count = ft_count_words(str, ch);
	words = malloc((word_count + 1) * sizeof(*words));
	if (!words)
		return (NULL);
	words = ft_split_words(words, str, ch, word_count);
	if (!words)
		return (NULL);
	return (words);
}

/*
static char	*ft_split_word(const char **str, char ch)
{
	char	*word;
	size_t	word_len;

	while (**str && **str == ch)
		(*str)++;
	word_len = 0;
	while ((*str)[word_len] && (*str)[word_len] != ch)
		word_len++;
	word = ft_strndup(*str, word_len);
	if (!word)
		return (NULL);
	*str = *str + word_len;
	return (word);
}

char	**ft_split(const char *str, char ch)
{
	char	**words;
	size_t	word_count;
	size_t	i;

	if (!str)
		return (NULL);
	word_count = ft_count_words(str, ch);
	words = malloc((word_count + 1) * sizeof(*words));
	if (!words)
		return (NULL);
	i = 0;
	while (i < word_count)
	{
		words[i] = ft_split_word(&str, ch);
		if (!words[i])
		{
			ft_free_arr(words, i);
			return (NULL);
		}
		i++;
	}
	words[i] = NULL;
	return (words);
}
*/
