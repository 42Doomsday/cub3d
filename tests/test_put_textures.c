/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_put_textures.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 00:00:00 by dkalgano          #+#    #+#             */
/*   Updated: 2026/04/09 00:00:00 by dkalgano        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mock_mlx.h"

/*
** put_textures is defined in src/game/put_textures.c but not declared in any
** public header — forward-declare it here.
*/
int	put_textures(mlx_image_t *img, t_rays *rays, t_png_textures *texts,
		t_icoords coords);

/*
** ── Pixel colour constants (RGBA as packed by get_text_pixel / pixel_at) ──
**
**   Texture pixels are stored as (R,G,B,A) bytes.
**   get_text_pixel returns  pixels[0]<<24 | pixels[1]<<16 | pixels[2]<<8 | pixels[3]
**   mock pixel_at reads them back the same way, so the round-trip is exact.
**
** ── Scenario 1: side selection ───────────────────────────────────────────
**   Four 1x1 solid-colour textures, one per cardinal direction.
**   Verifies that get_text() picks the right t_png_textures member.
**   Wall region: top=2, bot=7 on a 1x10 image; check y=4 (middle).
**
** ── Scenario 2: NORTH column mapping (x fractional part × width) ─────────
**   4x1 texture, each column a distinct colour:
**     col 0 = RED, col 1 = GREEN, col 2 = BLUE, col 3 = WHITE
**   get_text_clmn for NORTH: column = (int)((x - floor(x)) * width)
**     coords.x = 0.25 → col 1 → GREEN
**     coords.x = 0.75 → col 3 → WHITE
**
** ── Scenario 3: EAST column mapping (y fractional part × width) ──────────
**   Same 4x1 texture.
**   get_text_clmn for EAST: column = (int)((y - floor(y)) * width)
**     coords.y = 0.0  → col 0 → RED
**     coords.y = 0.5  → col 2 → BLUE
**
** ── Scenario 4: texture row step sampling ───────────────────────────────
**   1x4 texture, each row a distinct colour:
**     row 0 = RED, row 1 = GREEN, row 2 = BLUE, row 3 = WHITE
**   step = texture->height / heights
**
**   step = 1.0  (heights=4): wall pixels map 1-to-1 onto texture rows
**     y=2→row0(RED)  y=3→row1(GREEN)  y=4→row2(BLUE)  y=5→row3(WHITE)
**
**   step = 2.0  (heights=2): every other texture row is skipped
**     y=2→row0(RED)  y=3→row2(BLUE)
*/

# define C_RED    0xFF0000FFu
# define C_GREEN  0x00FF00FFu
# define C_BLUE   0x0000FFFFu
# define C_WHITE  0xFFFFFFFFu

static void	puterror(const char *name)
{
	dprintf(STDERR_FILENO, "\nThe test: %s - was failed:\n", name);
}

static void	putsuccess(const char *name)
{
	printf("Test: %s - passed!\n", name);
}

/*
** Build a fake mlx_texture_t.  buf must hold w*h*4 bytes.
** pixels_rgba is a flat array of (R,G,B,A) groups, one per pixel,
** in row-major order (row 0 first, within each row column 0 first).
*/
static void	fill_texture(mlx_texture_t *tex, uint8_t *buf,
				uint32_t w, uint32_t h, const uint8_t *rgba)
{
	tex->width = w;
	tex->height = h;
	tex->bytes_per_pixel = 4;
	tex->pixels = buf;
	ft_memcpy(buf, rgba, w * h * 4);
}

/*
** Minimal one-column rays struct wired onto caller-supplied arrays.
*/
static void	make_rays1(t_rays *r,
				int *top, int *bot, int *heights,
				t_texture_id *sides, t_coords *coords,
				int top_v, int bot_v, int h_v,
				t_texture_id side_v, float cx, float cy)
{
	top[0] = top_v;
	bot[0] = bot_v;
	heights[0] = h_v;
	sides[0] = side_v;
	coords[0].x = cx;
	coords[0].y = cy;
	r->count = 1;
	r->top_borders = top;
	r->bot_borders = bot;
	r->heights = heights;
	r->sides = sides;
	r->coords = coords;
}

static int	check(const char *name, uint32_t got, uint32_t expected)
{
	if (got == expected)
	{
		putsuccess(name);
		return (1);
	}
	puterror(name);
	dprintf(STDERR_FILENO, "  expected 0x%08X, got 0x%08X\n", expected, got);
	return (0);
}

