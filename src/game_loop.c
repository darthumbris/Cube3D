#include "cubed.h"



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

void	mouse_events(mouse_key_t button, action_t action, modifier_key_t mods, void *param)
{
	(void)action;
	(void)mods;
	(void)param;
	(void)button;
	//if (button == MLX_MOUSE_BUTTON_LEFT)
	//	write(1, "mleft\n", 6);
}

void	cursor_movement(double xpos, double ypos, void *param)
{	
	t_data			*data;

	data = (t_data *)param;
	printf("%f-%f\n", xpos, ypos);
}

void	game_loop(void *v_data)
{
	t_data	*data;

	data = (t_data *)v_data;
}

//TODO: fix slowdown near walls
//TODO: mouse movement
//TODO: floor ceiling colour gradient is nice