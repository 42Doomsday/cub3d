#include <stdio.h>
#include <libft.h>

int	main(void)
{
	char *str = "hello world";
	int	i = 0;

	while (!ft_isspace(str[i]))
		i++;
	printf("remainder of string: %s\n", &str[-i]);
	return (0);
}
