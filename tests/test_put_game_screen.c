/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_put_game_screen.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 00:00:00 by dkalgano          #+#    #+#             */
/*   Updated: 2026/04/09 00:00:00 by dkalgano        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mock_mlx.h"

/*
** Pixel constants (RGBA packed by mock mlx_put_pixel / get_rgba):
**   ceiling = green  0x00FF00FF
**   floor   = blue   0x0000FFFF
**   wall    = red    0xFF0000FF  (all-red 4x4 PNG texture)
**
** ── Scenario 1: standard ──────────────────────────────────────────────────
**   Image 1x10, top=2, bot=7, heights=5
**   y=0,1   → ceiling
**   y=2..6  → wall
**   y=7..9  → floor
**
** ── Scenario 2: top_border = 0 (no ceiling) ─────────────────────────────
**   Image 1x10, top=0, bot=7, heights=7
**   put_ceiling loop: while(y < 0) → never runs → y=0 is first wall pixel
**   y=0..6  → wall
**   y=7..9  → floor
**
** ── Scenario 3: negative top_border (wall taller than screen) ───────────
**   Image 1x10, top=-3, bot=13, heights=16
**   put_ceiling: top clamped to 0 → 0 ceiling pixels
**   put_textures: end = put_to_limits(13, 10) = 9 → y=0..8 wall
**   y=9     → floor
**
** ── Scenario 4: two independent columns ─────────────────────────────────
**   Image 2x10
**   col 0: top=2, bot=7  → ceiling y=0,1  | wall y=2..6  | floor y=7..9
**   col 1: top=5, bot=9  → ceiling y=0..4 | wall y=5..8  | floor y=9
**   Cross-check at y=3: col0=wall(red), col1=ceiling(green)
**   Cross-check at y=7: col0=floor(blue), col1=wall(red)
*/

# define C_GREEN  0x00FF00FFu
# define C_BLUE   0x0000FFFFu
# define C_RED    0xFF0000FFu

typedef struct s_px_case
{
	const char	*name;
	uint32_t	col;
	uint32_t	row;
	uint32_t	expected;
}	t_px_case;

static void	puterror(const char *name)
{
	dprintf(STDERR_FILENO, "\nThe test: %s - was failed:\n", name);
}

static void	putsuccess(const char *name)
{
	printf("Test: %s - passed!\n", name);
}

static void	fill_red_texture(mlx_texture_t *tex, uint8_t *buf,
				uint32_t w, uint32_t h)
{
	uint32_t	i;

	tex->width = w;
	tex->height = h;
	tex->bytes_per_pixel = 4;
	tex->pixels = buf;
	i = 0;
	while (i < w * h)
	{
		buf[i * 4 + 0] = 255;
		buf[i * 4 + 1] = 0;
		buf[i * 4 + 2] = 0;
		buf[i * 4 + 3] = 255;
		i++;
	}
}

static void	setup_colors(t_textures *texts, int *ceil_rgb, int *floor_rgb)
{
	ceil_rgb[0] = 0;
	ceil_rgb[1] = 255;
	ceil_rgb[2] = 0;
	floor_rgb[0] = 0;
	floor_rgb[1] = 0;
	floor_rgb[2] = 255;
	texts->ceiling = ceil_rgb;
	texts->floor = floor_rgb;
}

static void	setup_pngs(t_png_textures *pngs, mlx_texture_t *tex)
{
	pngs->north = tex;
	pngs->east = tex;
	pngs->west = tex;
	pngs->south = tex;
}

static int	run_cases(mlx_image_t *img, const t_px_case *cases, size_t total)
{
	size_t	i;
	size_t	passed;

	passed = 0;
	i = 0;
	while (i < total)
	{
		if (pixel_at(img, cases[i].col, cases[i].row) == cases[i].expected)
		{
			putsuccess(cases[i].name);
			passed++;
		}
		else
		{
			puterror(cases[i].name);
			dprintf(STDERR_FILENO, "  expected 0x%08X, got 0x%08X\n",
				cases[i].expected,
				pixel_at(img, cases[i].col, cases[i].row));
		}
		i++;
	}
	return (passed == total);
}

