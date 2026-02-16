#include "libft.h"
#include <fcntl.h>


typedef struct s_texture_vals
{
	char	*north;
	char	*south;
	char	*east;
	char	*west;
}	t_texture_vals;

// 0) initiate data (inside parser)
// 1) validate input (inside parse_texture)
// 2) allocate resutl array
// 3) find position of first space
// 4) if space is found 
//		create first substring
//		then create second substring\
// 5) if no space 
//		duplicate entire string
//		second string is NULL
//	6) return results




int	check_tag(char *line)

char	*get_path(char *line, int len, int len_before_space)
{
	path = ft_substr(line, len_before_space + 1, len);
	path = ft_strtrim(path);
}

int	check_path()


//get_line(fd);
//
//check_texture_tag
//
//set_path()
//
//set_texture_vals()

int	parse_textures(int fd, t_texture_vals *vals)
{			
	char *line;

	line = get_next_line(fd); // returns allocated memory
	while (line)
	{
		line = ft_strtrim(line, "\t\n\r:"); // does it return allocated memory?
		if (!line)
			return (NULL);
		if (line[0] == "\n")
		{
			free(line);
			line = get_next_line(fd); // returns allocated memory
			continue;
		}
		ft_strtrim(line, " ")
		//first_word
		check_tag
		//path
		//assign values to struct
		//check all values are in struct
		//return 1 if error exists
	}
	//return 0 if no error
	return (0);
}




	int	len;
	char *space_ptr;
	int len_before_space;
	char *tag;
	char *path;

	len = ft_strlen(line);
	space_ptr = ft_strchr(line, ' ');
	len_before_space = space_ptr - line;
	tag = ft_substr(line, 0, len_before_space);
	path = ft_substr(line, len_before_space + 1, len);
	int i = 0; 
	while (!ft_isprint(path[i])) 
		i++;
	
	printf("SECONDHALF %s\n", path);
	int fd = open(path, O_RDONLY);
	char *next = get_next_line(fd);
	printf("NEXTLINE: %s\n", next);
	return (0);
}

int main(void)
{
    t_texture_vals textures = {0};

    /* Simulated file lines */
    char *file_lines[] =
    {
        "NO     ./example.cub",
        "SO ./example.cub",
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

