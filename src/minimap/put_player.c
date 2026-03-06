/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <dkalgano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 00:00:00 by dkalgano         #+#    #+#             */
/*   Updated: 2026/03/06 00:00:00 by dkalgano        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_player_draw	make_draw_params(mlx_image_t *img,
							t_map *map, t_player *player);
static void				put_circle(mlx_image_t *img,
							t_ivec2 center, int radius);
static void				put_ray_pixel(mlx_image_t *img,
							t_ivec2 center, t_player_draw params, int step);
static void				put_direction_ray(mlx_image_t *img,
							t_player_draw params);

/**
 * @brief Draws the player on the minimap as a filled circle with a
 *        direction ray indicating the facing angle.
 *
 * @param img     Target MLX image to draw onto.
 * @param map     Pointer to the map used to derive the block size.
 * @param player  Pointer to the player whose position and rotation to draw.
 */
void	put_player(mlx_image_t *img, t_map *map, t_player *player)
{
	t_player_draw	params;

	params = make_draw_params(img, map, player);
	put_circle(params.img, params.center, params.radius);
	put_direction_ray(params.img, params);
}

/**
 * @brief Computes all screen-space drawing parameters for the player.
 *
 * Derives pixel center, radius, ray length, brush thickness and the
 * facing angle in radians from the player's current world state and
 * the block size of the minimap.
 *
 * @param img     Target MLX image (stored into the result for convenience).
 * @param map     Pointer to the map used to compute the block size.
 * @param player  Pointer to the player providing position and rotation.
 * @return        Fully populated t_player_draw parameter struct.
 */
static t_player_draw	make_draw_params(mlx_image_t *img,
						t_map *map, t_player *player)
{
	t_player_draw	params;
	int				block_size;

	params.img = img;
	block_size = get_block_size(map, img->width, img->height);
	params.center.x = (int)(player->x * block_size) + block_size / 2;
	params.center.y = (int)(player->y * block_size) + block_size / 2;
	params.radius = block_size / 4;
	params.ray_len = block_size / 2;
	params.thickness = block_size / 20;
	params.angle = (90.0f - player->rotation) * M_PI / 180.0f;
	return (params);
}

/**
 * @brief Fills a circle of the given radius centred at @p center with
 *        the player body colour (green).
 *
 * Iterates over the bounding square and writes only pixels whose squared
 * distance from the centre is within the squared radius.
 *
 * @param img     Target MLX image.
 * @param center  Pixel coordinates of the circle centre.
 * @param radius  Circle radius in pixels.
 */
static void	put_circle(mlx_image_t *img, t_ivec2 center, int radius)
{
	int	offset_x;
	int	offset_y;

	offset_y = -radius;
	while (offset_y <= radius)
	{
		offset_x = -radius;
		while (offset_x <= radius)
		{
			if (offset_x * offset_x + offset_y * offset_y <= radius * radius)
				mlx_put_pixel(img,
					center.x + offset_x,
					center.y + offset_y,
					get_rgba(0, 255, 0, 255));
			offset_x++;
		}
		offset_y++;
	}
}

/**
 * @brief Draws a single thick point of the direction ray at a given step
 *        distance from the edge of the player circle.
 *
 * Computes the floating-point screen offset for this step from the angle
 * stored in @p params, then paints a square brush of size params.thickness
 * centred on that offset.
 *
 * @param img     Target MLX image.
 * @param center  Pixel centre of the player circle.
 * @param params  Drawing parameters providing angle, radius and thickness.
 * @param step    Current step index along the ray (0 = circle edge).
 */
static void	put_ray_pixel(mlx_image_t *img, t_ivec2 center,
				t_player_draw params, int step)
{
	float	offset_x;
	float	offset_y;
	int		brush_x;
	int		brush_y;

	offset_x = (params.radius + step) * cosf(params.angle);
	offset_y = -(params.radius + step) * sinf(params.angle);
	brush_y = -(params.thickness / 2);
	while (brush_y <= params.thickness / 2)
	{
		brush_x = -(params.thickness / 2);
		while (brush_x <= params.thickness / 2)
		{
			mlx_put_pixel(img,
				center.x + (int)(offset_x + 0.5f) + brush_x,
				center.y + (int)(offset_y + 0.5f) + brush_y,
				get_rgba(255, 0, 0, 255));
			brush_x++;
		}
		brush_y++;
	}
}

/**
 * @brief Draws the full direction ray from the edge of the player circle
 *        outward along the facing angle.
 *
 * Steps along the ray one pixel at a time, forwarding each step index
 * to put_ray_pixel() which computes the exact screen position.
 *
 * @param img     Target MLX image.
 * @param params  Drawing parameter struct produced by make_draw_params().
 */
static void	put_direction_ray(mlx_image_t *img, t_player_draw params)
{
	int	step;

	step = 0;
	while (step <= params.ray_len)
	{
		put_ray_pixel(img, params.center, params, step);
		step++;
	}
}
