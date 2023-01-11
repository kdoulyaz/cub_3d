/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz <kdoulyaz@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 21:52:54 by kdoulyaz          #+#    #+#             */
/*   Updated: 2023/01/11 21:57:21 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	load_img(t_game *game, int *buff, char *path, t_image *img)
{
	int	y;
	int	x;

	y = -1;
	img->image = mlx_xpm_file_to_image(game->mlx, path, &img->width, \
		&img->height);
	if (!img->image)
		(write(2, "Error: Invalid texture path\n", 28), exit(EXIT_FAILURE));
	img->addr = (int *)mlx_get_data_addr(img->image, &img->bpp, \
		&img->line_length, &img->endian);
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
