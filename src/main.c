/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/06 13:18:02 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/04/06 13:32:10 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/MLX42/include/MLX42/MLX42.h"
#include <stdlib.h>

int	main(int argc, char **argv)
{
	mlx_t		*mlx;
	mlx_image_t	*bg;

	(void)argc;
	(void)argv;
	mlx = mlx_init(500, 500, "cube3D", false);
	bg = mlx_new_image(mlx, 500, 500);
	mlx_image_to_window(mlx, bg, 0, 0);
	mlx_loop(mlx);
	while (1)
		NULL;
	return (0);
}
