/* returns 0 if corresponds and is valid
 * returns 1 if only corresponds
 * returns 2 if does not correspond
 *
 * corresponds to { NO, SO, WE, EA, C, F, or <space> } in any order, once each
 * valid if the given values are within definition contraints
 * meaning path is a valid path
 * color ranges are valid color ranges
 * map is valid it contains no broken border, 
 *  is composed of 1/0 and 1 N/W/S/E which is to be considered a 0 by default.
*/

/* flood fill can check if borders are solid
 * texture atlas can help consolidate textures into a single document
*/

/* Very first step is open the first arg as file
 * if arg is not a .cub file return error an end program with message
 * make error handling messages
 * if args != 2 error and close
*/

/* now we have file that can open...maybe no permissions exist 
 * but once file opens we start at top left
 * enum NO, SO, EA, WE, C, F
 * textures can be in .xmp
 * when we find one we set a value corresponding to it from 0 to 1
 * we need to initialise those values first to 0
 * at each point we can validate and save the values next to it
*/

/* color validation can be tricky because the values could be separated by 
 * ,, or <space>, or multiple spaces
 * we should make reasonable rule about this and handle either as an error
 * or protect valid parsig of irregualar spacing
*/

/* if map preceeds any other information then error is sent */

/* i believe paths hould be legible with space
 * if it has space then quotes or backslash should be detecte or added
 * if space is detected and no back slash or quotes are dtected then add quotes
*/
#include "libft.h"
#include <stdio.h>

// texture map
typedef struct s_texture_map {
	char	        *name;
	t_texture_id	textr;
}	t_textr_map

// get 
t_textr	get_textr_type(char *textr_str)
{
	int			i;
    int         bytes;
	t_textr_map	map;

	i = 0;
	while (i < TEXTURE_CNT)
	{
        bytes = ft_strlen(textr_str);
		if (ft_strncmp(textr_str, map[i], )
			return (map[i]);
        i++;
	}
}

bool	parser_texture(int fd, t_textures *out)
{
	char	*line;
    char    **split;

	line = get_next_line(fd);
    split = ft_split(line, ' ');
    get_textr_type(split[0]);
}

int	main(int ac, char *av[])
{
	int	fd;
	
	fd = open(av[1], O_RDONLY);
	parser(fd);
}

