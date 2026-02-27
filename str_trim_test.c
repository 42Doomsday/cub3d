#include <libft.h>

int	main(void)
{
	char	*line = "\n";
	char	*trim;
	int		len;

	len = ft_strlen(line);
	printf("============\n");
	printf("ORG: %s\n", line);
	printf("LEN: %d\n", len);
	printf("------------\n");
	trim = ft_strtrim_wht(line);
	len = ft_strlen(trim);
	printf("TRIM: %s\n", trim);
	printf("LEN: %d\n", len);
	printf("------------\n");
	return (0);
}
