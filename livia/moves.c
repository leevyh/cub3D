/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoletzk <lkoletzk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 12:32:54 by lkoletzk          #+#    #+#             */
/*   Updated: 2023/12/11 13:23:10 by lkoletzk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_moves(t_game *game, double *mov_x, double *mov_y)
{
	if (game->key.key_w == 1)
	{
		*mov_x += game->coord.dir.x / moveSpeed;
		*mov_y += game->coord.dir.y / moveSpeed;
	}
	if (game->key.key_s == 1)
	{
		*mov_x -= game->coord.dir.x / moveSpeed;
		*mov_y -= game->coord.dir.y / moveSpeed;
	}
	if (game->key.key_a == 1)
	{
		*mov_x -= game->coord.plane.x / moveSpeed;
		*mov_y -= game->coord.plane.y / moveSpeed;
	}
	if (game->key.key_d == 1)
	{
		*mov_x += game->coord.plane.x / moveSpeed;
		*mov_y += game->coord.plane.y / moveSpeed;
	}
}

void	get_move(t_game *game)
{
	double	mov_x;
	double	mov_y;

	mov_x = 0.0;
	mov_y = 0.0;
	set_moves(game, &mov_x, &mov_y);
	if (game->map.map[(int)(game->coord.pos.x + mov_x)] \
		[(int)(game->coord.pos.y)] == '0')
		game->coord.pos.x += mov_x;
	if (game->map.map[(int)(game->coord.pos.x)] \
		[(int)(game->coord.pos.y + mov_y)] == '0')
		game->coord.pos.y += mov_y;
}

