/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz <kdoulyaz@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 22:01:42 by kdoulyaz          #+#    #+#             */
/*   Updated: 2023/01/09 16:44:27 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

	// printf("----------%lu---------\n", strlen("Starting mlx ...\n"));
	// return (0);

int	main(int ac, char **av)
{
	t_game	*game;

	if (ac == 2)
	{
		game = (t_game *)malloc(sizeof(t_game));
		game->map = (t_map *)malloc(sizeof(t_map));
		init_game(game);
		init_textures(game);
		write(2, "Parsing map...\n", 15);
		if (incorrect_file(av[1]))
			(write(2, "Error : invalid configuration file\n", 35), \
				exit(EXIT_FAILURE));
		if (!parse_file(av[1], game))
		{
			// free_game(game);
			(write(2, "Error : invalid configuration file\n", 35), \
				exit(EXIT_FAILURE));
		}
		write(1, "Starting mlx ...\n", 17);
		// if (mlx_exec(game))
		// 	return (EXIT_FAILURE);
		write(1, "Quit...\n", 8);
		return (0);
	}
}