/*
** Scenario 1: standard layout (top=2, bot=7 on a 1x10 image).
*/
static int	run_standard(void)
{
	static const t_px_case	cases[] = {
		{"std: ceiling y=0",   0, 0, C_GREEN},
		{"std: ceiling y=1",   0, 1, C_GREEN},
		{"std: wall    y=2",   0, 2, C_RED  },
		{"std: wall    y=4",   0, 4, C_RED  },
		{"std: wall    y=6",   0, 6, C_RED  },
		{"std: floor   y=7",   0, 7, C_BLUE },
		{"std: floor   y=9",   0, 9, C_BLUE },
	};
	uint8_t			tex_buf[4 * 4 * 4];
	mlx_texture_t	tex;
	int				top[1];
	int				bot[1];
	int				heights[1];
	t_texture_id	sides[1];
	t_coords		coords[1];
	t_rays			rays;
	int				ceil_rgb[3];
	int				floor_rgb[3];
	t_textures		texts;
	t_png_textures	pngs;
	mlx_image_t		*img;
	int				ok;

	fill_red_texture(&tex, tex_buf, 4, 4);
	top[0] = 2; bot[0] = 7; heights[0] = 5;
	sides[0] = NORTH; coords[0].x = 0.5f; coords[0].y = 0.0f;
	rays.count = 1;
	rays.top_borders = top; rays.bot_borders = bot; rays.heights = heights;
	rays.sides = sides; rays.coords = coords;
	setup_colors(&texts, ceil_rgb, floor_rgb);
	setup_pngs(&pngs, &tex);
	img = make_test_image(1, 10);
	put_game_screen(img, &rays, &texts, &pngs);
	ok = run_cases(img, cases, sizeof(cases) / sizeof(cases[0]));
	free_test_image(img);
	return (ok);
}

/*
** Scenario 2: top_border = 0 → no ceiling pixels at all.
** put_ceiling loop condition: while (coords.y < 0) → never executes.
** Wall starts at y=0 and runs to y=6 (bot=7 → end=7).
*/
static int	run_zero_top_border(void)
{
	static const t_px_case	cases[] = {
		{"zero-top: y=0 is wall (no ceiling)", 0, 0, C_RED },
		{"zero-top: y=6 is wall",              0, 6, C_RED },
		{"zero-top: y=7 is floor",             0, 7, C_BLUE},
	};
	uint8_t			tex_buf[4 * 4 * 4];
	mlx_texture_t	tex;
	int				top[1];
	int				bot[1];
	int				heights[1];
	t_texture_id	sides[1];
	t_coords		coords[1];
	t_rays			rays;
	int				ceil_rgb[3];
	int				floor_rgb[3];
	t_textures		texts;
	t_png_textures	pngs;
	mlx_image_t		*img;
	int				ok;

	fill_red_texture(&tex, tex_buf, 4, 4);
	top[0] = 0; bot[0] = 7; heights[0] = 7;
	sides[0] = NORTH; coords[0].x = 0.5f; coords[0].y = 0.0f;
	rays.count = 1;
	rays.top_borders = top; rays.bot_borders = bot; rays.heights = heights;
	rays.sides = sides; rays.coords = coords;
	setup_colors(&texts, ceil_rgb, floor_rgb);
	setup_pngs(&pngs, &tex);
	img = make_test_image(1, 10);
	put_game_screen(img, &rays, &texts, &pngs);
	ok = run_cases(img, cases, sizeof(cases) / sizeof(cases[0]));
	free_test_image(img);
	return (ok);
}

