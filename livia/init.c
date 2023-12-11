/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoletzk <lkoletzk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 11:26:05 by lkoletzk          #+#    #+#             */
/*   Updated: 2023/12/11 11:41:24 by lkoletzk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*Initializes the MLX pointer*/
int	init_mlx_ptr(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (1);
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "Our cub3D!");
	if (!game->win)
	{
		mlx_destroy_display(game->mlx);
		return (1);
	}
	if (init_mlx_img_addr(game))
		return (1);
	return (0);
}

/*Initializes the MLX main window where we print all*/
int	init_mlx_img_addr(t_game *game)
{
	game->img.img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game->img.img)
	{
		mlx_destroy_window(game->mlx, game->win);
		mlx_destroy_display(game->mlx);
		return (1);
	}
	add_img_to_tab(game, game->img.img);
	game->img.addr = mlx_get_game_addr(game->img.img,
			&game->img.bits_per_pixel,
			&game->img.line_length,
			&game->img.endian);
	if (!game->img.addr)
	{
		mlx_destroy_image(game->mlx, game->img.img);
		mlx_destroy_window(game->mlx, game->win);
		mlx_destroy_display(game->mlx);
		return (1);
	}
	return (0);
}

/*Initializes the images, adding them to the tab to destroy when we finish*/
int	init_texture(t_game *game, t_img *texture, char *path)
{
	texture->img = mlx_xpm_file_to_image(game->mlx,
			path, &(texture->width), &(texture->height));
	if (!texture->img)
		return (1);
	add_img_to_tab(game, texture->img);
	texture->addr = mlx_get_game_addr(texture->img, &(texture->bits_per_pixel),
			&(texture->line_length), &(texture->endian));
	if (!texture->addr)
		return (1);
	game->map.n_textures++;
	return (0);
}

/*Initializes the colors of the floor and ceiling*/
int	init_fc_color(t_game *game, int *color, char *path)
{
	int			r;
	int			g;
	int			b;
	char		**c_tab;

	if (!path || !path[0])
		return (1);
	c_tab = ft_split(path, ',');
	if (!c_tab)
		return (1);
	if (get_colors(&r, &g, &b, c_tab))
	{
		ft_free_matrix((void **)c_tab);
		return (1);
	}
	*color = r << 16 | g << 8 | b;
	game->map.NO_texture++;
	ft_free_matrix((void **)c_tab);
	return (0);
}

/*Divides the color given in the parsing into R G B values*/
int	get_colors(int *r, int *g, int *b, char **color_tab)
{
	int	i;

	i = 0;
	if (!color_tab || !color_tab[0])
		return (1);
	while (color_tab[i])
		i++;
	if (i != 3)
		return (1);
	*r = ft_atoi_rgb(color_tab[0]);
	*g = ft_atoi_rgb(color_tab[1]);
	*b = ft_atoi_rgb(color_tab[2]);
	if (*r == -1 || *g == -1 || *b == -1)
		return (1);
	return (0);
}
