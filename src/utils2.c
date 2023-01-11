/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz <kdoulyaz@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 18:40:12 by kdoulyaz          #+#    #+#             */
/*   Updated: 2023/01/11 22:03:00 by kdoulyaz         ###   ########.fr       */
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

void	my_mlx_pixel_put_char(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (y >= HEIGHT || x >= WIDTH || y < 0 || x < 0)
		return ;
	dst = (char *)game->image.addr + (y * game->image.line_length + x * \
			(game->image.bpp / 8));
	*(unsigned int *) dst = color;
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

void	calc_screen_line(t_game *game)
{
	calculate_ray_draw(game);
	if (game->ray->side == 0)
		game->ray->wall_x = game->player->pos_y
			+ game->ray->perp_wall_dist * game->ray->ray_dir_y;
	else
		game->ray->wall_x = game->player->pos_x
			+ game->ray->perp_wall_dist * game->ray->ray_dir_x;
	game->ray->wall_x -= floor(game->ray->wall_x);
	game->ray->tex_x = (int)(game->ray->wall_x * (double)TEX_WIDTH);
	if (game->ray->side == 0 && game->ray->ray_dir_x > 0)
		game->ray->tex_x = TEX_WIDTH - game->ray->tex_x - 1;
	if (game->ray->side == 1 && game->ray->ray_dir_y < 0)
		game->ray->tex_x = TEX_WIDTH - game->ray->tex_x - 1;
	game->ray->step = 1.0 * TEX_HEIGHT / game->ray->line_height;
	game->ray->tex_pos = (game->ray->draw_start - HEIGHT / 2
			+ game->ray->line_height / 2) * game->ray->step;
}