/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 20:12:02 by mac               #+#    #+#             */
/*   Updated: 2023/01/11 20:33:31 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	put_texture(t_game *game, int x)
{
	int	y;

	y = game->ray->draw_start;
	while (y < game->ray->draw_end)
	{
		game->ray->tex_y = (int)game->ray->tex_pos & (TEX_HEIGHT - 1);
		game->ray->tex_pos += game->ray->step;
		game->ray->color = game->textures[game->ray->tex_num][TEX_HEIGHT
			* game->ray->tex_y + game->ray->tex_x];
		if (game->ray->side == 1)
			game->ray->color = (game->ray->color >> 1) & 8355711;
		game->buf[y][x] = game->ray->color;
		game->res_buff = 1;
		y++;
	}
}

void	draw_ceiling_floor(t_game *game)
{
	if (game->ray->side == 0 && game->ray->ray_dir_x > 0)
	{
		game->ray->floor_x_wall = game->ray->map_x;
		game->ray->floor_y_wall = game->ray->map_y + game->ray->wall_x;
	}
	else if (game->ray->side == 0 && game->ray->ray_dir_x < 0)
	{
		game->ray->floor_x_wall = game->ray->map_x + 1.0;
		game->ray->floor_y_wall = game->ray->map_y + game->ray->wall_x;
	}
	else if (game->ray->side == 1 && game->ray->ray_dir_y > 0)
	{
		game->ray->floor_x_wall = game->ray->map_x + game->ray->wall_x;
		game->ray->floor_y_wall = game->ray->map_y;
	}
	else
	{
		game->ray->floor_x_wall = game->ray->map_x + game->ray->wall_x;
		game->ray->floor_y_wall = game->ray->map_y + 1.0;
	}
}

void	draw_floor(t_game *game, int x)
{
	int	y;

	draw_ceiling_floor(game);
	y = game->ray->draw_end;
	while (y < HEIGHT)
	{
		game->ray->curr_dist = HEIGHT / (2.0 * y - HEIGHT);
		game->ray->weight = game->ray->curr_dist / game->ray->perp_wall_dist;
		game->ray->curr_floor_x = game->ray->weight * game->ray->floor_x_wall
			+ (1.0 - game->ray->weight) * game->player->pos_x;
		game->ray->curr_floor_y = game->ray->weight * game->ray->floor_y_wall
			+ (1.0 - game->ray->weight) * game->player->pos_y;
		game->ray->floor_tex_x = (int)(game->ray->curr_floor_x * TEX_WIDTH)
			% TEX_WIDTH;
		game->ray->floor_tex_y = (int)(game->ray->curr_floor_y * TEX_HEIGHT)
			% TEX_HEIGHT;
		game->ray->color = convert_to_hex(game->floor_rgb);
		game->buf[y][x] = game->ray->color;
		game->ray->color = convert_to_hex(game->ceiling_rgb);
		game->buf[HEIGHT - y][x] = game->ray->color;
		game->res_buff = 1;
		y++;
	}
}
