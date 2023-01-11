/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz <kdoulyaz@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 22:08:50 by kdoulyaz          #+#    #+#             */
/*   Updated: 2023/01/10 18:16:16 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	norm(t_game *game)
{
	game->player->angle = ANGLE;
	game->floor_rgb->r = -1;
	game->floor_rgb->g = -1;
	game->floor_rgb->b = -1;
	game->ceiling_rgb->r = -1;
	game->ceiling_rgb->g = -1;
	game->ceiling_rgb->b = -1;
	return ;
}

void	init_params(t_game *game)
{
	game->map->height = 1;
	game->map->width = 1;
	game->player = malloc(sizeof(t_player));
	game->floor_rgb = malloc(sizeof(t_rgb));
	game->ceiling_rgb = malloc(sizeof(t_rgb));
	if (!game->map || !game->player || !game->floor_rgb || !game->ceiling_rgb)
		(write(2, "Error : Malloc() failed\n", 24), exit(EXIT_FAILURE));
	game->zoom = ZOOM;
	game->no = 0;
	game->so = 0;
	game->we = 0;
	game->ea = 0;
	game->map->view = ' ';
	game->floor = 0;
	game->ceiling = 0;
	game->player->move_speed = SPEED;
	game->player->rot_speed = 0.05;
	game->player->pos_x = 0;
	game->player->pos_y = 0;
	game->player->plane_x = 0;
	game->player->plane_y = 0;
	norm(game);
	return ;
}

void	init_textures(t_game *game)
{
	int	i;
	int	j;

	game->textures = (int **)malloc(sizeof(int *) * 8);
	if (!game->textures)
		(write(2, "Error : Malloc() failed\n", 24), exit(EXIT_FAILURE));
	i = -1;
	while (++i < 8)
	{
		game->textures[i] = (int *)malloc(sizeof(int) * TEX_WIDTH * TEX_HEIGHT);
		if (!game->textures)
			(write(2, "Error : Malloc() failed\n", 24), exit(EXIT_FAILURE));
	}
	i = -1;
	while (++i < 8)
	{
		j = -1;
		while (++j < TEX_WIDTH * TEX_HEIGHT)
			game->textures[i][j] = 0;
	}
}

void	init_game(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (++i < HEIGHT)
	{
		j = -1;
		while (++j < WIDTH)
			game->buf[i][j] = 0;
	}
}
