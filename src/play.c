/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoletzk <lkoletzk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 11:47:12 by lkoletzk          #+#    #+#             */
/*   Updated: 2023/12/11 15:22:57 by lkoletzk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	start_game(t_game *game)
{
	mlx_hook(game->win, EXIT, 0, &close_window, game);
	mlx_hook(game->win, 2, 1L << 0, &handle_keypress, game);
	mlx_hook(game->win, 3, 1L << 1, &handle_keyrelease, game);
	mlx_loop_hook(game->mlx, update_game, game);
	mlx_loop(game->mlx);
}

int	update_game(t_game *game)
{
	// get_move(game);
	ft_display(game);
	return (0);
}

void	ft_display(t_game *game)
{
	// render_background(game);
	// ft_raycasting(game);
	game->img.img = mlx_xpm_file_to_image(game->mlx, NO, &(game->map.width), &(game->map.height));
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);

}

/*
Prints ground and sky color
*/
void	render_background(t_game *data)
{
	int	height;
	int	width;

	height = 0;
	while (height < WIN_HEIGHT)
	{
		width = 0;
		while (width < WIN_WIDTH)
		{
			if (height < WIN_HEIGHT / 2)
				ft_img_pix_put(&data->img, width, height, data->map.C_color);
			else
				ft_img_pix_put(&data->img, width, height, data->map.F_color);
			width++;
		}
		height++;
	}
}

void	ft_img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->addr + ((y * img->line_length) + (x * (img->bits_per_pixel / 8)));
	*(int *)pixel = color;
}


int	handle_keypress(int keysym, t_game *game)
{
	// printf("Keypress: %d\n", keysym);
	if (keysym == EXIT || keysym == ESC)
		close_window(game, XK_Escape);
	if (keysym == W)
		game->key.key_w = 1;
	if (keysym == A)
		game->key.key_a = 1;
	if (keysym == S)
		game->key.key_s = 1;
	if (keysym == D)
		game->key.key_d = 1;
	if (keysym == RIGHT)
		game->key.right = 1;
	if (keysym == LEFT)
		game->key.left = 1;
	return (0);
}

int	handle_keyrelease(int keysym, t_game *game)
{
	// printf("Keyrelease: %d\n", keysym);
	if (keysym == W)
		game->key.key_w = 0;
	if (keysym == A)
		game->key.key_a = 0;
	if (keysym == S)
		game->key.key_s = 0;
	if (keysym == D)
		game->key.key_d = 0;
	if (keysym == RIGHT)
		game->key.right = 0;
	if (keysym == LEFT)
		game->key.left = 0;
	return (0);
}

