/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz <kdoulyaz@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 22:00:59 by kdoulyaz          #+#    #+#             */
/*   Updated: 2023/01/17 01:11:04 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_particule(t_game *game, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			my_mlx_pixel_put_char(game, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_player(t_game *game)
{
	draw_particule(game, game->player->pos_x * game->zoom + 0.1,
		game->player->pos_y * game->zoom + 0.1, 0x000000);
}

void	draw_map(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map->height)
	{
		j = 0;
		while (j < (int)ft_strlene(game->map->mtrx[i]))
		{
			if (game->map->mtrx[i][j] == '1')
				draw_rectangle(game, j * game->zoom, i * game->zoom, 0xA9A9A9);
			else
				draw_rectangle(game, j * game->zoom, i * game->zoom, 0xFFFFFF);
			j++;
		}
		i++;
	}
}

void	draw(t_game *game)
{
	int	y;
	int	x;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			game->image.addr[y * WIDTH + x] = game->buf[y][x];
		}
	}
	mlx_put_image_to_window(game->mlx, game->win, game->image.image, 0, 0);
}

void	draw_rectangle(t_game *game, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->zoom)
	{
		j = 0;
		while (j < game->zoom)
		{
			my_mlx_pixel_put_char(game, x + j, y + i, color);
			j++;
		}
		i++;
	}
}
