/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_screen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkalgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 12:30:05 by dkalgano          #+#    #+#             */
/*   Updated: 2026/03/10 16:13:53 by dkalgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    put_game_screen(mlx_image_t *img, t_map *map, t_player *player)
{
    float   rays_arr[img->width];
    t_vec2  origin;
    float   fov;
    float   angle;
    float   ray_angle;
    float   step;
    float   proj_plane;
    int     rays;
    int     i;

    fov = 60.0f * M_PI / 180.0f;
    rays = img->width;
    step = fov / rays;
    origin.x = player->x + 0.5f;
    origin.y = player->y + 0.5f;
    angle = (90.0f - player->rotation) * M_PI / 180.0f;
    proj_plane = (img->width / 2.0f) / tan(fov / 2.0f);

    // 1. Заполняем массив расстояний
    i = 0;
    while (i < rays)
    {
        ray_angle = (angle - fov / 2) + step * i;
        rays_arr[i] = get_dist_to_wall(origin, ray_angle, map);
        // Fish-eye коррекция
        rays_arr[i] *= cos(ray_angle - angle);
        i++;
    }

    // 2. Рисуем колонны
    i = 0;
    while (i < rays)
    {
        int col_height = (int)(proj_plane / rays_arr[i]);
        int top = (img->height / 2) - (col_height / 2);
        int bot = (img->height / 2) + (col_height / 2);

        // Clamp
        if (top < 0) top = 0;
        if (bot > (int)img->height) bot = img->height;

        // Потолок
        int j = 0;
        while (j < top)
        {
            mlx_put_pixel(img, i, j, get_rgba(30, 30, 30, 255));
            j++;
        }
        // Стена
        while (j < bot)
        {
            mlx_put_pixel(img, i, j, get_rgba(180, 100, 60, 255));
            j++;
        }
        // Пол
        while (j < (int)img->height)
        {
            mlx_put_pixel(img, i, j, get_rgba(80, 60, 40, 255));
            j++;
        }
        i++;
    }
}

