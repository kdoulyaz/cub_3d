/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz <kdoulyaz@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 15:31:52 by kdoulyaz          #+#    #+#             */
/*   Updated: 2023/01/11 15:47:05 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	init(t_game *game)
{
	game->keys.a = false;
	game->keys.w = false;
	game->keys.s = false;
	game->keys.d = false;
	game->keys.left_arrow = false;
	game->keys.right_arrow = false;
	game->keys.show_map = false;
	game->ray = (t_ray *)malloc(sizeof(t_ray));
	if (!game->ray)
		(write(2, "Error : Malloc() failed\n", 24), exit(EXIT_FAILURE));
	return (0);
}

int	mlx_exec(t_game *game)
{
	if (init(game))
	{
		free_game(game);
		(write(2, "cub3D: malloc() failed\n", 23), exit(EXIT_FAILURE));
	}
	game->mlx = mlx_init();
	return (0);
}