/*
** ── Scenario 1: side selection ───────────────────────────────────────────
** Four 1x1 single-colour textures confirm get_text() dispatches correctly.
*/
static int	run_side_selection(void)
{
	/* 1x1 solid textures: RGBA bytes */
	static const uint8_t	px_red[4]   = {255,   0,   0, 255};
	static const uint8_t	px_green[4] = {  0, 255,   0, 255};
	static const uint8_t	px_blue[4]  = {  0,   0, 255, 255};
	static const uint8_t	px_white[4] = {255, 255, 255, 255};
	uint8_t			buf_n[4];
	uint8_t			buf_e[4];
	uint8_t			buf_s[4];
	uint8_t			buf_w[4];
	mlx_texture_t	t_north;
	mlx_texture_t	t_east;
	mlx_texture_t	t_south;
	mlx_texture_t	t_west;
	t_png_textures	pngs;
	t_rays			rays;
	int				top[1];
	int				bot[1];
	int				heights[1];
	t_texture_id	sides[1];
	t_coords		coords[1];
	mlx_image_t		*img;
	t_icoords		start;
	int				passed;

	fill_texture(&t_north, buf_n, 1, 1, px_red);
	fill_texture(&t_east,  buf_e, 1, 1, px_green);
	fill_texture(&t_south, buf_s, 1, 1, px_blue);
	fill_texture(&t_west,  buf_w, 1, 1, px_white);
	pngs.north = &t_north;
	pngs.east  = &t_east;
	pngs.south = &t_south;
	pngs.west  = &t_west;
	make_rays1(&rays, top, bot, heights, sides, coords,
		2, 7, 5, NORTH, 0.0f, 0.0f);
	start.x = 0;
	start.y = 2;
	passed = 0;
	/* NORTH → red */
	img = make_test_image(1, 10);
	rays.sides[0] = NORTH;
	start.y = 2;
	put_textures(img, &rays, &pngs, start);
	passed += check("side NORTH → red texture",  pixel_at(img, 0, 4), C_RED);
	free_test_image(img);
	/* EAST → green */
	img = make_test_image(1, 10);
	rays.sides[0] = EAST;
	start.y = 2;
	put_textures(img, &rays, &pngs, start);
	passed += check("side EAST → green texture", pixel_at(img, 0, 4), C_GREEN);
	free_test_image(img);
	/* SOUTH → blue */
	img = make_test_image(1, 10);
	rays.sides[0] = SOUTH;
	start.y = 2;
	put_textures(img, &rays, &pngs, start);
	passed += check("side SOUTH → blue texture", pixel_at(img, 0, 4), C_BLUE);
	free_test_image(img);
	/* WEST → white */
	img = make_test_image(1, 10);
	rays.sides[0] = WEST;
	start.y = 2;
	put_textures(img, &rays, &pngs, start);
	passed += check("side WEST → white texture", pixel_at(img, 0, 4), C_WHITE);
	free_test_image(img);
	return (passed == 4);
}

/*
** ── Scenario 2: NORTH column mapping ────────────────────────────────────
** 4x1 texture; NORTH side uses x fractional part to pick column.
**   get_text_clmn: column = (int)((crds.x - floor(crds.x)) * width)
*/
static int	run_north_column_mapping(void)
{
	/*
	** pixels: 4 columns × 1 row
	** col0=RED, col1=GREEN, col2=BLUE, col3=WHITE
	*/
	static const uint8_t	col_px[16] = {
		255,   0,   0, 255,   /* col 0: red   */
		  0, 255,   0, 255,   /* col 1: green */
		  0,   0, 255, 255,   /* col 2: blue  */
		255, 255, 255, 255,   /* col 3: white */
	};
	uint8_t			buf[16];
	mlx_texture_t	tex;
	t_png_textures	pngs;
	t_rays			rays;
	int				top[1];
	int				bot[1];
	int				heights[1];
	t_texture_id	sides[1];
	t_coords		coords[1];
	mlx_image_t		*img;
	t_icoords		start;
	int				passed;

	fill_texture(&tex, buf, 4, 1, col_px);
	pngs.north = &tex;
	pngs.east = &tex;
	pngs.west = &tex;
	pngs.south = &tex;
	start.x = 0;
	start.y = 2;
	passed = 0;
	/* coords.x = 0.25 → frac=0.25 → col=(int)(0.25*4)=1 → GREEN */
	make_rays1(&rays, top, bot, heights, sides, coords,
		2, 7, 5, NORTH, 0.25f, 0.0f);
	img = make_test_image(1, 10);
	put_textures(img, &rays, &pngs, start);
	passed += check("NORTH x=0.25 → col 1 (green)", pixel_at(img, 0, 4), C_GREEN);
	free_test_image(img);
	/* coords.x = 0.75 → frac=0.75 → col=(int)(0.75*4)=3 → WHITE */
	make_rays1(&rays, top, bot, heights, sides, coords,
		2, 7, 5, NORTH, 0.75f, 0.0f);
	img = make_test_image(1, 10);
	put_textures(img, &rays, &pngs, start);
	passed += check("NORTH x=0.75 → col 3 (white)", pixel_at(img, 0, 4), C_WHITE);
	free_test_image(img);
	return (passed == 2);
}

