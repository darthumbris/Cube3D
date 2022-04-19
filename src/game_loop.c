#include "cubed.h"

void	change_camera_angle(t_data *data, double dir)
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
	data->cam.dir.x = data->cam.dir.x * \
		cos_rotate - data->cam.dir.y * sin_rotate;
	data->cam.dir.y = old_dir_x * sin_rotate + data->cam.dir.y * cos_rotate;
	old_plane_x = data->cam.plane.x;
	data->cam.plane.x = data->cam.plane.x * \
		cos_rotate - data->cam.plane.y * sin_rotate;
	data->cam.plane.y = old_plane_x * \
		sin_rotate + data->cam.plane.y * cos_rotate;
}

void	move_camera_pos(t_data *data, int dir, bool strafe)
{
	const double	move_speed = dir * MOVE_SPEED * data->mlx.mlx_handle->delta_time;
	const double	temp_dir_x = data->cam.dir.x * move_speed;
	const double	temp_dir_y = data->cam.dir.y * move_speed;

	if (!strafe && data->level.map[(int)(data->cam.pos.y + temp_dir_y)] \
		[(int)(data->cam.pos.x + temp_dir_x)] == '0')
	{
		data->cam.pos.x += temp_dir_x;
		data->cam.pos.y += temp_dir_y;
	}
	else if (strafe && data->level.map[(int)(data->cam.pos.y + temp_dir_x)] \
		[(int)(data->cam.pos.x - temp_dir_y)] == '0')
	{
		data->cam.pos.x -= temp_dir_y;
		data->cam.pos.y += temp_dir_x;
	}
	else
		return ;
}

void	key_handler(struct mlx_key_data keys, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keys.key == MLX_KEY_ESCAPE && keys.action != MLX_RELEASE)
		mlx_close_window(data->mlx.mlx_handle);
}

void	game_loop(void *v_data)
{
	t_data	*data;

	data = (t_data *)v_data;
	if (mlx_is_key_down(data->mlx.mlx_handle, MLX_KEY_LEFT))
		change_camera_angle(data, -1);
	if (mlx_is_key_down(data->mlx.mlx_handle, MLX_KEY_RIGHT))
		change_camera_angle(data, +1);
	if (mlx_is_key_down(data->mlx.mlx_handle, MLX_KEY_W))
		move_camera_pos(data, +1, false);
	if (mlx_is_key_down(data->mlx.mlx_handle, MLX_KEY_S))
		move_camera_pos(data, -1, false);
	if (mlx_is_key_down(data->mlx.mlx_handle, MLX_KEY_A))
		move_camera_pos(data, -1, true);
	if (mlx_is_key_down(data->mlx.mlx_handle, MLX_KEY_D))
		move_camera_pos(data, +1, true);
	raycaster(data);
}

//TODO: fix slowdown near walls
//TODO: mouse movement
//TODO: floor ceiling colour gradient is nice/skybox/textures