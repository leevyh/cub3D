/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoletzk <lkoletzk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 12:42:37 by lkoletzk          #+#    #+#             */
/*   Updated: 2023/11/30 12:56:59 by lkoletzk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// static void	free_images(t_game *game)
// {
// 	mlx_destroy_image(game->mlx, game->xpm.img_player_right);
// 	mlx_destroy_image(game->mlx, game->xpm.img_player_left);
// 	mlx_destroy_image(game->mlx, game->xpm.img_path);
// 	mlx_destroy_image(game->mlx, game->xpm.img_wall);
// 	mlx_destroy_image(game->mlx, game->xpm.img_colect);
// 	mlx_destroy_image(game->mlx, game->xpm.img_exit_close);
// 	mlx_destroy_image(game->mlx, game->xpm.img_exit_open);
// 	mlx_destroy_image(game->mlx, game->img.img);
// }

void	free_map(t_game *game)
{
	int	x;

	x = -1;
	if (game->map.map)
	{
		while (game->map.map[++x])
			free(game->map.map[x]);
		free(game->map.map[x]);
		free(game->map.map);
	}
}

int	close_window(t_game *game, int key)
{
	// free_images(game);
	mlx_clear_window(game->mlx, game->win);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	free_map(game);
	if (key == A || key == LEFT || key == W || key == UP || key == S
		|| key == DOWN || key == D || key == RIGHT)
		printf("GG WP !\n");										// ft_printf
	else
		printf("See you soon !\n");								// ft_printf
	exit(0);
	return (0);
}

void	set_on_null(t_game *game)
{
	game->exit = 0;
	game->start = 0;
	game->map.width = 0;
	game->map.height = 0;
	game->end_game = 0;
}

// void	error_message(char *str, t_game *game)
// {
// 	free_map(game);
// 	ft_printf("%s", str);
// 	exit(EXIT_FAILURE);
// }