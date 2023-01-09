/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz <kdoulyaz@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 19:00:57 by kdoulyaz          #+#    #+#             */
/*   Updated: 2023/01/09 19:15:04 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	fill_r(char *str, t_rgb *rgb, int i)
{
	char	*r;
	int		j;

	j = 0;
	r = malloc(sizeof(char) * (ft_strlene(str) + 1));
	while (str[i] != ',')
	{
		if (str[i] < 48 || str[i] > 57 || !str[i])
		{
			free(r);
			return (0);
		}
		r[j] = str[i];
		i++;
		j++;
	}
	if (j == 0)
	{
		free(r);
		return (0);
	}
	r[j] = '\0';
	rgb->r = ft_atoi(r);
	free(r);
	return (i);
}

int	fill_g(char *str, t_rgb *rgb, int i)
{
	char	*g;
	int		j;

	j = 0;
	g = malloc(sizeof(char) * (ft_strlene(str) + 1));
	while (str[i] != ',')
	{
		if (str[i] < 48 || str[i] > 57)
		{
			free(g);
			return (0);
		}
		g[j] = str[i];
		i++;
		j++;
	}
	if (j == 0)
	{
		free(g);
		return (0);
	}
	g[j] = '\0';
	rgb->g = ft_atoi(g);
	free(g);
	return (i);
}

int	fill_b(char *str, t_rgb *rgb, int i)
{
	char	*b;
	int		j;

	j = 0;
	b = malloc(sizeof(char) * (ft_strlene(str) + 1));
	while (str[i] != '\0')
	{
		if (str[i] < 48 || str[i] > 57)
		{
			free(b);
			return (0);
		}
		b[j] = str[i];
		i++;
		j++;
	}
	if (j == 0)
	{
		free(b);
		return (0);
	}
	b[j] = 0;
	rgb->b = ft_atoi(b);
	free(b);
	return (i);
}

int	fill_rgb(char *str, t_rgb *rgb)
{
	int	i;
	int	pointer;
	int	count_commas;

	i = -1;
	count_commas = 0;
	while (str[++i])
		count_commas += (str[i] == ',');
	if (count_commas > 2)
		return (0);
	i = 0;
	pointer = fill_r(str, rgb, i);
	if (pointer == 0)
		return (0);
	i = pointer + 1;
	pointer = fill_g(str, rgb, i);
	i = pointer + 1;
	pointer = fill_b(str, rgb, i);
	if (rgb->r < 0 || rgb->r > 255 || rgb->g < 0
		|| rgb->g > 255 || rgb->b < 0 || rgb->b > 255)
		return (0);
	return (1);
}
