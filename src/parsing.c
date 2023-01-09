/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz <kdoulyaz@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 23:06:10 by kdoulyaz          #+#    #+#             */
/*   Updated: 2023/01/09 19:36:54 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	file_exist(t_game *game)
{
	int	fd;

	fd = open(game->no, O_RDONLY);
	if (fd < 0)
	{
		printf("-%s-\n", game->no);
		return (0);
	}
	close(fd);
	fd = open(game->so, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	fd = open(game->we, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	fd = open(game->ea, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}


int	conf_valid(t_game *game)
{
	if (game->no == NULL || game->so == NULL || game->we == NULL
		|| game->ea == NULL || game->floor == NULL || game->ceiling == NULL)
		return (0);
	if (!file_exist(game))
		return (0);
	if (!fill_rgb(game->floor, game->floor_rgb) || \
		!fill_rgb(game->ceiling, game->ceiling_rgb))
		return (0);
	return (1);
}

int	parse_file(char *file, t_game *game)
{
	int		fd;
	char	*str;

	str = NULL;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	init_params(game);
	parse_conf(str, fd, game);
	close(fd);
	if (!conf_valid(game))
		free_exit(game);
	fd = open(file, O_RDONLY);
	game->map->mtrx = malloc(sizeof(char *) * (game->map->height + 1));
	// if (!parse_map(str, fd, game))
	// 	return (0);
	// is_corr_map(game);
	// set_player(game);
	// get_player(game);
	// free(str);
	// close(fd);
	return (1);
}
