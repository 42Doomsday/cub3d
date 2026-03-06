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
static void				put_ray_pixel(mlx_image_t *img, t_ivec2 point,
						int thickness, uint32_t color);
static void				put_direction_ray(mlx_image_t *img,
						t_player_draw params);

/**
 * @brief Draws the player on the minimap as a filled circle with two
 *        direction rays showing the vertical and horizontal tile edge
 *        crossings from the player's current position.
 *
 * @param img     Target MLX image to draw onto.
 * @param map     Pointer to the map used to derive block size and walls.
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
 * Derives pixel center, radius, ray length, brush thickness, facing angle,
 * world position and block size from the player's current state.
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
	params.map = map;
	block_size = get_block_size(map, img->width, img->height);
	params.block_size = block_size;
	params.center.x = (int)(player->x * block_size) + block_size / 2;
	params.center.y = (int)(player->y * block_size) + block_size / 2;
	params.world_pos.x = player->x;
	params.world_pos.y = player->y;
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
 * @brief Draws one pixel of a direction ray at screen position @p point.
 *
 * Paints a square brush of size @p thickness centred on the given pixel
 * coordinates using the provided @p color.
 *
 * @param img        Target MLX image.
 * @param point      Screen-space pixel coordinates of this ray point.
 * @param thickness  Side length of the square brush in pixels.
 * @param color      RGBA colour to paint.
 */
static void	put_ray_pixel(mlx_image_t *img, t_ivec2 point,
				int thickness, uint32_t color)
{
	int	brush_x;
	int	brush_y;
	int	pixel_x;
	int	pixel_y;

	brush_y = -(thickness / 2);
	while (brush_y <= thickness / 2)
	{
		brush_x = -(thickness / 2);
		while (brush_x <= thickness / 2)
		{
			pixel_x = point.x + brush_x;
			pixel_y = point.y + brush_y;
			if (pixel_x >= 0 && pixel_x < (int)img->width
				&& pixel_y >= 0 && pixel_y < (int)img->height)
				mlx_put_pixel(img, pixel_x, pixel_y, color);
			brush_x++;
		}
		brush_y++;
	}
}

static void	put_direction_ray(mlx_image_t *img, t_player_draw params)
{
	t_vec2		origin;
	t_vec2		hits[2];
	t_ivec2		screen_hit;
	t_ivec2		point;
	int			ray;
	int			step;

	origin.x = params.world_pos.x + 0.5f;
	origin.y = params.world_pos.y + 0.5f;
	cast_ray_both_edges(origin, params.angle, hits);
	ray = 0;
	while (ray < 2)
	{
		screen_hit.x = (int)(hits[ray].x * params.block_size);
		screen_hit.y = (int)(hits[ray].y * params.block_size);
		step = 0;
		while (step <= 100)
		{
			point.x = params.center.x
				+ (screen_hit.x - params.center.x) * step / 100;
			point.y = params.center.y
				+ (screen_hit.y - params.center.y) * step / 100;
			if (ray == 0)
				put_ray_pixel(img, point, params.thickness,
					get_rgba(255, 0, 0, 255));
			else
				put_ray_pixel(img, point, params.thickness,
					get_rgba(0, 0, 255, 255));
			step++;
		}
		ray++;
	}
}
