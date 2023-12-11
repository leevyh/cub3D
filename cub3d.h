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

# include "libft/libft.h"
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
# include "minilibx-linux/mlx.h"

# define SIZE_IMG 64

# define NO "srcs/Wall.xpm"
# define SO "srcs/Wall.xpm"
# define WE "srcs/Wall.xpm"
# define EA "srcs/Wall.xpm"
// # define F_texture "sprites/background/mid1.xpm"
// # define C_texture "sprites/background/obst1.xpm"


typedef enum s_keycode
{
	ESC = 65307,
	EXIT = 17,
	// QUIT = 113,
	W = 119,
	S = 115,
	A = 97,
	D = 100,
	UP = 65362,
	DOWN = 65364,
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
	t_img	F_texture;
	t_img	C_texture;
}	t_map;

typedef struct s_game {
	void	*mlx;
	void	*win;

	t_key	key;
	t_map	map;

	int		start;
	int		exit;
	t_point	p_perso;
	int		end_game;
	t_img	img;
}	t_game;

/* Utils */
void	free_map(t_game *game);
int		close_window(t_game *game, int key);
void	set_on_null(t_game *game);
void	error_message(char *str, t_game *game);

/* Map checker */


/* Map solvability */
void	flood_fill(t_game *game);

/* Player's moves */
int		key_map(int key, t_game *game);

/* Graphismes */


#endif
