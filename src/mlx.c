/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz <kdoulyaz@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 15:31:52 by kdoulyaz          #+#    #+#             */
/*   Updated: 2023/01/11 23:29:18 by kdoulyaz         ###   ########.fr       */
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
	mlx_mouse_hook(game->win, mouse_hooks, game);
	mlx_hook(game->win, 2, (1L << 0), key_hook_pressed, game);
	mlx_hook(game->win, 3, (1L << 1), key_hook_released, game);
	mlx_hook(game->win, 17, (1L << 17), clean_close, game);
	mlx_loop(game->mlx);
	return (0);
}
