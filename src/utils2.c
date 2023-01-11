/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz <kdoulyaz@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 18:40:12 by kdoulyaz          #+#    #+#             */
/*   Updated: 2023/01/11 15:30:21 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_game(t_game *game)
{
	int	i;

	i = -1;
	while (++i < 8)
		free(game->textures[i]);
	i = -1;
	while (++i < game->map->height)
		free(game->map->mtrx[i]);
	free(game->map->mtrx);
	free(game->map);
	free(game->player);
	free(game->no);
	free(game->so);
	free(game->we);
	free(game->ea);
	free(game->floor);
	free(game->floor_rgb);
	free(game->ceiling);
	free(game->ceiling_rgb);
	return ;
}
