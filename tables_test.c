#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include "table_test.h"
#include <libft.h>

// must only be declared in the file that uses it
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

void	assign_texture( t_texture_vals, const char *tag, const char *value)
{
	for (int i = 0; g_texture_table[i].name; i++)
	{
		if (strcmp(tab, g_texture_table[i].name) == 0)
		{
			void	*member = 
				(char *)vals + g_texture_table[i].offset_member;
			*(const char **)member = strdup(value);

			return;
		}
	}
}
