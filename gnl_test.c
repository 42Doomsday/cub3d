#include <libft.h>
#include <stdio.h>
#include <fcntl.h>

int main(void)
{
	char *line;
	int	fd;
	
	fd = open("example.cub", O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		printf("LINE: %s", line);
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}

