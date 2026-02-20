
#include <libft.h>
#include <stdio.h>


// this counts commas
int	comma_cnt(char *trim)
{
	int	cnt;

	cnt = 0;
	while (*trim)
	{
		if (*trim == ',')
			cnt++;
		trim++;
	}
	return (cnt);
}

bool	check_range(int num)
{
	return (num > -1 && num < 256);
}

bool	validate_rgb(char **strarr)
{
	int	i;
	int	new;

	i = 0;
	if (!strarr || !*strarr || ft_strarr_len(strarr) != 3)
	{
		return (false);
	}
	while (strarr[i])
	{
		if (!ft_isnum(strarr[i]))
		{
			return (false);
		}
		new = ft_atoi(strarr[i]);
		if (!check_range(new))
			return (false);
		i++;
	}
	return (true);
}

void	free_rgb(char ***strarr, int **intarr)
{
	if (strarr)
		ft_strarr_free(strarr);
	if (*intarr)
		free(*intarr);
	return ;
}

int	*parse_rgb(char *trim)
{
	char	**strarr;
	int		*intarr;
	int		i;
	int		new;

	strarr = ft_split(trim, ',');
	intarr = ft_calloc(sizeof(int), 3);
	if (comma_cnt(trim) != 2 || !validate_rgb(strarr) || !intarr)
	{
		free_rgb(&strarr, &intarr);
		return (NULL);
	}
	if (validate_rgb(strarr))
	{
		i = 0;
		while (strarr[i])
		{
			intarr[i] = ft_atoi(strarr[i]);
			i++;
		}
		ft_strarr_free(&strarr);
		return (intarr);
	}
	else
	{
		free_rgb(&strarr, &intarr);
		return (NULL);
	}
}

int main(void)
{
	char *str = "256, 0, 0";
	int	*intarr;
	intarr = parse_rgb(str);
	if (!intarr)
		return (0);
	for(int i = 0; i < 3; i++)
	{
		printf("INT: %d\n", intarr[i]);
	}
	return (0);
}
