/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 18:40:12 by kdoulyaz          #+#    #+#             */
/*   Updated: 2023/01/11 20:44:32 by mac              ###   ########.fr       */
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
				draw_rectangle(game, j * game->zoom, i * game->zoom, 0xFF0000);
			else
				draw_rectangle(game, j * game->zoom, i * game->zoom, 0xFFFFFF);
			j++;
		}
		i++;
	}
}

void	my_mlx_pixel_put_char(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (y >= HEIGHT || x >= WIDTH || y < 0 || x < 0)
		return ;
	dst = (char *)game->image.addr + (y * game->image.line_length + x * \
			(game->image.bpp / 8));
	*(unsigned int *) dst = color;
}

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

void	menu(t_game *game)
{
	void	*mlx;
	int		add;
	void	*win;

	add = 0;
	mlx = game->mlx;
	win = game->win;
	mlx_string_put(mlx, win, SCREEN_POS, add += 15, WHITE, "Controls :");
	mlx_string_put(mlx, win, SCREEN_POS,
		add += 15, WHITE, "Move [W] [A] [S] [D]");
	mlx_string_put(mlx, win, SCREEN_POS, add += 15, WHITE, "Quit [ESC]");
	mlx_string_put(mlx, win, SCREEN_POS, add += 15, WHITE, "Look [<-] [->]");
}
