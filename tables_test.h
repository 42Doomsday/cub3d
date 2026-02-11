
typedef enum	e_texture 
{
	NORTH,
	SOUTH,
	EAST,
	WEST,
	FLOOR,
	CEILING,
	T_COUNT
}	t_texture_id;

typedef struct	s_texture_vals
{
	const char	*north;
	const char	*south;
	const char	*east;
	const char	*west;
	int			*floor;
	int			*ceiling;
}	t_texture_vals;

typedef struct	s_texture_map
{
	t_texture_id	tex_id;
	const char		*name;
	size_t			offset_member;
}   t_texture_map;