/*
** ── Scenario 3: EAST column mapping ─────────────────────────────────────
** Same 4x1 texture; EAST side uses y fractional part to pick column.
**   get_text_clmn: column = (int)((crds.y - floor(crds.y)) * width)
*/
static int	run_east_column_mapping(void)
{
	static const uint8_t	col_px[16] = {
		255,   0,   0, 255,
		  0, 255,   0, 255,
		  0,   0, 255, 255,
		255, 255, 255, 255,
	};
	uint8_t			buf[16];
	mlx_texture_t	tex;
	t_png_textures	pngs;
	t_rays			rays;
	int				top[1];
	int				bot[1];
	int				heights[1];
	t_texture_id	sides[1];
	t_coords		coords[1];
	mlx_image_t		*img;
	t_icoords		start;
	int				passed;

	fill_texture(&tex, buf, 4, 1, col_px);
	pngs.north = &tex;
	pngs.east = &tex;
	pngs.west = &tex;
	pngs.south = &tex;
	start.x = 0;
	start.y = 2;
	passed = 0;
	/* coords.y = 0.0 → frac=0.0 → col=0 → RED */
	make_rays1(&rays, top, bot, heights, sides, coords,
		2, 7, 5, EAST, 0.0f, 0.0f);
	img = make_test_image(1, 10);
	put_textures(img, &rays, &pngs, start);
	passed += check("EAST y=0.0 → col 0 (red)",  pixel_at(img, 0, 4), C_RED);
	free_test_image(img);
	/* coords.y = 0.5 → frac=0.5 → col=(int)(0.5*4)=2 → BLUE */
	make_rays1(&rays, top, bot, heights, sides, coords,
		2, 7, 5, EAST, 0.0f, 0.5f);
	img = make_test_image(1, 10);
	put_textures(img, &rays, &pngs, start);
	passed += check("EAST y=0.5 → col 2 (blue)", pixel_at(img, 0, 4), C_BLUE);
	free_test_image(img);
	return (passed == 2);
}

/*
** ── Scenario 4: texture row step sampling ───────────────────────────────
** 1x4 texture, each row a distinct colour.
** step = texture->height / heights
**
** step=1.0 (heights=4, top=2, bot=6): wall pixels map 1-to-1 onto rows.
**   text_pos_y at y=top+k  =  (y - top_border) * step  =  k * 1.0  =  k
**   y=2→row0(RED) y=3→row1(GREEN) y=4→row2(BLUE) y=5→row3(WHITE)
**
** step=2.0 (heights=2, top=2, bot=4): skips every other row.
**   y=2→row0(RED)  y=3→row2(BLUE)
*/
static int	run_step_sampling(void)
{
	/*
	** pixels: 1 column × 4 rows
	** row0=RED, row1=GREEN, row2=BLUE, row3=WHITE
	*/
	static const uint8_t	row_px[16] = {
		255,   0,   0, 255,   /* row 0: red   */
		  0, 255,   0, 255,   /* row 1: green */
		  0,   0, 255, 255,   /* row 2: blue  */
		255, 255, 255, 255,   /* row 3: white */
	};
	uint8_t			buf[16];
	mlx_texture_t	tex;
	t_png_textures	pngs;
	t_rays			rays;
	int				top[1];
	int				bot[1];
	int				heights[1];
	t_texture_id	sides[1];
	t_coords		coords[1];
	mlx_image_t		*img;
	t_icoords		start;
	int				passed;

	fill_texture(&tex, buf, 1, 4, row_px);
	pngs.north = &tex;
	pngs.east = &tex;
	pngs.west = &tex;
	pngs.south = &tex;
	start.x = 0;
	passed = 0;
	/*
	** step = 1.0: heights=4, texture->height=4
	** bot=6 → end = put_to_limits(6, 10) = 6
	** wall rows: y=2,3,4,5
	*/
	make_rays1(&rays, top, bot, heights, sides, coords,
		2, 6, 4, NORTH, 0.0f, 0.0f);
	img = make_test_image(1, 10);
	start.y = 2;
	put_textures(img, &rays, &pngs, start);
	passed += check("step=1.0: y=2 → row 0 (red)",   pixel_at(img, 0, 2), C_RED);
	passed += check("step=1.0: y=3 → row 1 (green)", pixel_at(img, 0, 3), C_GREEN);
	passed += check("step=1.0: y=4 → row 2 (blue)",  pixel_at(img, 0, 4), C_BLUE);
	passed += check("step=1.0: y=5 → row 3 (white)", pixel_at(img, 0, 5), C_WHITE);
	free_test_image(img);
	/*
	** step = 2.0: heights=2, texture->height=4
	** bot=4 → end = put_to_limits(4, 10) = 4
	** wall rows: y=2,3
	*/
	make_rays1(&rays, top, bot, heights, sides, coords,
		2, 4, 2, NORTH, 0.0f, 0.0f);
	img = make_test_image(1, 10);
	start.y = 2;
	put_textures(img, &rays, &pngs, start);
	passed += check("step=2.0: y=2 → row 0 (red)",  pixel_at(img, 0, 2), C_RED);
	passed += check("step=2.0: y=3 → row 2 (blue)", pixel_at(img, 0, 3), C_BLUE);
	free_test_image(img);
	return (passed == 6);
}

int	main(void)
{
	int	all_ok;

	all_ok = run_side_selection();
	all_ok &= run_north_column_mapping();
	all_ok &= run_east_column_mapping();
	all_ok &= run_step_sampling();
	if (all_ok)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}