/*
** Scenario 3: negative top_border (wall taller than screen height).
** top=-3, bot=13 → consistent with heights=16 on a 10-px tall screen.
**   put_ceiling: top clamped to 0 → ceiling loop never runs
**   put_textures: end = put_to_limits(13, 10) = 9 → wall fills y=0..8
**   put_floor: y=9
*/
static int	run_negative_top_border(void)
{
	static const t_px_case	cases[] = {
		{"neg-top: y=0 is wall (top clamped)", 0, 0, C_RED },
		{"neg-top: y=8 is wall (bot clamped)", 0, 8, C_RED },
		{"neg-top: y=9 is floor",              0, 9, C_BLUE},
	};
	uint8_t			tex_buf[4 * 4 * 4];
	mlx_texture_t	tex;
	int				top[1];
	int				bot[1];
	int				heights[1];
	t_texture_id	sides[1];
	t_coords		coords[1];
	t_rays			rays;
	int				ceil_rgb[3];
	int				floor_rgb[3];
	t_textures		texts;
	t_png_textures	pngs;
	mlx_image_t		*img;
	int				ok;

	fill_red_texture(&tex, tex_buf, 4, 4);
	top[0] = -3; bot[0] = 13; heights[0] = 16;
	sides[0] = NORTH; coords[0].x = 0.5f; coords[0].y = 0.0f;
	rays.count = 1;
	rays.top_borders = top; rays.bot_borders = bot; rays.heights = heights;
	rays.sides = sides; rays.coords = coords;
	setup_colors(&texts, ceil_rgb, floor_rgb);
	setup_pngs(&pngs, &tex);
	img = make_test_image(1, 10);
	put_game_screen(img, &rays, &texts, &pngs);
	ok = run_cases(img, cases, sizeof(cases) / sizeof(cases[0]));
	free_test_image(img);
	return (ok);
}

/*
** Scenario 4: two independent columns on a 2x10 image.
**   col 0: top=2, bot=7  → ceiling y=0,1  | wall y=2..6  | floor y=7..9
**   col 1: top=5, bot=9  → ceiling y=0..4 | wall y=5..8  | floor y=9
**
** Independence cross-checks (same y, different region per column):
**   y=3: col0=wall(red),  col1=ceiling(green)
**   y=7: col0=floor(blue), col1=wall(red)
*/
static int	run_two_columns(void)
{
	static const t_px_case	cases[] = {
		{"2col: col0 y=1 ceiling",                   0, 1, C_GREEN},
		{"2col: col0 y=3 wall",                      0, 3, C_RED  },
		{"2col: col0 y=7 floor",                     0, 7, C_BLUE },
		{"2col: col1 y=0 ceiling",                   1, 0, C_GREEN},
		{"2col: col1 y=6 wall",                      1, 6, C_RED  },
		{"2col: col1 y=9 floor",                     1, 9, C_BLUE },
		{"2col: col1 y=3 is ceiling while col0 wall",1, 3, C_GREEN},
		{"2col: col1 y=7 is wall while col0 floor",  1, 7, C_RED  },
	};
	uint8_t			tex_buf[4 * 4 * 4];
	mlx_texture_t	tex;
	int				top[2];
	int				bot[2];
	int				heights[2];
	t_texture_id	sides[2];
	t_coords		coords[2];
	t_rays			rays;
	int				ceil_rgb[3];
	int				floor_rgb[3];
	t_textures		texts;
	t_png_textures	pngs;
	mlx_image_t		*img;
	int				ok;

	fill_red_texture(&tex, tex_buf, 4, 4);
	top[0] = 2; bot[0] = 7;  heights[0] = 5;
	top[1] = 5; bot[1] = 9;  heights[1] = 4;
	sides[0] = NORTH; coords[0].x = 0.5f; coords[0].y = 0.0f;
	sides[1] = NORTH; coords[1].x = 0.5f; coords[1].y = 0.0f;
	rays.count = 2;
	rays.top_borders = top; rays.bot_borders = bot; rays.heights = heights;
	rays.sides = sides; rays.coords = coords;
	setup_colors(&texts, ceil_rgb, floor_rgb);
	setup_pngs(&pngs, &tex);
	img = make_test_image(2, 10);
	put_game_screen(img, &rays, &texts, &pngs);
	ok = run_cases(img, cases, sizeof(cases) / sizeof(cases[0]));
	free_test_image(img);
	return (ok);
}

int	main(void)
{
	int	all_ok;

	all_ok = run_standard();
	all_ok &= run_zero_top_border();
	all_ok &= run_negative_top_border();
	all_ok &= run_two_columns();
	if (all_ok)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}
