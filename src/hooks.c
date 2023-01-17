/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz <kdoulyaz@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 22:49:47 by kdoulyaz          #+#    #+#             */
/*   Updated: 2023/01/17 01:17:40 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	look_left(t_game *game)
{
	float	olddirx;
	float	oldplanex;

	olddirx = game->player->dir_x;
	oldplanex = game->player->plane_x;
	game->keys.left_arrow = true;
	game->player->dir_x = game->player->dir_x * cos(-game->player->rot_speed)
		- game->player->dir_y * sin(-game->player->rot_speed);
	game->player->dir_y = olddirx * sin(-game->player->rot_speed)
		+ game->player->dir_y * cos(-game->player->rot_speed);
	game->player->plane_x = game->player->plane_x * \
		cos(-game->player->rot_speed) - game->player->plane_y * \
		sin(-game->player->rot_speed);
	game->player->plane_y = oldplanex * sin(-game->player->rot_speed)
		+ game->player->plane_y * cos(-game->player->rot_speed);
}

int	mouse_hooks(int a, int x, int y, t_game *game)
{
	(void)y;
	if (a == 1)
	{
		if (x < (WIDTH - 1) / 2)
			look_left(game);
		else
			look_right(game);
	}
	else if (a == 4)
		down_movement(game);
	else if (a == 5)
		up_movement(game);
	return (0);
}

int	clean_close(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	write(2, "Quit Game\n", 10);
	exit(EXIT_SUCCESS);
	return (0);
}

int	key_hook_pressed(int key, t_game *game)
{
	if (key == SHOW_MAP)
	{
		if (game->keys.show_map)
			game->keys.show_map = false;
		else
			game->keys.show_map = true;
	}
	if (key == KEY_ESC)
		clean_close(game);
	if (key == KEY_W)
		up_movement(game);
	if (key == KEY_A)
		left_movement(game);
	if (key == KEY_S)
		down_movement(game);
	if (key == KEY_D)
		right_movement(game);
	if (key == KEY_LEFT)
		look_left(game);
	if (key == KEY_RIGHT)
		look_right(game);
	return (EXIT_SUCCESS);
}

int	key_hook_released(int key, t_game *game)
{
	if (key == KEY_W && game->keys.w == true)
		game->keys.w = false;
	if (key == KEY_A && game->keys.a == true)
		game->keys.a = false;
	if (key == KEY_S && game->keys.s == true)
		game->keys.s = false;
	if (key == KEY_D && game->keys.d == true)
		game->keys.d = false;
	if (key == KEY_LEFT && game->keys.left_arrow == true)
		game->keys.left_arrow = false;
	if (key == KEY_RIGHT && game->keys.right_arrow == true)
		game->keys.right_arrow = false;
	return (EXIT_SUCCESS);
}
