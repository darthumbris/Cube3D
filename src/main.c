#include "cubed.h"

int	main(int argc, char **argv)
{
	t_data		data;

	(void)argc;
	(void)argv;
	data.mlx.mlx_handle = mlx_init(500, 500, "cube3D", false);
	data.mlx.bg = mlx_new_image(data.mlx.mlx_handle, 500, 500);
	data.mlx.fg = mlx_new_image(data.mlx.mlx_handle, 500, 500);
	data.mlx.no_texture = mlx_load_png("assets/wood.png");
	mlx_draw_texture(data.mlx.fg, data.mlx.no_texture, 0, 0);
	mlx_image_to_window(data.mlx.mlx_handle, data.mlx.bg, 0, 0);
	mlx_image_to_window(data.mlx.mlx_handle, data.mlx.fg, 0, 0);
	mlx_loop(data.mlx.mlx_handle);
	return (0);
}
