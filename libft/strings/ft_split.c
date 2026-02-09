/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 19:23:22 by clouden           #+#    #+#             */
/*   Updated: 2025/05/23 21:21:32 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

static int	ft_cntsplits(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (count + 1);
}

static char	*ft_findword(char const *s, char c, int *i)
{
	char	*word;
	int		wi;

	wi = 0;
	word = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (!word)
		return (NULL);
	while (s[*i] && s[*i] != c)
		word[wi++] = s[(*i)++];
	if (wi == 0)
	{
		free(word);
		return (NULL);
	}
	word[wi] = '\0';
	return (word);
}

static char	**ft_fillarray(char const *s, char c, char **array, int strcnt)
{
	int		i;
	int		wi;
	char	*word;

	i = 0;
	wi = 0;
	while (i < strcnt - 1)
	{
		while (s[wi] == c)
			wi++;
		word = ft_findword(s, c, &wi);
		if (word)
		{
			array[i] = ft_strdup(word);
			free(word);
			i++;
		}
	}
	return (array);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	int		strcnt;

	if (!s)
		return (NULL);
	strcnt = ft_cntsplits(s, c);
	array = (char **)ft_calloc(strcnt, sizeof(char *));
	if (!array)
		return (NULL);
	return (ft_fillarray(s, c, array, strcnt));
}
