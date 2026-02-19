
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

int	*parse_rgb(char *trim)
{
	char	**strarr;
	char	**ptr;
	int		new;
	int		*intarr;
	int		i;

	i = 0;
	intarr = ft_calloc(sizeof(int), 3);
	if (!intarr)
		return (NULL);
	if (comma_cnt(trim) != 2)
		return (NULL);
	strarr = ft_split(trim, ',');
	if (!strarr || !*strarr || ft_strarr_len(strarr) != 3)
	{
		ft_strarr_free(&strarr);
		return (NULL);
	}
	ptr = strarr;
	while (*ptr)
	{
		if (!ft_isnum(*ptr))
		{
			free(intarr);
			return (NULL);
		}
		intarr[i] = ft_atoi(*ptr);
		i++;
		ptr++;
	}
	return (intarr);
}

int main(void)
{
	char *str = "230, 44, 45";
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
