#include "cubed.h"
#include <stdio.h>
#include <sys/time.h>

void	change_camera_angle(t_data *data, int dir)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rotate_speed;
	double	cos_rotate;
	double	sin_rotate;
	struct timeval	timev;
	long			ms_before;
	long			ms_after;
	
	rotate_speed = dir * ROTATE_SPEED * data->mlx.mlx_handle->delta_time;
	cos_rotate = cos(rotate_speed);
	sin_rotate = sin(rotate_speed);
	old_dir_x = data->cam.dir.x;
	data->cam.dir.x = data->cam.dir.x * cos_rotate - data->cam.dir.y * sin_rotate;
	data->cam.dir.y = old_dir_x * sin_rotate + data->cam.dir.y * cos_rotate;
	old_plane_x = data->cam.plane.x;
	data->cam.plane.x = data->cam.plane.x * cos_rotate - data->cam.plane.y * sin_rotate;
	data->cam.plane.y = old_plane_x * sin_rotate + data->cam.plane.y * cos_rotate;
	gettimeofday(&timev, NULL);
	ms_before = timev.tv_sec * 1000 + timev.tv_usec / 1000;
	raycaster(data);
	gettimeofday(&timev, NULL);
	ms_after = timev.tv_sec * 1000 + timev.tv_usec / 1000;
	printf("\r%ld\n", ms_after - ms_before);
}

void	key_handler(struct mlx_key_data keys,void *param)
{
	t_data *data;

	data = (t_data *)param;
	if (keys.key == MLX_KEY_LEFT)
		change_camera_angle(data, 1);
	if (keys.key == MLX_KEY_RIGHT)
		change_camera_angle(data, -1);
	if (keys.key == MLX_KEY_ESCAPE)
		exit(0);
}

void	game_loop(void *v_data)
{
	t_data *data;
	

	data = (t_data *)v_data;
	
	mlx_key_hook(data->mlx.mlx_handle, key_handler, data);
	//printf("\rfps: %f", 1 / data->mlx.mlx_handle->delta_time);
}