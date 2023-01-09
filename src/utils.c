/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz <kdoulyaz@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 17:06:09 by kdoulyaz          #+#    #+#             */
/*   Updated: 2023/01/09 19:47:15 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	print_err(char *s)
{
	write(2, "Error:", 7);
	write(2, s, ft_strlene(s));
	write(2, "\n", 1);
	exit(0);
}

int	is_valid(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] != '1' && s[i] != '0' && s[i] != ' ' && s[i] != '\n'
			&& s[i] != 'N' && s[i] != 'S' && s[i] != 'E'
			&& s[i] != 'W' && s[i] != '\0')
			return (0);
		i++;
	}
	return (1);
}

void	calcule(t_game *game, char *line)
{
	if ((int)ft_strlene(line) > game->map->width)
	{
		game->map->width = (int)ft_strlene(line);
	}
	game->map->height++;
}

char	*ss_strdup(char *s)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	while (s[i] == ' ')
		i++;
	str = malloc(sizeof(char) * (ft_strlene(s) - i + 1));
	while (s[i])
	{
		str[j] = s[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return (str);
}

int	ft_atoi(char *s)
{
	int	i;
	int	neg;
	int	res;

	i = 0;
	neg = 1;
	res = 0;
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n' || s[i] == '\v'
		|| s[i] == '\f' || s[i] == '\r')
		i++;
	if (s[i] == '-')
	{
		neg = -1;
		i++;
	}
	else if (s[i] == '+')
		i++;
	while (s[i] >= '0' && s[i] <= '9')
	{
		res = res * 10 + (s[i] - '0');
		i++;
	}
	return (res * neg);
}
