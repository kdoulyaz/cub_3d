/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 19:58:41 by mac               #+#    #+#             */
/*   Updated: 2023/01/11 20:29:54 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_ray(t_game *game, int x)
{
	game->ray->camera_x = 2 * x / (float) WIDTH - 1;
	game->ray->ray_dir_x = game->player->dir_x
		+ game->player->plane_x * game->ray->camera_x;
	game->ray->ray_dir_y = game->player->dir_y
		+ game->player->plane_y * game->ray->camera_x;
	game->ray->map_x = (int) game->player->pos_x;
	game->ray->map_y = (int) game->player->pos_y;
	game->ray->delta_dist_x = fabs(1 / game->ray->ray_dir_x);
	game->ray->delta_dist_y = fabs(1 / game->ray->ray_dir_y);
	game->ray->hit = 0;
}

void	init_stepside_dist(t_game *game)
{
	if (game->ray->ray_dir_x < 0)
	{
		game->ray->step_x = -1;
		game->ray->side_dist_x = (game->player->pos_x
				- game->ray->map_x) * game->ray->delta_dist_x;
	}
	else
	{
		game->ray->step_x = 1;
		game->ray->side_dist_x = (game->ray->map_x + 1.0
				- game->player->pos_x) * game->ray->delta_dist_x;
	}
	if (game->ray->ray_dir_y < 0)
	{
		game->ray->step_y = -1;
		game->ray->side_dist_y = (game->player->pos_y
				- game->ray->map_y) * game->ray->delta_dist_y;
	}
	else
	{
		game->ray->step_y = 1;
		game->ray->side_dist_y = (game->ray->map_y + 1.0
				- game->player->pos_y) * game->ray->delta_dist_y;
	}
}

void	dda(t_game *game)
{
	while (game->ray->hit == 0)
	{
		if (game->ray->side_dist_x < game->ray->side_dist_y)
		{
			game->ray->side_dist_x += game->ray->delta_dist_x;
			game->ray->map_x += game->ray->step_x;
			game->ray->side = 0;
		}
		else
		{
			game->ray->side_dist_y += game->ray->delta_dist_y;
			game->ray->map_y += game->ray->step_y;
			game->ray->side = 1;
		}
		if (game->map->mtrx[game->ray->map_y][game->ray->map_x] == '1')
			game->ray->hit = 1;
	}
}

void	texture_id(t_game *game)
{
	if (game->ray->side == 0)
	{
		if (game->ray->ray_dir_x > 0)
			game->ray->tex_num = 0;
		else
			game->ray->tex_num = 1;
	}
	else
	{
		if (game->ray->ray_dir_y > 0)
			game->ray->tex_num = 2;
		else
			game->ray->tex_num = 3;
	}
}

void	calculate_ray_draw(t_game *game)
{
	if (game->ray->side == 0)
		game->ray->perp_wall_dist = (game->ray->map_x - game->player->pos_x
				+ (1 - game->ray->step_x) / 2) / game->ray->ray_dir_x;
	else
		game->ray->perp_wall_dist = (game->ray->map_y - game->player->pos_y
				+ (1 - game->ray->step_y) / 2) / game->ray->ray_dir_y;
	game->ray->line_height = (int)(HEIGHT / game->ray->perp_wall_dist);
	game->ray->draw_start = -game->ray->line_height / 2 + HEIGHT / 2;
	if (game->ray->draw_start < 0)
		game->ray->draw_start = 0;
	game->ray->draw_end = game->ray->line_height / 2 + HEIGHT / 2;
	if (game->ray->draw_end >= HEIGHT)
		game->ray->draw_end = HEIGHT - 1;
}

void	calc_screen_line(t_game *game)
{
	calculate_ray_draw(game);
	if (game->ray->side == 0)
		game->ray->wall_x = game->player->pos_y
			+ game->ray->perp_wall_dist * game->ray->ray_dir_y;
	else
		game->ray->wall_x = game->player->pos_x
			+ game->ray->perp_wall_dist * game->ray->ray_dir_x;
	game->ray->wall_x -= floor(game->ray->wall_x);
	game->ray->tex_x = (int)(game->ray->wall_x * (double)TEX_WIDTH);
	if (game->ray->side == 0 && game->ray->ray_dir_x > 0)
		game->ray->tex_x = TEX_WIDTH - game->ray->tex_x - 1;
	if (game->ray->side == 1 && game->ray->ray_dir_y < 0)
		game->ray->tex_x = TEX_WIDTH - game->ray->tex_x - 1;
	game->ray->step = 1.0 * TEX_HEIGHT / game->ray->line_height;
	game->ray->tex_pos = (game->ray->draw_start - HEIGHT / 2
			+ game->ray->line_height / 2) * game->ray->step;
}
