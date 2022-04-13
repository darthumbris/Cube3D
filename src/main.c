#include "cubed.h"

int	main(int argc, char **argv)
{
	t_data		data;

	if (argc != 2 || !parse_input(argv, &data))
	{
		write(2, "Error\n", 6);
		return (1);
	}
	init_mlx(&data);
	mlx_draw_texture(data.mlx.fg, data.mlx.no_texture, 64, 64);
	mlx_image_to_window(data.mlx.mlx_handle, data.mlx.bg, 0, 0);
	mlx_image_to_window(data.mlx.mlx_handle, data.mlx.fg, 0, 0);
	mlx_loop(data.mlx.mlx_handle);
	return (0);
}
