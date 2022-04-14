#include "cubed.h"
#include <stdio.h>

void	change_camera_angle(t_data *data, int dir)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rotate_speed;
	double	cos_rotate;
	double	sin_rotate;

	rotate_speed = dir * ROTATE_SPEED * data->mlx.mlx_handle->delta_time;
	cos_rotate = cos(rotate_speed);
	sin_rotate = sin(rotate_speed);
	old_dir_x = data->cam.dir.x;
	data->cam.dir.x = data->cam.dir.x * cos_rotate - data->cam.dir.y * sin_rotate;
	data->cam.dir.y = old_dir_x * sin_rotate + data->cam.dir.y * cos_rotate;
	old_plane_x = data->cam.plane.x;
	data->cam.plane.x = data->cam.plane.x * cos_rotate - data->cam.plane.y * sin_rotate;
	data->cam.plane.y = old_plane_x * sin_rotate + data->cam.plane.y * cos_rotate;
	raycaster(data);
}

void	key_handler(struct mlx_key_data keys,void *param)
{
	t_data *data;

	data = (t_data *)param;
	(void)keys;
	if (mlx_is_key_down(data->mlx.mlx_handle, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx.mlx_handle); //free shit afterwards
	if (mlx_is_key_down(data->mlx.mlx_handle, MLX_KEY_LEFT))
		change_camera_angle(data, 1);
	if (mlx_is_key_down(data->mlx.mlx_handle, MLX_KEY_RIGHT))
		change_camera_angle(data, -1);
	if (mlx_is_key_down(data->mlx.mlx_handle, MLX_KEY_W))
		;//change player pos
	if (mlx_is_key_down(data->mlx.mlx_handle, MLX_KEY_S))
		;//change player pos
	if (mlx_is_key_down(data->mlx.mlx_handle, MLX_KEY_A))
		;//change player pos
	if (mlx_is_key_down(data->mlx.mlx_handle, MLX_KEY_D))
		;//change player pos
}


void	game_loop(void *v_data)
{
	t_data	*data;

	data = (t_data *)v_data;
	mlx_key_hook(data->mlx.mlx_handle, key_handler, data);
}
