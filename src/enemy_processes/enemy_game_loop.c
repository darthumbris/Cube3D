/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   enemy_game_loop.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/17 15:01:59 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/19 14:30:46 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static void	check_attack_sound_play(t_data *data, t_sprite *enemy)
{
	if (enemy->en_dat.frame == 1 && !enemy->en_dat.played_sound)
	{
		if (enemy->kind == DOG)
			play_sound_vol(data, "./assets/wav_files/sounds/dogatk.wav", \
				enemy->dist);
		if (enemy->kind == GUARD)
			play_sound_vol(data, "./assets/wav_files/sounds/grdatk.wav", \
				enemy->dist);
		enemy->en_dat.played_sound = true;
	}
}

static void	change_animation_frame(t_sprite *enemy, int delay, bool dead)
{
	if (!dead)
	{
		if (delay % 16 == 0 && enemy->en_dat.state != HURT)
			enemy->en_dat.frame++;
		if (enemy->en_dat.frame > 2 || \
			(delay % 24 == 0 && enemy->en_dat.state == HURT))
		{
			enemy->en_dat.frame = 0;
			enemy->en_dat.state = TRACKING;
		}
	}
	else
	{
		if (enemy->kind == GUARD && enemy->en_dat.frame > 4)
		{
			enemy->en_dat.state = DEAD;
			enemy->en_dat.frame = 4;
		}
		else if (enemy->kind == DOG && enemy->en_dat.frame > 3)
		{
			enemy->en_dat.state = DEAD;
			enemy->en_dat.frame = 3;
		}
	}
}

static void	check_enemies_attack(t_data *data)
{
	t_sprite_lst	*lst;
	static int		delay = 0;

	lst = data->sprite_lst;
	delay++;
	while (lst)
	{
		if (is_enemy_kind(lst->sprite_data.kind) \
			&& (lst->sprite_data.en_dat.state == ATTACKING || \
			lst->sprite_data.en_dat.state == HURT))
		{
			check_attack_sound_play(data, &lst->sprite_data);
			change_animation_frame(&lst->sprite_data, delay, false);
		}
		lst = lst->next;
	}
	if (delay > 48)
		delay = 0;
}

static void	check_enemies_dead(t_data *data)
{
	t_sprite_lst	*lst;
	static int		delay = 0;

	lst = data->sprite_lst;
	delay++;
	while (lst)
	{
		if (is_enemy_kind(lst->sprite_data.kind) \
			&& lst->sprite_data.en_dat.state == DYING)
		{
			if (delay % 8 == 0)
				lst->sprite_data.en_dat.frame++;
			change_animation_frame(&lst->sprite_data, 0, true);
		}
		lst = lst->next;
	}
	if (delay > 48)
		delay = 0;
}

void	update_enemies(t_data *data)
{
	check_enemies_attack(data);
	check_enemies_dead(data);
}
