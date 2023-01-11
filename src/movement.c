/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz <kdoulyaz@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 22:58:10 by kdoulyaz          #+#    #+#             */
/*   Updated: 2023/01/11 23:27:25 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	down_movement(t_game *game)
{
	game->keys.s = true;
	if (game->map->mtrx[(int)(game->player->pos_y - game->player->dir_y
			* game->player->move_speed * 2)][(int)(game->player->pos_x)] != '1')
			game->player->pos_y -= game->player->dir_y * \
			game->player->move_speed;
	if (game->map->mtrx[(int)(game->player->pos_y)][(int)(game->player->pos_x
			- game->player->dir_x * game->player->move_speed * 2)] != '1')
			game->player->pos_x -= game->player->dir_x * \
			game->player->move_speed;
}

void	up_movement(t_game *game)
{
	game->keys.w = true;
	if (game->map->mtrx[(int)(game->player->pos_y + game->player->dir_y
			* game->player->move_speed * 2)][(int)(game->player->pos_x)] != '1')
			game->player->pos_y += game->player->dir_y * \
			game->player->move_speed;
	if (game->map->mtrx[(int)(game->player->pos_y)][(int)(game->player->pos_x
			+ game->player->dir_x * game->player->move_speed * 2)] != '1')
			game->player->pos_x += game->player->dir_x \
			* game->player->move_speed;
}

void	left_movement(t_game *game)
{
	game->keys.a = true;
	if (game->map->mtrx[(int)(game->player->pos_y - game->player->move_speed
			* game->player->dir_x * 2)][(int)(game->player->pos_x
			+ game->player->move_speed * game->player->dir_y * 2)] != '1')
	{
		game->player->pos_y -= game->player->move_speed * game->player->dir_x;
		game->player->pos_x += game->player->move_speed * game->player->dir_y;
	}
}

void	right_movement(t_game *game)
{
	game->keys.d = true;
	if (game->map->mtrx[(int)(game->player->pos_y + 2 * \
		game->player->move_speed * game->player->dir_x)][(int) \
		(game->player->pos_x - 2 * game->player->move_speed * \
		game->player->dir_y)] != '1')
	{
		game->player->pos_y += game->player->move_speed * game->player->dir_x;
		game->player->pos_x -= game->player->move_speed * game->player->dir_y;
	}
}

void	look_right(t_game *game)
{
	float	old_dir_x;
	float	old_plane_x;

	old_dir_x = game->player->dir_x;
	old_plane_x = game->player->plane_x;
	game->keys.right_arrow = true;
	game->player->dir_x = game->player->dir_x * cos(game->player->rot_speed)
		- game->player->dir_y * sin(game->player->rot_speed);
	game->player->dir_y = old_dir_x * sin(game->player->rot_speed)
		+ game->player->dir_y * cos(game->player->rot_speed);
	game->player->plane_x = game->player->plane_x * cos(game->player->rot_speed)
		- game->player->plane_y * sin(game->player->rot_speed);
	game->player->plane_y = old_plane_x * sin(game->player->rot_speed)
		+ game->player->plane_y * cos(game->player->rot_speed);
}
