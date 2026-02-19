
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
	char **strarr;
	char **ptr;
	int	i;

	if (comma_cnt(trim) != 2) // validate commas
		return (NULL);
	strarr = ft_split(trim, ',');
	if (!strarr || !*strarr || ft_strarr_len(strarr) != 3) //validate length of arr
	{
		ft_strarr_free(&strarr);
		return (NULL);
	}
	ptr = strarr;
	while (*ptr)
	{
		i = ft_atoi(*ptr);
		printf("PTR: %d\n", ft_atoi(*ptr));
		ptr++;
	}
	return (0);
}

int main(void)
{
	char *str = "230, 44, aa";
	parse_rgb(str);
	return (0);
}
