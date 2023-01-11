/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz <kdoulyaz@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 18:52:53 by kdoulyaz          #+#    #+#             */
/*   Updated: 2023/01/10 18:59:56 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	previous_length(t_map *map, int i, int j)
{
	int	k;

	k = 0;
	while (map->mtrx[i - 1][k])
		k++;
	if (k < j)
		return (0);
	return (1);
}

int	next_length(t_map *map, int i, int j)
{
	int	k;

	k = 0;
	while (map->mtrx[i + 1][k])
		k++;
	if (k < j)
		return (0);
	return (1);
}

void	check_box(t_map *map, int p, int n, int i)
{
	int	j;

	if (map->mtrx[i][0] == '0')
		print_err("Map not closed");
	j = 0;
	while (j < map->width && map->mtrx[i][j])
	{
		if (map->mtrx[i][j] == '0' && !map->mtrx[i][j + 1])
			print_err("Map not closed");
		if (map->mtrx[i][j] == '0')
		{
			p = previous_length(map, i, j);
			n = next_length(map, i, j);
			if (!p || !n || map->mtrx[i - 1][j] == ' '
				|| map->mtrx[i + 1][j] == ' ' || map->mtrx[i][j - 1]
				== ' ' || map->mtrx[i][j + 1] == ' ' || !map->mtrx[i - 1][j]
				|| !map->mtrx[i + 1][j] || !map->mtrx[i][j - 1]
				|| !map->mtrx[i][j + 1])
				print_err("Map not closed");
		}
		j++;
	}
}

void	is_corr_map(t_game *game)
{
	t_map	*map;
	int		i;
	int		p;
	int		n;

	map = game->map;
	i = -1;
	p = -1;
	n = -1;
	while (++i < map->height)
		check_box(map, p, n, i);
}
