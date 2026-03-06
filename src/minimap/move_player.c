/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <dkalgano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 00:00:00 by dkalgano         #+#    #+#             */
/*   Updated: 2026/03/06 00:00:00 by dkalgano        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_vec2	direction_from_angle(float rotation);
static bool		is_wall(t_map *map, int col, int row);
static bool		collides_on_x(t_map *map, float dx, float new_x, float cur_y);
static bool		collides_on_y(t_map *map, float dy, float cur_x, float new_y);

/**
 * @brief Moves the player one step forward in the direction they are facing.
 *
 * Movement is resolved separately on each axis (X then Y) so that the player
 * can slide along walls instead of stopping dead on diagonal contact.
 * Each axis is tested for collision independently; only the blocked axis is
 * suppressed.
 *
 * @param map     Pointer to the map structure used for collision checks.
 * @param player  Pointer to the player whose position will be updated.
 */
void	move_player_forward(t_map *map, t_player *player)
{
	t_vec2	dir;
	float	new_x;
	float	new_y;

	dir = direction_from_angle(player->rotation);
	dir.x *= PLAYER_STEP;
	dir.y *= PLAYER_STEP;
	new_x = player->x + dir.x;
	new_y = player->y + dir.y;
	if (!collides_on_x(map, dir.x, new_x, player->y))
		player->x = new_x;
	if (!collides_on_y(map, dir.y, player->x, new_y))
		player->y = new_y;
}

/**
 * @brief Converts a player rotation angle (degrees) into a world-space
 *        movement direction vector.
 *
 * Rotation is measured clockwise from north (0° = up, 90° = right).
 * Internally the angle is converted to the standard mathematical convention
 * so that it can be fed directly to cosf() and sinf().
 *
 * @param rotation  Player's current rotation in degrees.
 * @return          Direction vector (dx, dy) of unit length.
 */
static t_vec2	direction_from_angle(float rotation)
{
	t_vec2	dir;
	float	radians;

	radians = (90.0f - rotation) * M_PI / 180.0f;
	dir.x = cosf(radians);
	dir.y = -sinf(radians);
	return (dir);
}

/**
 * @brief Returns true if tile (col, row) is a wall or out of map bounds.
 *
 * Any tile that is not the open-floor character '0' is treated as solid.
 * Out-of-bounds coordinates are also considered solid to prevent the player
 * from walking off the map edge.
 *
 * @param map   Pointer to the map structure.
 * @param col   Tile column index (X axis).
 * @param row   Tile row index    (Y axis).
 * @return      true if the tile blocks movement, false otherwise.
 */
static bool	is_wall(t_map *map, int col, int row)
{
	if (col < 0 || col >= map->width)
		return (true);
	if (row < 0 || row >= map->height)
		return (true);
	return (map->data[row][col] != '0');
}

/**
 * @brief Checks for a wall collision when the player moves along the X axis.
 *
 * The player is modelled as an axis-aligned square with half-size PLAYER_R.
 * Only the leading edge in the direction of movement (@p dx) is tested.
 * All tiles that overlap the player's vertical extent at the new X position
 * are checked.
 *
 * @param map    Pointer to the map structure.
 * @param dx     Horizontal displacement this frame (can be negative).
 * @param new_x  Candidate X grid position after applying the step.
 * @param cur_y  Current  Y grid position (unchanged on X-only move).
 * @return       true if a blocking tile is found, false if movement is free.
 */
static bool	collides_on_x(t_map *map, float dx, float new_x, float cur_y)
{
	float	cx;
	float	cy;
	int		tile_x;
	int		tile_y;
	int		tile_y_bot;

	cx = new_x + 0.5f;
	cy = cur_y + 0.5f;
	if (dx > 0)
		tile_x = (int)floorf(cx + PLAYER_R);
	else
		tile_x = (int)floorf(cx - PLAYER_R);
	tile_y = (int)floorf(cy - PLAYER_R);
	tile_y_bot = (int)floorf(cy + PLAYER_R - EPS);
	while (tile_y <= tile_y_bot)
	{
		if (is_wall(map, tile_x, tile_y))
			return (true);
		tile_y++;
	}
	return (false);
}

/**
 * @brief Checks for a wall collision when the player moves along the Y axis.
 *
 * Mirrors the logic of collides_on_x() but sweeps horizontally across the
 * player's width while testing the leading edge in the Y direction.
 *
 * @param map    Pointer to the map structure.
 * @param dy     Vertical displacement this frame (can be negative).
 * @param cur_x  Current  X grid position (unchanged on Y-only move).
 * @param new_y  Candidate Y grid position after applying the step.
 * @return       true if a blocking tile is found, false if movement is free.
 */
static bool	collides_on_y(t_map *map, float dy, float cur_x, float new_y)
{
	float	cx;
	float	cy;
	int		tile_x;
	int		tile_x_right;
	int		tile_y;

	cx = cur_x + 0.5f;
	cy = new_y + 0.5f;
	if (dy > 0)
		tile_y = (int)floorf(cy + PLAYER_R);
	else
		tile_y = (int)floorf(cy - PLAYER_R);
	tile_x = (int)floorf(cx - PLAYER_R);
	tile_x_right = (int)floorf(cx + PLAYER_R - EPS);
	while (tile_x <= tile_x_right)
	{
		if (is_wall(map, tile_x, tile_y))
			return (true);
		tile_x++;
	}
	return (false);
}
