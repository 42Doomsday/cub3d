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
static void				put_direction_ray(t_player_draw params, t_player *player);

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
	put_direction_ray(params, player);
	put_circle(params.img, params.center, params.radius);
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

void put_line(mlx_image_t *img, t_vec2 start, t_vec2 end, uint32_t color)
{
    int dx = abs((int)end.x - (int)start.x);
    int dy = abs((int)end.y - (int)start.y);
    int sx = start.x < end.x ? 1 : -1;
    int sy = start.y < end.y ? 1 : -1;
    int err = dx - dy;
    int x = (int)start.x;
    int y = (int)start.y;

    while (1)
    {
        mlx_put_pixel(img, x, y, color);
        if (x == (int)end.x && y == (int)end.y)
            break;
        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x += sx; }
        if (e2 < dx)  { err += dx; y += sy; }
    }
}

static void	put_direction_ray(t_player_draw params, t_player *player)
{
	(void)player;
	t_vec2  origin;
	t_vec2  wall_coords;
	t_vec2  start_px;
	t_vec2  end_px;
	float   fov;
	float   ray_angle;
	float   step;
	int     rays;
	int     i;

	fov = 60.0f * M_PI / 180.0f;
	rays = params.img->width / 10;
	step = fov / rays;
	origin.x = params.world_pos.x + 0.5f;
	origin.y = params.world_pos.y + 0.5f;
	start_px.x = origin.x * params.block_size;
	start_px.y = origin.y * params.block_size;
	i = 0;
	while (i < rays)
	{
		ray_angle = (params.angle - fov / 2) + step * i;
		wall_coords = cast_ray_to_wall(origin, ray_angle, params.map);
		end_px.x = wall_coords.x * params.block_size;
		end_px.y = wall_coords.y * params.block_size;
		put_line(params.img, start_px, end_px, get_rgba(0, 215, 0, 200));
		i++;
	}
}
