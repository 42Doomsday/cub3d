#include "libft.h"


typedef struct s_texture_vals
{
	char	*north;
	char	*south;
	char	*east;
	char	*west;
}	t_texture_vals;


// 1) validate input
// 2) allocate resutl array
// 3) find position of first space
// 4) if space is found 
//		create first substring
//		then create second substring\
// 5) if no space 
//		duplicate entire string
//		second string is NULL
//	6) return results



int find_split_point()


int parse_textures(const char *line, t_texture_vals *vals)
{
	int	len;
	char *space_ptr;
	int before_space;

	len = ft_strlen(line);
	space_ptr = ft_strchr(line, ' ');

	before_space = space_ptr - line;

	printf("Total length: %d\n", len);
	printf("Length before space: %d\n", before_space);
	printf("First part: %.*s\n", before_space, line);
	return (0);
}


int main(void)
{
    t_texture_vals textures = {0};

    /* Simulated file lines */
    char *file_lines[] =
    {
        "NO ./north.xpm",
        "SO ./south.xpm",
        "EA ./east.xpm",
        "WE ./west.xpm",
        NULL
    };

    for (int i = 0; file_lines[i]; i++)
        parse_textures(file_lines[i], &textures);

    /* Print results */
//    printf("North: %s\n", textures.north);
//    printf("South: %s\n", textures.south);
//    printf("East : %s\n", textures.east);
//    printf("West : %s\n", textures.west);

    return 0;
}

