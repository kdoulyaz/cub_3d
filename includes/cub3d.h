/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz <kdoulyaz@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 21:57:35 by kdoulyaz          #+#    #+#             */
/*   Updated: 2023/01/09 19:16:24 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include "get_next_line.h"

/*
* Game defines :
*/

# define HEIGHT 1080
# define WIDTH 1920

/*
 * TEXTURES : 
 */

# define TEX_WIDTH 64
# define TEX_HEIGHT 64

/*
 * ZOOM :
*/

# define ZOOM 15
# define ANGLE 0
# define SPEED 0.2
# define FOV 60
# define FLOOR '0'

typedef struct s_map
{
	char	view;
	char	*line;
	char	**mtrx;
	int		width;
	int		height;
}				t_map;

typedef struct s_player
{
	float	move_speed;
	float	rot_speed;
	float	pos_x;
	float	pos_y;
	float	dir_x;
	float	dir_y;
	float	plane_x;
	float	plane_y;
	double	angle;
}	t_player;

typedef struct s_rgb
{
	int			r;
	int			g;
	int			b;
}	t_rgb;

typedef struct s_ray
{
	int		tex_num;
	double	camera_x;
	double	camera_y;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	float	side_dist_x;
	float	side_dist_y;
	float	delta_dist_x;
	float	delta_dist_y;
	float	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		color;
	int		texture_id;
	float	step;
	float	tex_pos;
	int		tex_x;
	int		tex_y;
	float	wall_x;
	float	raydir_x0;
	float	raydir_y0;
	float	raydir_x1;
	float	raydir_y1;
	int		p;
	float	pos_z;
	float	row_dist;
	float	floor_step_x;
	float	floor_step_y;
	float	floor_x;
	float	floor_y;
	int		tx;
	int		ty;
	int		floor_tex;
	int		ceiling_tex;
	float	floor_x_wall;
	float	floor_y_wall;
	float	dist_wall;
	float	dist_player;
	float	curr_dist;
	float	weight;
	float	curr_floor_x;
	float	curr_floor_y;
	int		floor_tex_x;
	int		floor_tex_y;
}	t_ray;

typedef struct s_game
{
	unsigned int	buf[HEIGHT][WIDTH];
	int				**textures;
	t_map			*map;
	t_player		*player;
	t_rgb			*floor_rgb;
	t_rgb			*ceiling_rgb;
	t_ray			*ray;
	float			zoom;
	char			*floor;
	char			*ceiling;
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
}					t_game;

void	init_game(t_game *game);
void	init_textures(t_game *game);
int		incorrect_file(char *str);
void	init_params(t_game *game);
int		parse_file(char *file, t_game *game);
void	parse_conf(char *line, int fd, t_game *game);
void	print_err(char *s);
int		is_valid(char *s);
void	calcule(t_game *game, char *line);
char	*ss_strdup(char *s);
int		fill_rgb(char *str, t_rgb *rgb);
void	free_exit(t_game *game);
int		ft_atoi(char *s);

#endif