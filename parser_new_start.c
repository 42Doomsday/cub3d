#include <libft.h>
#include <stdio.h>

int	get_textures(int fd, t_textures *out)
{
	char	*line;
	char	*trim;

	line = get_next_line(fd);
	while (line)
	{
		if (line[0] == '\n')
		{
			free(line);
			line = get_next_line(fd);
			continue;
		}
		printf("line: %s\n", line);
		trim = ft_strtrim_wht(line);
		free(line);
		printf("trim: %s\n", trim);
	}
}
