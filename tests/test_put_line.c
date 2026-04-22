/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_put_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 00:00:00 by dkalgano          #+#    #+#             */
/*   Updated: 2026/04/09 00:00:00 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"
#include "mock_mlx.h"

typedef struct s_line_case
{
	const char	*name;
	t_coords	start;
	t_coords	end;
	uint32_t	cx;
	uint32_t	cy;
	bool		expect_set;
}	t_line_case;

static void	puterror(const char *name)
{
	dprintf(STDERR_FILENO, "\nThe test: %s - was failed:\n", name);
}

static void	putsuccess(const char *name)
{
	printf("Test: %s - passed!\n", name);
}

int	main(void)
{
	/*
	** Bresenham traces the shortest path between two integer pixel coords.
	**
	** Horizontal (0,3)→(5,3): only row 3 is painted.
	** Vertical   (3,0)→(3,5): only column 3 is painted.
	** Zero-length (3,3)→(3,3): exactly the single endpoint is painted.
	** Diagonal 45° (0,0)→(3,3): steps one pixel per row,
	**   so (0,0),(1,1),(2,2),(3,3) are set; (0,1) and (1,0) are not.
	*/
	static const t_line_case	cases[] = {
		{"horiz (0,3)→(5,3): (0,3) set",
			{0.f, 3.f}, {5.f, 3.f}, 0, 3, true},
		{"horiz (0,3)→(5,3): (3,3) set",
			{0.f, 3.f}, {5.f, 3.f}, 3, 3, true},
		{"horiz (0,3)→(5,3): (5,3) set",
			{0.f, 3.f}, {5.f, 3.f}, 5, 3, true},
		{"horiz (0,3)→(5,3): (0,2) untouched",
			{0.f, 3.f}, {5.f, 3.f}, 0, 2, false},
		{"horiz (0,3)→(5,3): (0,4) untouched",
			{0.f, 3.f}, {5.f, 3.f}, 0, 4, false},
		{"vert  (3,0)→(3,5): (3,0) set",
			{3.f, 0.f}, {3.f, 5.f}, 3, 0, true},
		{"vert  (3,0)→(3,5): (3,3) set",
			{3.f, 0.f}, {3.f, 5.f}, 3, 3, true},
		{"vert  (3,0)→(3,5): (3,5) set",
			{3.f, 0.f}, {3.f, 5.f}, 3, 5, true},
		{"vert  (3,0)→(3,5): (2,0) untouched",
			{3.f, 0.f}, {3.f, 5.f}, 2, 0, false},
		{"vert  (3,0)→(3,5): (4,0) untouched",
			{3.f, 0.f}, {3.f, 5.f}, 4, 0, false},
		{"zero-length (3,3)→(3,3): (3,3) set",
			{3.f, 3.f}, {3.f, 3.f}, 3, 3, true},
		{"zero-length (3,3)→(3,3): (4,3) untouched",
			{3.f, 3.f}, {3.f, 3.f}, 4, 3, false},
		{"zero-length (3,3)→(3,3): (3,4) untouched",
			{3.f, 3.f}, {3.f, 3.f}, 3, 4, false},
		{"diag 45° (0,0)→(3,3): (0,0) set",
			{0.f, 0.f}, {3.f, 3.f}, 0, 0, true},
		{"diag 45° (0,0)→(3,3): (1,1) set",
			{0.f, 0.f}, {3.f, 3.f}, 1, 1, true},
		{"diag 45° (0,0)→(3,3): (3,3) set",
			{0.f, 0.f}, {3.f, 3.f}, 3, 3, true},
		{"diag 45° (0,0)→(3,3): (0,1) untouched",
			{0.f, 0.f}, {3.f, 3.f}, 0, 1, false},
		{"diag 45° (0,0)→(3,3): (1,0) untouched",
			{0.f, 0.f}, {3.f, 3.f}, 1, 0, false},
	};
	mlx_image_t	*img;
	size_t		total;
	size_t		passed;
	bool		result;
	size_t		i;

	total = sizeof(cases) / sizeof(cases[0]);
	passed = 0;
	i = 0;
	while (i < total)
	{
		img = make_test_image(10, 10);
		put_line(img, cases[i].start, cases[i].end, 0xFFFFFFFF);
		result = (pixel_at(img, cases[i].cx, cases[i].cy) != 0);
		free_test_image(img);
		if (result == cases[i].expect_set)
		{
			putsuccess(cases[i].name);
			passed++;
		}
		else
		{
			puterror(cases[i].name);
			dprintf(STDERR_FILENO, "  expected pixel at (%u,%u) to be %s\n",
				cases[i].cx, cases[i].cy,
				cases[i].expect_set ? "set" : "unset");
		}
		i++;
	}
	if (passed == total)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}
