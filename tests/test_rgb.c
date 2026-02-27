
#include "cub3d.h"

static void	puterror(char *filename);
static void	putsuccess(char *filename);

int main(void)
{
	char	*invalid_cases[] = {
		"255, 0,, 0",
		"255, 0, , 0"
		"255, 0, ",
		"255, 0, 0, 0",
		"255, 0 0 ",
		"255, a, 0",
		"255, -1, 0",
		"256, 0, 0",
		"25 5, 0, 0",
		"2147483649, 0, 0",
		"-2147483649, 0, 0",
		NULL
	};
	char	*valid_cases[] = {
		"255, 0, 0",
		"0, 0, 255",
		"0, 255, 0",
		"0, 0, 0",
		"0,0,0",
		"0,   0   ,  +1  ",
		" 100, 200, 050",
		NULL
	};
	int		*intarr;
	bool	results = true;
	char	*trim;
	char	**strarr;

	for (int i = 0; invalid_cases[i] != NULL; i++)
	{
		trim = ft_strtrim_wht(invalid_cases[i]);
		if(!trim)
			continue;
		strarr = ft_split(trim, ',');
		if (!strarr)
			continue;
		results = validate_rgb(trim, strarr);
		if (results == false)
			putsuccess(invalid_cases[i]);
		else
			puterror(invalid_cases[i]);
		free(trim);
		trim = NULL;
		ft_strarr_free(&strarr);
	}

	for (int i = 0; valid_cases[i] != NULL; i++)
	{
		trim = ft_strtrim_wht(valid_cases[i]);
		intarr = parse_rgb(trim);
		if (!intarr)
			puterror(valid_cases[i]);
		else
		{
			printf("INT OUT: %d, %d, %d\n", intarr[0], intarr[1], intarr[2]);
			putsuccess(valid_cases[i]);
		}
		free(trim);
		trim = NULL;
		free(intarr);
		intarr = NULL;
	}
	return (0);
}

static void	puterror(char *filename)
{
	dprintf(STDERR_FILENO, "\nThe test: %s - was failed:\n", filename);
}

static void	putsuccess(char *filename)
{
	printf("Test: %s - passed!\n", filename);
}
