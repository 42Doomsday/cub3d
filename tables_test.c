#include <strdio.h>
#include <string.h>

typedef enum	e_texture 
{
	NORTH,
	SOUTH,
	EAST,
	WEST,
	FLOOR,
	CEILING,
	T_COUNT:!
}	t_texture_id;

typedef struct	s_texture_vals
{
	const char	*north;
	const char	*south;
	const char	*east;
	const char	*west;
	int			floor;
	int			ceiling;
}	t_texture_vals;

typedef struct	s_texture_map
{
	t_texture_id	tex_id;
	const char		*name;
	void			*member_ptr;
}   t_texture_map;

// must only be declared in the file that uses it
void	build_map()
{
	t_texture_vals	textures;

	static const t_texture_map  g_texture_table[] =
	{ 
		{NORTH, "NO", offsetof(t_texture_vals, north)},
		{SOUTH, "SO", offsetof(t_texture_vals, north)},
		{EAST, "EA", offsetof(t_texture_vals, north)},
		{WEST, "WE", offsetof(t_texture_vals, north)},
		{FLOOR, "F", offsetof(t_texture_vals, north)},
		{CEILING, "C", offsetof(t_texture_vals, north)},
		{T_COUNT, NULL, NULL}
	}

	g_texture_table[FLOOR]
}

