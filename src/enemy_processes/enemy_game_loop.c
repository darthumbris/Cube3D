/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   enemy_game_loop.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/17 15:01:59 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/28 12:19:17 by shoogenb      ########   odam.nl         */
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
			enemy->en_dat.state = CHASE;
		}
	}
	else
	{
		if ((enemy->kind == GUARD || enemy->kind == BOSS_BARNEY) && enemy->en_dat.frame > 4)
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

static void	check_enemies_attack(t_data *data, t_sprite *enemy)
{
	static int		delay = 0;

	delay++;
	if (enemy->en_dat.state == ATTACK || \
		enemy->en_dat.state == HURT)
	{
		check_attack_sound_play(data, enemy);
		change_animation_frame(enemy, delay, false);
	}
	if (delay > 50)
		delay = 0;
}

static void	check_enemies_dead(t_sprite *enemy)
{
	static int		delay = 0;

	delay++;
	if (delay % 8 == 0)
		enemy->en_dat.frame++;
	change_animation_frame(enemy, 0, true);
	if (delay > 50)
		delay = 0;
	enemy->en_dat.state = DEAD;
}

//TODO change this to use a struct with function pointers
// similar to how real wolfenstein does it 
//	and (https://github.com/amalliar/cub3d) does it too
void	update_enemies(t_data *data, t_sprite *enemy)
{
	draw_enemies(data, enemy, &data->spr_cast);
	check_enemies_attack(data, enemy);
	if (enemy->en_dat.state == DYING)
		check_enemies_dead(enemy);
	path_find(data, enemy);
}
