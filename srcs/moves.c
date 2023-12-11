/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoletzk <lkoletzk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:24:28 by lkoletzk          #+#    #+#             */
/*   Updated: 2023/11/29 16:24:28 by lkoletzk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
Takes the event and transforms it into movement
*/
void	set_moves(t_game *game, double *x, double *y)
{
	if (game->key.key_w == 1)
	{
		*x += game->coord.dir.x / MOV_SPEED;
		*y += game->coord.dir.y / MOV_SPEED;
	}
	if (game->key.key_s == 1)
	{
		*x -= game->coord.dir.x / MOV_SPEED;
		*y -= game->coord.dir.y / MOV_SPEED;
	}
	if (game->key.key_a == 1)
	{
		*x -= game->coord.plane.x / MOV_SPEED;
		*y -= game->coord.plane.y / MOV_SPEED;
	}
	if (game->key.key_d == 1)
	{
		*x += game->coord.plane.x / MOV_SPEED;
		*y += game->coord.plane.y / MOV_SPEED;
	}
}

/*
Checks if the movement is possible, if it is, it moves
*/
void	get_move(t_game *data)
{
	double	mov_x;
	double	mov_y;

	mov_x = 0.0;
	mov_y = 0.0;
	set_moves(data, &mov_x, &mov_y);
	if (data->map.map[(int)(data->coord.pos.x + mov_x)] \
		[(int)(data->coord.pos.y)] == '0')
		data->coord.pos.x += mov_x;
	if (data->map.map[(int)(data->coord.pos.x)] \
		[(int)(data->coord.pos.y + mov_y)] == '0')
		data->coord.pos.y += mov_y;
}