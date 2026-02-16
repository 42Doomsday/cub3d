/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 13:53:25 by dkalgano          #+#    #+#             */
/*   Updated: 2026/02/16 14:45:45 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_list	*read_to_list(int fd);
static t_list	*expand_tabs(t_list *lst);
static char		**convert_to_array(t_list *lst);

char	**read_lines(int fd)
{
	char	**map;
	t_list	*lst;

	lst = expand_tabs(read_to_list(fd));
	map = convert_to_array(lst);
	ft_lstclear(&lst, NULL);
	return (map);
}

static t_list	*read_to_list(int fd)
{
	t_list	*lst;
	t_list	*node;
	char	*line;

	lst = NULL;
	while (42)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		line[ft_strlen(line) - 1] = '\0';
		node = ft_lstnew(line);
		if (node == NULL)
		{
			ft_lstclear(&lst, free);
			return (NULL);
		}
		ft_lstadd_back(&lst, node);
	}
	return (lst);
}

static t_list	*expand_tabs(t_list *lst)
{
	char	*str;
	char	*new_str;
	int		counter;
	int		idx;
	t_list	*tmp;

	tmp = lst;
	while (tmp )
	{
		str = tmp->content;
		idx = 0;
		counter = 0;
		while (str && str[idx])
		{
			if (str[idx] == '\t')
				counter += TAB_SIZE;
			else
				counter++;
			idx++;
		}
		if (idx != counter)
		{
			new_str = malloc(counter + 1);
			int	i;
			int	k;
			int	j;
			i = 0;
			k = 0;
			j = 0;
			while (str && str[i])
			{
				if (str[i] == '\t')
				{
					k = 0;
					while (k < TAB_SIZE)
					{
						new_str[j++] = ' ';
						k++;
					}
				}
				else
					new_str[j++] = str[i];
				i++;
			}
			new_str[j] = '\0';
			free(str);
			tmp ->content = new_str;
		}
		tmp  = tmp ->next;
	}
	return (lst);
}

static char	**convert_to_array(t_list *lst)
{
	char	**data;
	int		idx;

	if (lst == NULL)
		return (NULL);
	data = malloc((ft_lstsize(lst) + 1) * sizeof(char *));
	if (data == NULL)
		return (NULL);
	idx = 0;
	while (lst)
	{
		data[idx] = lst->content;
		lst = lst->next;
		idx++;
	}
	data[idx] = NULL;
	return (data);
}
