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
	data->cam.dir.x = data->cam.dir.x * cos_rotate - data->cam.dir.y * sin_rotate;
	data->cam.dir.y = old_dir_x * sin_rotate + data->cam.dir.y * cos_rotate;
	old_plane_x = data->cam.plane.x;
	data->cam.plane.x = data->cam.plane.x * cos_rotate - data->cam.plane.y * sin_rotate;
	data->cam.plane.y = old_plane_x * sin_rotate + data->cam.plane.y * cos_rotate;
	raycaster(data);
}

void	move_camera_pos(t_data *data, int dir, bool strafe)
{
	const double	move_speed = dir * MOVE_SPEED * data->mlx.mlx_handle->delta_time;
	const double	temp_dir_x = data->cam.dir.x * move_speed;
	const double	temp_dir_y = data->cam.dir.y * move_speed;
	//TODO:its possible to jam yourself stuck inside a wall
	if (data->level.map[(int)(data->cam.pos.y + temp_dir_y)][(int)(data->cam.pos.x + temp_dir_x)] == '1' ||
		data->level.map[(int)(data->cam.pos.y + temp_dir_x)][(int)(data->cam.pos.x - temp_dir_y)] == '1')
		return ;
	if (!strafe)
	{
		data->cam.pos.x += data->cam.dir.x * move_speed;
		data->cam.pos.y += data->cam.dir.y * move_speed;
	}
	else if (strafe)
	{
		data->cam.pos.x -= data->cam.dir.y * move_speed;
		data->cam.pos.y += data->cam.dir.x * move_speed;
	}
	raycaster(data);
}

void	key_handler(struct mlx_key_data keys, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keys.key == MLX_KEY_ESCAPE && keys.action != MLX_RELEASE)
		mlx_close_window(data->mlx.mlx_handle);
	if (keys.key == MLX_KEY_LEFT && keys.action != MLX_RELEASE)
		change_camera_angle(data, -1);
	if (keys.key == MLX_KEY_RIGHT && keys.action != MLX_RELEASE)
		change_camera_angle(data, +1);
	if (keys.key == MLX_KEY_W && keys.action != MLX_RELEASE)
		move_camera_pos(data, +1, false);
	if (keys.key == MLX_KEY_S && keys.action != MLX_RELEASE)
		move_camera_pos(data, -1, false);
	if (keys.key == MLX_KEY_A && keys.action != MLX_RELEASE)
		move_camera_pos(data, -1, true);
	if (keys.key == MLX_KEY_D && keys.action != MLX_RELEASE)
		move_camera_pos(data, +1, true);
}


void	game_loop(void *v_data)
{
	t_data	*data;

	data = (t_data *)v_data;
}
