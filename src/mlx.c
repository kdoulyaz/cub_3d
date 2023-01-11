/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 15:31:52 by kdoulyaz          #+#    #+#             */
/*   Updated: 2023/01/11 19:58:10 by mac              ###   ########.fr       */
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

void	load_img(t_game *game, int *buff, char *path, t_image *img)
{
	int	y;
	int	x;

	y = -1;
	img->image = mlx_xpm_file_to_image(game->mlx, path, &img->width, &img->height);
	if (!img->image)
		(write(2, "Error: Invalid texture path\n", 28), exit(EXIT_FAILURE));
	img->addr = (int *)mlx_get_data_addr(img->image, &img->bpp, &img->line_length, &img->endian);
	while (++y < img->height)
	{
		x = -1;
		while (++x < img->width)
			buff[img->width * y + x] = img->addr[img->width * y + x];
	}
	mlx_destroy_image(game->mlx, img->image);
	return ;
}

void	load_textures(t_game *game)
{
	t_image	img;

	load_img(game, game->textures[0], game->ea, &img);
	load_img(game, game->textures[1], game->we, &img);
	load_img(game, game->textures[2], game->no, &img);
	load_img(game, game->textures[3], game->so, &img);
	return ;

}

void	raycaster(t_game *game)
{
	int	x;

	x = -1;
	while (++x < WIDTH)
	{
		init_ray(game, x);
		init_stepside_dist(game);
		dda(game);
		texture_id(game);
		calc_screen_line(game);
		put_texture(game, x);
		draw_floor(game, x);
	}
}

void	draw_frames(t_game *game)
{
	mlx_clear_window(game->mlx, game->win);
	if (game->res_buff == 1)
		init_game(game);
	raycaster(game);
	draw(game);
	if (game->keys.show_map)
	{
		draw_map(game);
		draw_player(game);
	}
	mlx_put_image_to_window(game->mlx, game->win, game->image.image, 0, 0);
	menu(game);
}

int	gam(void *game)
{
	draw_frames(game);
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
	load_textures(game);
	game->image.image = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->image.addr = (int *)mlx_get_data_addr(game->image.image,
			&game->image.bpp, &game->image.line_length, &game->image.endian);
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Cub3D");
	mlx_loop_hook(game->mlx, gam, game);
	return (0);
}
