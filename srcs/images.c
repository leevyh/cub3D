/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoletzk <lkoletzk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:48:01 by lkoletzk          #+#    #+#             */
/*   Updated: 2023/11/30 17:07:55 by lkoletzk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	put_map(t_game *game, int line, int col);
static void	put_player(t_game *game, int line, int col, int key);

void	load_images(t_game *game)
{
	game->map.NO_texture.img = mlx_xpm_file_to_image(game->mlx,
			NO, &(game->map.width), &(game->map.height));
	game->map.SO_texture.img = mlx_xpm_file_to_image(game->mlx,
			SO, &(game->map.width), &(game->map.height));
	game->map.WE_texture.img = mlx_xpm_file_to_image(game->mlx,
			WE, &(game->map.width), &(game->map.height));
	game->map.EA_texture.img = mlx_xpm_file_to_image(game->mlx,
			EA, &(game->map.width), &(game->map.height));

	// game->map.F_texture.img = mlx_xpm_file_to_image(game->mlx,
	// 		F_texture, &(game->map.width), &(game->map.height));
	// game->map.C_texture.img = mlx_xpm_file_to_image(game->mlx,
	// 		C_texture, &(game->map.width), &(game->map.height));
}

int	put_images(t_game *game, int key)
{
	int	line;
	int	col;

	line = -1;
	while (game->map[++line])
	{
		col = -1;
		while (game->map[line][++col])
		{
			if (game->map[line][col] == '1' || game->map[line][col] == '0'
				|| game->map[line][col] == 'C' || game->map[line][col] == 'E')
				put_map(game, line, col);
			if (game->map[line][col] == 'P')
				put_player(game, line, col, key);
		}
	}
	return (1);
}

static void	put_map(t_game *game, int line, int col)
{
	if (game->map[line][col] == '1')
		mlx_put_image_to_window(game->mlx, game->win,
			game->xpm.img_wall, col * SIZE_IMG, line * SIZE_IMG);
	if (game->map[line][col] == '0')
		mlx_put_image_to_window(game->mlx, game->win,
			game->xpm.img_path, col * SIZE_IMG, line * SIZE_IMG);
	if (game->map[line][col] == 'C')
		mlx_put_image_to_window(game->mlx, game->win,
			game->xpm.img_colect, col * SIZE_IMG, line * SIZE_IMG);
	if (game->map[line][col] == 'E')
	{
		if (game->colectible == 0)
			mlx_put_image_to_window(game->mlx, game->win,
				game->xpm.img_exit_open, col * SIZE_IMG, line * SIZE_IMG);
		else
			mlx_put_image_to_window(game->mlx, game->win,
				game->xpm.img_exit_close, col * SIZE_IMG, line * SIZE_IMG);
	}
}

static void	put_player(t_game *game, int line, int col, int key)
{
	if (key == A || key == LEFT)
		mlx_put_image_to_window(game->mlx, game->win,
			game->xpm.img_player_left, col * SIZE_IMG, line * SIZE_IMG);
	else if (key == D || key == RIGHT)
		mlx_put_image_to_window(game->mlx, game->win,
			game->xpm.img_player_right, col * SIZE_IMG, line * SIZE_IMG);
	else if (key == W || key == UP || key == S || key == DOWN)
		mlx_put_image_to_window(game->mlx, game->win,
			game->xpm.img_player_right, col * SIZE_IMG, line * SIZE_IMG);
}
