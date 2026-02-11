#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

/* ================= ENUM ================= */

typedef enum e_texture
{
    NORTH,
    SOUTH,
    EAST,
    WEST,
    T_COUNT
} t_texture_id;

/* ================= TARGET STRUCT ================= */

typedef struct s_texture_vals
{
    const char *north;
    const char *south;
    const char *east;
    const char *west;
} t_texture_vals;

/* ================= MAP STRUCT ================= */

typedef struct s_texture_map
{
    t_texture_id tex_id;
    const char   *tag;
    size_t        offset;
} t_texture_map;

/* ================= GLOBAL TABLE ================= */

static const t_texture_map g_texture_table[] =
{
    {NORTH, "NO", offsetof(t_texture_vals, north)},
    {SOUTH, "SO", offsetof(t_texture_vals, south)},
    {EAST,  "EA", offsetof(t_texture_vals, east)},
    {WEST,  "WE", offsetof(t_texture_vals, west)},
    {T_COUNT, NULL, 0}
};

/* ================= ASSIGN FUNCTION ================= */

void assign_texture(
    t_texture_vals *vals,
    const char *tag,
    const char *value)
{
    for (int i = 0; g_texture_table[i].tag != NULL; i++)
    {
        if (strcmp(tag, g_texture_table[i].tag) == 0)
        {
            void *member_ptr =
                (char *)vals + g_texture_table[i].offset;

            *(const char **)member_ptr = strdup(value);

            return;
        }
    }

    printf("Unknown tag: %s\n", tag);
}

/* ================= SIMPLE LINE PARSER ================= */

void parse_line(t_texture_vals *vals, const char *line)
{
    char tag[10];
    char value[256];

    if (sscanf(line, "%s %s", tag, value) == 2)
    {
        assign_texture(vals, tag, value);
    }
}

/* ================= DEMO ================= */

int main(void)
{
    t_texture_vals textures = {0};

    /* Simulated file lines */
    const char *file_lines[] =
    {
        "NO ./north.xpm",
        "SO ./south.xpm",
        "EA ./east.xpm",
        "WE ./west.xpm",
        NULL
    };

    for (int i = 0; file_lines[i]; i++)
        parse_line(&textures, file_lines[i]);

    /* Print results */
    printf("North: %s\n", textures.north);
    printf("South: %s\n", textures.south);
    printf("East : %s\n", textures.east);
    printf("West : %s\n", textures.west);

    return 0;
}

