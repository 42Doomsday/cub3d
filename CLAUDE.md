# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## RULES

**Never modify any file inside `src/` without first asking the user for permission.** This means: after analysis or when a fix is ready, always ask "Do you want me to apply this?" before touching any file under `src/`. Do not assume permission even when a fix seems obvious or implied. Analysis, suggestions, and test writing are always allowed without asking.

## Project

cub3d is a 42 School raycasting project — a Wolfenstein-style 3D renderer written in C, using MLX42 (OpenGL/GLFW) for graphics and a custom libft standard library.

## Build Commands

```bash
make           # build cub3d binary (also builds libft and MLX42 via cmake)
make re        # clean rebuild
make clean     # remove build/ and MLX42/build/
make fclean    # clean + remove binary and libft.a
```

Run the game:
```bash
./cub3d <map.cub>
```

Run all tests:
```bash
make test
```

Run tests by category:
```bash
make test-parsing   # parsing tests only
make test-rays      # ray/DDA tests only
make test-minimap   # minimap rendering tests only
make test-game      # game logic and rendering tests only
```

Run a single test binary (build first):
```bash
./build/test_is_closed
./build/test_parse_map
./build/test_cast_ray
# etc.
```

Check for memory leaks (requires valgrind):
```bash
make test-leaks
```

Compiler flags: `-Wall -Wextra -Werror -g -O3`. Tests use `-g` without `-O3`.

## Architecture

### Initialization pipeline (`src/initialize.c`)

`init_info()` runs a chain: validate path → `parse()` → load PNG textures → `mlx_init` → allocate rays + game images. Failure at any stage frees everything allocated so far.

### Main struct (`t_cub3d`, `include/cub3d.h`)

All subsystems live inside `t_cub3d_data data` (value, owns memory). `t_cub3d` holds pointer aliases into `data` for convenience. The `t_world` struct is a thin grouping of `*map` and `*player` passed to movement code.

### Parsing (`src/parsing/`)

Parses `.cub` config files. Format: texture paths (`NO`, `SO`, `WE`, `EA`), floor/ceiling RGB (`F`, `C`), then the map grid. Entry point: `parse()` → `parse_textures()` then `parse_map()`. Map validation uses flood-fill (`helpers/flood_fill.c`) and wall-closure checks (`helpers/is_closed.c`). Map characters: `0`=open, `1`=wall, `N/E/W/S`=player start. Tabs in map data are expanded to 4 spaces (`helpers/expand_tabs.c`).

### Raycasting (`src/rays/`)

DDA (Digital Differential Analysis) algorithm. `get_all_rays()` in `cast_ray.c` iterates over each screen column. `cast_ray_to_border()` steps the ray to the nearest grid boundary on either axis, calling `is_wall()` to check if a wall was hit. Wall side (NORTH/SOUTH/EAST/WEST) is determined by `get_side_of_wall()`. Fish-eye correction: distance is multiplied by `cosf(ray_angle - player_angle)`. Results stored in parallel arrays inside `t_rays`.

### `is_wall` logic (`src/rays/is_wall.c`)

A ray position can land in three states:

- **Mid-cell** — neither coordinate is an integer: `floor(x)` and `floor(y)` directly give the tile.
- **Single-axis edge** — exactly one coordinate is an integer (on a grid line): `get_block_coord` picks the correct adjacent tile based on the sign of the ray's unit vector on that axis.
- **Exact corner** — both coordinates are integers (the ray lands on a grid-point where 4 tiles meet): **both axes** must use `get_block_coord` to select the single tile the ray is entering.

  ```
     (x-1,y-1) | (x, y-1)
     -----------+-----------
     (x-1, y)  | (x,  y)
                ^ corner point
  ```

  Correct cell by direction:

  | Ray direction | Cell entered |
  |---------------|-------------|
  | NW `(ux<0, uy<0)` | `(x-1, y-1)` |
  | NE `(ux>0, uy<0)` | `(x,   y-1)` |
  | SW `(ux<0, uy>0)` | `(x-1, y  )` |
  | SE `(ux>0, uy>0)` | `(x,   y  )` |

  The `x > 0 && y > 0` guard is required before the corner/edge checks because `get_block_coord` can produce `x-1 = -1` which would be an invalid map coordinate.

### Rendering (`src/game/`, `src/minimap/`)

`get_frame()` (called each MLX loop tick) runs: `get_all_rays` → `put_game_screen` → `put_minimap` → `mlx_scale_image_into`. The game renders to a full-resolution `game` image, which is scaled down into a smaller `window` image for display (the minimap overlaps). `put_textures.c` handles texture-mapped wall columns using the `t_png_textures` (loaded MLX textures).

### Angle system

Player direction is stored as degrees in `t_direct.degree`, with corresponding `radians` and a precomputed unit `t_vec2`. Rays are spread across `FOV=60°` centered on the player direction. Angles are **not** in classic math notation (north ≠ 90°).

`convert_degree_to_radians(d)` = `(90 - d) * PI / 180`. Consequence: North=0°→unit(0,-1), East=90°→unit(1,0), South=180°→unit(0,1), West=270°→unit(-1,0). `move_player(world, degree, delta)` adds the converted `degree` to `player->dir.radians` before normalizing; W-key passes 90 (straight ahead), S-key 270 (backward), A-key 0 (strafe left). D-key currently passes 190 instead of 180 (known asymmetry bug).

### Tests (`tests/`)

Each test is an independent C program in `tests/test_<name>.c`. Tests do not use any framework — just `EXIT_SUCCESS`/`EXIT_FAILURE` return codes. Multiple named cases run inside each binary via a struct array, printing `Test: <name> - passed!` per case.

**Parsing tests** — test the `.cub` file parsing pipeline. Link against `PARSING_SRC` + `UTILS_SRC` + `libft`.

**Ray tests** — test the DDA raycasting math (`src/rays/`). Link against `RAYS_SRC` + `UTILS_SRC` + `libft`. Ray sources include `cub3d.h` (and therefore `MLX42.h`) but call no MLX functions, so they link without libmlx42.

**Minimap tests** — test `src/minimap/` drawing primitives (`put_square`, `put_circle`, `put_line`, `make_draw_params`). Use `mock_mlx.c` which stubs `mlx_put_pixel` and provides `make_test_image`/`free_test_image`/`pixel_at` helpers. Link against `MINIMAP_SRC` + `utils/common.o` + `mock_mlx.o` + `libft`.

**Game tests** — test `src/game/` logic and rendering. Link against `GAME_SRC` + `rays/is_wall.o` + `utils/common.o` + `mock_mlx.o` + `libft`.
- `test_move_player` — collision/clamping: player is stopped at walls (PLAYER_HITBOX_R = 0.3) in all four cardinal directions.
- `test_put_game_screen` — pixel-level rendering: verifies ceiling, wall (texture), and floor regions land in the correct rows with the correct colour values.

`print_error` is defined in `src/utils/common.c` (part of `UTILS_SRC`) so it is available to all test categories without pulling in the MLX-dependent `cleanup.c`.

## Known Bugs (from README)

- Minimap ray artifacts when directed north
- Corner collision issues
- Collision bugs with large delta time
- Left/right rotation speed asymmetry
- East-south corner rays don't always reach the wall
