#include <libft.h>
#include <stdio.h>

int	main(void)
{
	char *str = "	\t hello world	\t\n";
	char *new;

	new = ft_strtrim(str);
	printf("old: %s\n", str);
	printf("new: %s\n", new);
	return (0);
}
