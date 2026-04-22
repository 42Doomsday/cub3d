/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_put_square.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 00:00:00 by dkalgano          #+#    #+#             */
/*   Updated: 2026/04/09 00:00:00 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"
#include "mock_mlx.h"

typedef struct s_sq_case
{
	const char		*name;
	t_render_obj	square;
	uint32_t		cx;
	uint32_t		cy;
	bool			expect_set;
}	t_sq_case;

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
	** A 3x3 square at (2,2) must cover columns 2..4, rows 2..4.
	** Pixels outside that region must stay zero (calloc'd image).
	** A size=1 square at (3,3) must cover exactly one pixel.
	*/
	static const t_sq_case	cases[] = {
		{"3x3 sq: corner (2,2) set",
			{2, 2, 3, 0x64646464}, 2, 2, true},
		{"3x3 sq: center (3,3) set",
			{2, 2, 3, 0x64646464}, 3, 3, true},
		{"3x3 sq: far corner (4,4) set",
			{2, 2, 3, 0x64646464}, 4, 4, true},
		{"3x3 sq: left of sq (1,2) untouched",
			{2, 2, 3, 0x64646464}, 1, 2, false},
		{"3x3 sq: right of sq (5,2) untouched",
			{2, 2, 3, 0x64646464}, 5, 2, false},
		{"3x3 sq: above sq (2,1) untouched",
			{2, 2, 3, 0x64646464}, 2, 1, false},
		{"3x3 sq: below sq (2,5) untouched",
			{2, 2, 3, 0x64646464}, 2, 5, false},
		{"size=1 sq: only (3,3) set",
			{3, 3, 1, 0x64646464}, 3, 3, true},
		{"size=1 sq: (2,3) untouched",
			{3, 3, 1, 0x64646464}, 2, 3, false},
		{"size=1 sq: (4,3) untouched",
			{3, 3, 1, 0x64646464}, 4, 3, false},
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
		put_square(img, cases[i].square);
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
