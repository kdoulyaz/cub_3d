/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz <kdoulyaz@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 16:10:13 by kdoulyaz          #+#    #+#             */
/*   Updated: 2023/01/09 19:52:15 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	incorrect_file(char *str)
{
	int	i;
	int	fd;

	i = 0;
	if (str[i] == '.')
		return (1);
	while (str[i])
		i++;
	while (str[i] != '.')
	{
		i--;
		if (i == 0)
			return (1);
	}
	if (!strcmp(&str[i], ".cub"))
	{
		fd = open(str, O_RDONLY);
		if (fd < 0)
			return (1);
		close(fd);
		return (0);
	}
	return (1);
}

char	*retrieve_color(char *s)
{
	int		i;
	int		j;
	char	*color;

	i = 0;
	j = 0;
	while (s[i] == ' ')
		i++;
	if (s[i] < 48 || s[i] > 57)
		return (NULL);
	color = malloc(sizeof(char) * (ft_strlene(s) - i + 1));
	while (s[i])
	{
		if (s[i] == ' ')
		{
			i++;
			continue ;
		}
		color[j] = s[i];
		i++;
		j++;
	}
	color[j] = '\0';
	return (color);
}

void	set_colors(char *line, t_game *game)
{
	if (line[0] == 'F' && line[1] == ' ' && game->floor == NULL)
		game->floor = retrieve_color(line + 2);
	else if (line[0] == 'C' && line[1] == ' ' && game->ceiling == NULL)
		game->ceiling = retrieve_color(line + 2);
}

void	parse_conf(char *line, int fd, t_game *game)
{
	while (get_next_line(fd, &line) > 0)
	{
		if (!strncmp(line, "NO ", 3) && !game->no)
			game->no = ss_strdup(line + 3);
		else if (!strncmp(line, "SO ", 3) && !game->so)
			game->so = ss_strdup(line + 3);
		else if (!strncmp(line, "WE ", 3) && !game->we)
			game->we = ss_strdup(line + 3);
		else if (!strncmp(line, "EA ", 3) && !game->ea)
			game->ea = ss_strdup(line + 3);
		else if ((!strncmp(line, "F ", 2) && !game->floor) || \
			(!strncmp(line, "C ", 2) && !game->ceiling))
			set_colors(line, game);
		else if (line[0] == '\0')
		{
			free(line);
			continue ;
		}
		else if (is_valid(line))
			calcule(game, line);
		else
			print_err("Something wrong in the config file");
		free(line);
	}
	free(line);
}
