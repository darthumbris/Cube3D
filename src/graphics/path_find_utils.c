/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path_find_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/10 15:48:51 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/05/13 17:04:08 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

bool	door_check(t_data *data, t_vector_int g_pos)
{
	return (is_door_tile(data->level.map[g_pos.y][g_pos.x]) && \
			!is_door_open(data, g_pos.y, g_pos.x));
}

void	set_val(t_vector_int *delta, t_vector_int *sign, \
				t_vector_int pc_pos, t_vector_int g_pos)
{
	delta->x = abs(pc_pos.x - g_pos.x);
	delta->y = abs(pc_pos.y - g_pos.y);
	if (pc_pos.x > g_pos.x)
		sign->x = 1;
	else
		sign->x = -1;
	if (pc_pos.y > g_pos.y)
		sign->y = 1;
	else
		sign->y = -1;
}

bool	view_not_blocked(t_data *data, t_vector_int pc_pos, t_vector_int g_pos)
{
	t_vector_int	sign;
	t_vector_int	delta;
	int				err;

	set_val(&delta, &sign, pc_pos, g_pos);
	err = 2 * (delta.y - delta.x);
	while (1)
	{
		if (is_wall_tile(data->level.map[g_pos.y][g_pos.x]) || \
			door_check(data, g_pos))
			return (false);
		if (g_pos.x == pc_pos.x && g_pos.y == pc_pos.y)
			return (true);
		if (err >= 0)
		{
			g_pos.y += sign.y;
			err = err - 2 * delta.x;
		}
		if (err < 0)
		{
			g_pos.x += sign.x;
			err = err + 2 * delta.y;
		}
	}	
}

void	rotate_enemy(t_data *data, t_sprite *enemy)
{
	double			enemy_angle;
	double			rot_speed;
	t_vector_double	old_dir;
	t_vector_double	rotation;
	t_vector_double	shifted_pos;

	enemy_angle = get_angle_of_attack(data->cam.pos, enemy->map_pos, enemy->dir);
	shifted_pos.x = enemy->map_pos.x - 0.5;
	shifted_pos.y = enemy->map_pos.y - 0.5;
	if (!enemy->player_detected && enemy_angle < (M_PI_2 + M_PI_4))
	{
		if (!enemy->scanned_for_player)
		{
			enemy->player_detected = is_target_visible(data->cam.pos, shifted_pos, enemy->dir, data);
			enemy->scanned_for_player = true;
			if (enemy->player_detected)
				printf("player detected\n");
		}
	}
	if (enemy->player_detected && enemy_angle > WEAPON_FOV)
	{
		rot_speed = 0.2;
		rotation.x = cos(rot_speed);
		rotation.y = sin(rot_speed);
		old_dir.x = enemy->dir.x;
		old_dir.y = enemy->dir.y;
		enemy->dir.x = enemy->dir.x * rotation.x - enemy->dir.y * rotation.y;
		enemy->dir.y = old_dir.x * rotation.y + enemy->dir.y * rotation.x;
		if (get_angle_of_attack(data->cam.pos, enemy->map_pos, enemy->dir) < enemy_angle)
			return ;
		else
		{
			rotation.x = cos(-rot_speed);
			rotation.y = sin(-rot_speed);
			enemy->dir.x = old_dir.x * rotation.x - old_dir.y * rotation.y;
			enemy->dir.y = old_dir.x * rotation.y + old_dir.y * rotation.x;
			if (get_angle_of_attack(data->cam.pos, enemy->map_pos, enemy->dir) > enemy_angle)
			{
				enemy->dir.x = (data->cam.pos.x - enemy->map_pos.x) / enemy->dist;
				enemy->dir.y = (data->cam.pos.y - enemy->map_pos.y) / enemy->dist;
				//printf("overshoot correction\n");
			}
		}
	}
}
