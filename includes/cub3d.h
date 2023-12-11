/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoletzk <lkoletzk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:48:59 by lkoletzk          #+#    #+#             */
/*   Updated: 2023/11/29 15:48:59 by lkoletzk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <math.h>
# include <limits.h>

# include <X11/X.h>
# include <X11/keysym.h>
# include "../mlx/mlx.h"

# define SIZE_IMG 64
# define WIN_WIDTH 600
# define WIN_HEIGHT 300
# define moveSpeed 100
# define rotSpeed 50

/* A METTRE DANS .CUB*/
# define NO "Wall.xpm"
# define SO "Wall.xpm"
# define WE "Wall.xpm"
# define EA "Wall.xpm"
// # define F_texture "sprites/background/mid1.xpm"
// # define C_texture "sprites/background/obst1.xpm"


typedef enum s_keycode
{
	ESC = 65307,
	EXIT = 17,
	W = 119,
	S = 115,
	A = 97,
	D = 100,
	RIGHT = 65363,
	LEFT = 65361
}	t_keycode;

typedef struct s_key
{
	int	key_w;
	int	key_a;
	int	key_s;
	int	key_d;
	int	right;
	int	left;
}	t_key;

typedef struct s_point {
	int	x;
	int	y;
}	t_point;

typedef struct s_range
{
	int	start;
	int	end;
}	t_range;

typedef struct s_coord
{
	int	x;
	int	y;
}	t_coord;

typedef struct s_ray
{
	t_point	pos;
	t_point	dir;
	t_point	screen_dir;
	t_point	plane;
	t_point	raydir;
	t_point	sidedist;
	t_point	deltadist;
	t_coord		map;
	t_coord		step;
	t_range		draw;
	double		camera_x;
	double		perp_w_dist;
	int			hit;
	int			side;
	int			line_height;
	int			color;
}	t_ray;

typedef struct s_img {
	void	*img;
	void	*addr;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	t_point	size;
}	t_img;

typedef struct s_map {
	char	**map;
	int		width;
	int		height;
	t_img	NO_texture;
	t_img	SO_texture;
	t_img	WE_texture;
	t_img	EA_texture;
	// t_img	F_texture;
	// t_img	C_texture;
	int		F_color;
	int		C_color;
}	t_map;

typedef struct s_game {
	void	*mlx;
	void	*win;
	t_key	key;
	t_map	map;
	t_ray	coord;

	int		start;
	int		exit;
	t_point	p_perso;
	int		end_game;
	t_img	img;
}	t_game;

/* Utils */
void	free_map(t_game *game);
void	set_on_null(t_game *game);
void	error_message(char *str, t_game *game);

void	start_game(t_game *data);
int		close_window(t_game *game, int key);
int		handle_keypress(int keysym, t_game *data);
int		handle_keyrelease(int keysym, t_game *data);

int	update_game(t_game *game);
void	ft_display(t_game *data);
void	render_background(t_game *data);
void	ft_img_pix_put(t_img *img, int x, int y, int color);

void	set_moves(t_game *game, double *mov_x, double *mov_y);
void	get_move(t_game *game);


/* Map checker */


/* Map solvability */
void	flood_fill(t_game *game);

/* Player's moves */
void	set_moves(t_game *game, double *mov_x, double *mov_y);

/* Graphismes */


#endif
