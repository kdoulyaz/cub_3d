/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz <kdoulyaz@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 19:08:56 by kdoulyaz          #+#    #+#             */
/*   Updated: 2023/01/09 19:13:19 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_exit(t_game *game)
{
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
	(write(2, "Error: Invalid configuration\n", 29), exit(EXIT_FAILURE));
}
