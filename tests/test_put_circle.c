/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_put_circle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 00:00:00 by dkalgano          #+#    #+#             */
/*   Updated: 2026/04/09 00:00:00 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"
#include "mock_mlx.h"

typedef struct s_circle_case
{
	const char	*name;
	t_icoords	center;
	int			radius;
	uint32_t	cx;
	uint32_t	cy;
	bool		expect_set;
}	t_circle_case;

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
	** put_circle fills all pixels where dx²+dy² <= r².
	** r=0: only center pixel is set.
	** r=2, center (5,5):
	**   (7,5) dx=2 dy=0  d²=4  <= 4  → set
	**   (8,5) dx=3 dy=0  d²=9  >  4  → unset
	**   (5,7) dx=0 dy=2  d²=4  <= 4  → set
	**   (5,8) dx=0 dy=3  d²=9  >  4  → unset
	**   (4,4) dx=-1 dy=-1 d²=2 <= 4  → set
	**   (3,3) dx=-2 dy=-2 d²=8 >  4  → unset
	*/
	static const t_circle_case	cases[] = {
		{"r=0: center (5,5) set",
			{5, 5}, 0, 5, 5, true},
		{"r=0: (5,6) untouched",
			{5, 5}, 0, 5, 6, false},
		{"r=0: (6,5) untouched",
			{5, 5}, 0, 6, 5, false},
		{"r=2: center (5,5) set",
			{5, 5}, 2, 5, 5, true},
		{"r=2: (7,5) on boundary set (d²=4)",
			{5, 5}, 2, 7, 5, true},
		{"r=2: (8,5) outside unset (d²=9)",
			{5, 5}, 2, 8, 5, false},
		{"r=2: (5,7) on boundary set (d²=4)",
			{5, 5}, 2, 5, 7, true},
		{"r=2: (5,8) outside unset (d²=9)",
			{5, 5}, 2, 5, 8, false},
		{"r=2: (4,4) inside set (d²=2)",
			{5, 5}, 2, 4, 4, true},
		{"r=2: (3,3) outside unset (d²=8)",
			{5, 5}, 2, 3, 3, false},
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
		img = make_test_image(15, 15);
		put_circle(img, cases[i].center, cases[i].radius);
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
