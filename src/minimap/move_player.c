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

static bool		is_wall(t_map *map, int col, int row);
static float	resolve_x(t_map *map, float dx, float new_x, float cur_y);
static float	resolve_y(t_map *map, float dy, float cur_x, float new_y);

/**
 * @brief Moves the player one step forward in the direction they are facing.
 *
 * Movement is resolved separately on each axis so that the player can slide
 * along walls.  Each axis is either applied freely or snapped to the wall
 * surface at exactly PLAYER_R distance.
 *
 * @param map     Pointer to the map structure used for collision checks.
 * @param player  Pointer to the player whose position will be updated.
 */
void	move_player_forward(t_map *map, t_player *player)
{
	t_vec2	dir;

	dir = direction_from_angle(player->dir);
	dir.x *= PLAYER_STEP;
	dir.y *= PLAYER_STEP;
	player->x = resolve_x(map, dir.x, player->x + dir.x, player->y);
	player->y = resolve_y(map, dir.y, player->x, player->y + dir.y);
}

/**
 * @brief Returns true if tile (col, row) is a wall or out of map bounds.
 *
 * Any tile that is not the open-floor character '0' is treated as solid.
 * Out-of-bounds coordinates are also considered solid.
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
 * @brief Resolves the final X position after attempting to move to new_x.
 *
 * If no wall blocks the path, new_x is returned as-is.  If a wall is
 * found, the player is snapped flush against it at exactly PLAYER_R
 * distance so that no gap or overlap remains.
 *
 * @param map    Pointer to the map structure.
 * @param dx     Horizontal displacement this frame (sign gives direction).
 * @param new_x  Candidate X position after applying the step.
 * @param cur_y  Current Y position (unchanged during X resolution).
 * @return       The furthest reachable X position this frame.
 */
static float	resolve_x(t_map *map, float dx, float new_x, float cur_y)
{
	float	center_x;
	float	center_y;
	int		tile_x;
	int		tile_y;
	int		tile_y_bot;

	center_x = new_x + 0.5f;
	center_y = cur_y + 0.5f;
	if (dx > 0)
		tile_x = (int)floorf(center_x + PLAYER_HITBOX_R);
	else
		tile_x = (int)floorf(center_x - PLAYER_HITBOX_R);
	tile_y = (int)floorf(center_y - PLAYER_R);
	tile_y_bot = (int)floorf(center_y + PLAYER_R - EPS);
	while (tile_y <= tile_y_bot)
	{
		if (is_wall(map, tile_x, tile_y))
		{
			if (dx > 0)
				return (tile_x - PLAYER_HITBOX_R - 0.5f);
			return (tile_x + 1 + PLAYER_HITBOX_R - 0.5f);
		}
		tile_y++;
	}
	return (new_x);
}

/**
 * @brief Resolves the final Y position after attempting to move to new_y.
 *
 * Mirrors the logic of resolve_x() along the Y axis.  On collision the
 * player is snapped flush against the wall at exactly PLAYER_R distance.
 *
 * @param map    Pointer to the map structure.
 * @param dy     Vertical displacement this frame (sign gives direction).
 * @param cur_x  Current X position (unchanged during Y resolution).
 * @param new_y  Candidate Y position after applying the step.
 * @return       The furthest reachable Y position this frame.
 */
static float	resolve_y(t_map *map, float dy, float cur_x, float new_y)
{
	float	center_x;
	float	center_y;
	int		tile_y;
	int		tile_x;
	int		tile_x_right;

	center_x = cur_x + 0.5f;
	center_y = new_y + 0.5f;
	if (dy > 0)
		tile_y = (int)floorf(center_y + PLAYER_HITBOX_R);
	else
		tile_y = (int)floorf(center_y - PLAYER_HITBOX_R);
	tile_x = (int)floorf(center_x - PLAYER_R);
	tile_x_right = (int)floorf(center_x + PLAYER_R - EPS);
	while (tile_x <= tile_x_right)
	{
		if (is_wall(map, tile_x, tile_y))
		{
			if (dy > 0)
				return (tile_y - PLAYER_HITBOX_R - 0.5f);
			return (tile_y + 1 + PLAYER_HITBOX_R - 0.5f);
		}
		tile_x++;
	}
	return (new_y);
}
