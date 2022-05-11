/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mouse_functions.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/11 11:19:30 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/11 11:32:21 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static void	mouse_fire(t_data *data, bool *fired, int *old_x)
{
	if (mlx_is_mouse_down(data->mlx.mlx_handle, MLX_MOUSE_BUTTON_LEFT) && \
		!*fired && data->bonus)
	{
		data->mlx.weapon_anim[data->player.active_weapon].animate = true;
		if (data->player.ammo > 0 && data->player.active_weapon != KNIFE)
		{
			data->player.ammo--;
			data->update_hud = true;
		}
		check_weapon_hit(data);
		*fired = true;
	}
	if (*fired && data->player.active_weapon == MACHINEGUN)
	{
		(*old_x)++;
		if (*old_x > 7)
		{
			*old_x = 2;
			*fired = false;
		}
	}
	if (*fired && !mlx_is_mouse_down(data->mlx.mlx_handle, \
		MLX_MOUSE_BUTTON_LEFT))
		*fired = false;
}

void	mouse_handler(t_data *data)
{
	int			x;
	int			y;
	int			delta_x;
	static int	old_x = 0;
	static bool	fired = false;

	if (old_x < 2)
	{
		mlx_set_mouse_pos(data->mlx.mlx_handle, SCREEN_WIDTH / 2, \
												SCREEN_HEIGHT / 2);
		old_x++;
	}
	else
	{
		mlx_get_mouse_pos(data->mlx.mlx_handle, &x, &y);
		delta_x = x - SCREEN_WIDTH / 2;
		change_camera_angle_mouse(data, \
		delta_x * data->mlx.mlx_handle->delta_time * MOUSE_SENSITIV);
		mlx_set_mouse_pos(data->mlx.mlx_handle, SCREEN_WIDTH / 2, \
												SCREEN_HEIGHT / 2);
	}
	mouse_fire(data, &fired, &old_x);
}
