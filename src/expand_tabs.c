/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tabs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 16:42:50 by dkalgano          #+#    #+#             */
/*   Updated: 2026/02/16 16:52:40 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static size_t	exanded_strlen(char *line);
static char		*expand_line(char *line, int size);

t_list	*expand_tabs(t_list *lst)
{
	char	*str;
	int		idx;
	size_t	size;
	t_list	*tmp;

	tmp = lst;
	while (tmp)
	{
		str = tmp->content;
		idx = 0;
		size = exanded_strlen(str);
		if (size != ft_strlen(str))
		{
			tmp->content = expand_line(str, size);
			if (tmp->content == NULL)
			{
				ft_lstclear(&lst, free);
				return (NULL);
			}
			free(str);
		}
		tmp = tmp->next;
	}
	return (lst);
}

static size_t	exanded_strlen(char *line)
{
	size_t	size;
	int		idx;

	size = 0;
	idx = 0;
	while (line && line[idx])
	{
		if (line[idx++] == '\t')
			size += TAB_SIZE;
		else
			size++;
	}
	return (size);
}

static char	*expand_line(char *line, int size)
{
	char	*expanded;
	int		i;
	int		k;
	int		j;

	expanded = malloc(size + 1);
	if (expanded == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (line && line[i])
	{
		if (line[i] == '\t')
		{
			k = 0;
			while (k++ < TAB_SIZE)
				expanded[j++] = ' ';
		}
		else
			expanded[j++] = line[i];
		i++;
	}
	expanded[j] = '\0';
	return (expanded);
}
