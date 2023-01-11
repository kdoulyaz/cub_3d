/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz <kdoulyaz@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:38:25 by kdoulyaz          #+#    #+#             */
/*   Updated: 2023/01/11 15:18:21 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	get_direction(t_game *game)
{
	game->player->dir_x = 0;
	game->player->dir_y = 0;
	game->player->plane_x = 0;
	game->player->plane_y = 0;
	if (game->map->view == 'N')
	{
		game->player->dir_y = -1;
		game->player->plane_x = 0.66;
	}
	else if (game->map->view == 'S')
	{
		game->player->dir_y = 1;
		game->player->plane_x = -0.66;
	}
	else if (game->map->view == 'E')
	{
		game->player->dir_x = 1;
		game->player->plane_y = 0.66;
	}
	else if (game->map->view == 'W')
	{
		game->player->dir_x = -1;
		game->player->plane_y = -0.66;
	}
}

int	is_player(char c, t_game *game)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'w')
	{
		game->map->view = c;
		return (1);
	}
	return (0);
}

void	set_player(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map->height)
	{
		j = 0;
		while (j < (int)ft_strlene(game->map->mtrx[i]))
		{
			if (is_player(game->map->mtrx[i][j], game))
			{
				if (game->player->pos_x)
					print_err("Error: More than one player in the map");
				game->player->pos_x = j + 0.2;
				game->player->pos_y = i + 0.2;
			}
			j++;
		}
		i++;
	}
	get_direction(game);
}

void	check_walls(t_game *game, int i, int j)
{
	if (!next_length(game->map, i, j) || !previous_length(game->map, i, j)
		|| game->map->mtrx[i][j + 1] == ' ' || game->map->mtrx[i][j - 1] == ' '
		|| game->map->mtrx[i + 1][j] == ' ' || game->map->mtrx[i - 1][j] == ' '
		|| !game->map->mtrx[i][j + 1] || !game->map->mtrx[i + 1][j] ||
		!game->map->mtrx[i - 1][j])
		print_err("Error: Player is not surrounded by walls");
}

void	get_player(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	if (!game->player->pos_x)
		print_err("Error: No player in the map");
	while (i < game->map->height)
	{
		j = 0;
		while (j < game->map->width && game->map->mtrx[i][j])
		{
			if (is_player(game->map->mtrx[i][j], game))
				check_walls(game, i, j);
			j++;
		}
		i++;
	}
}
