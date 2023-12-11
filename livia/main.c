/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoletzk <lkoletzk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:50:45 by lkoletzk          #+#    #+#             */
/*   Updated: 2023/11/29 15:50:45 by lkoletzk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static void	first_part(int argc, char **argv, t_game *game)
// {
// 	(void)argc;
// 	(void)argv;
// 	game->map.map = 0;
// 	set_on_null(game);
// 	// check_filename(argc, argv[1], game);
// 	// create_map(argv[1], game);
// 	// check_map_stucture(game->map, game);
// 	// flood_fill(game);
// }

static void	ft_minilibx(t_game *game)
{
	game->mlx = mlx_init();
	if (game->mlx == NULL)
		return ;
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");	//game->map.width * SIZE_IMG, game->map.height * SIZE_IMG
	if (game->win == NULL)
	{
		free(game->win);
		return ;
	}
	start_game(game);
	
 	// game->img.img = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);		// game->map.width * SIZE_IMG, game->map.height * SIZE_IMG
	// game->img.addr = mlx_get_data_addr(game->img.img,
	// 		&game->img.bits_per_pixel, &game->img.line_length,
	// 		&game->img.endian);
	// load_images(game);
	// put_images(game, RIGHT);
	// mlx_hook(game->win, KeyPress, 1L << 0, &key_map, game);
	// mlx_hook(game->win, EXIT, 0, &close_window, game);
	// mlx_loop_hook(game->mlx, put_images, game);
	
    // mlx_loop(game->mlx);
	mlx_destroy_display(game->mlx);
    free(game->mlx);
}

int	main(int argc, char **argv)
{
	t_game	game;

	(void)argc;
	(void)argv;
	// first_part(argc, argv, &game);

	ft_minilibx(&game);
	return (0);
}


// int	handle_no_event(void *data)
// {
// 	(void)data;
//     /* This function needs to exist, but it is useless for the moment */
//     return (0);
// }

// int	handle_input(int keysym, t_data *data)
// {
//     if (keysym == XK_Escape)
//         mlx_destroy_window(data->mlx_ptr, data->win_ptr);
//     return (0);
// }

// int	handle_keypress(int keysym, t_data *data)
// {
//     if (keysym == XK_Escape)
//         mlx_destroy_window(data->mlx_ptr, data->win_ptr);

//     printf("Keypress: %d\n", keysym);
//     return (0);
// }

// int	handle_keyrelease(int keysym, void *data)
// {
// 	(void)data;
//     printf("Keyrelease: %d\n", keysym);
//     return (0);
// }

// int	main(void)
// {
//     t_data	data;

//     data.mlx_ptr = mlx_init();
//     // if (data.mlx_ptr == NULL)
//     //     return (MLX_ERROR);
//     data.win_ptr = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "My first window!");
//     // if (data.win_ptr == NULL)
//     // {
//     //     free(data.win_ptr);
//     //     return (MLX_ERROR);
//     // }

//     /* Setup hooks */ 
//     mlx_loop_hook(data.mlx_ptr, &handle_no_event, &data);
//     mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data); /* ADDED */
//     mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &handle_keyrelease, &data); /* CHANGED */

//     mlx_loop(data.mlx_ptr);

//     /* we will exit the loop if there's no window left, and execute this code */
//     mlx_destroy_display(data.mlx_ptr);
//     free(data.mlx_ptr);
// }
