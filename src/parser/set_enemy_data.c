/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_enemy_data.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/17 16:05:05 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/22 12:20:51 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static void	set_health(t_sprite *enemy)
{
	switch (enemy->kind)
	{
	case GUARD:
		enemy->en_dat.health = 25;
		break;
	case DOG:
		enemy->en_dat.health = 1;
		break;
	case SS:
		enemy->en_dat.health = 100;
		break;
	case MUTANT:
		enemy->en_dat.health = 45;
		break;
	case OFFICER:
		enemy->en_dat.health = 50;
		break;
	case PAC_1 ... PAC_4:
		enemy->en_dat.health = 2147483647;
		break;
	case SPECTRE:
		enemy->en_dat.health = 5;
		break;
	case DEATHKNIGHT:
		enemy->en_dat.health = 1250;
		break;
	case UBERMUTANT:
		enemy->en_dat.health = 1050;
		break;
	case BOSS_BARNEY:
		enemy->en_dat.health = 950;
		break;
	case BOSS_DEVIL:
		enemy->en_dat.health = 1450;
		break;
	case BOSS_FAKE:
		enemy->en_dat.health = 200;
		break;
	case BOSS_HITL:
		enemy->en_dat.health = 500;
		break;
	case BOSS_MECH:
		enemy->en_dat.health = 800;
		break;
	default:
		enemy->en_dat.health = 850;
	}
}

static void	set_state(t_sprite *enemy)
{
	const int	k = enemy->kind;

	if (k == GUARD_PATROL || k == OFFICER_PATROL || k == SS_PATROL || \
		k == DOG_PATROL || k == MUTANT_PATROL || k == SPECTRE_PATROL || \
		k == DEATHKNIGHT_PATROL || k == UBERMUTANT_PATROL)
		enemy->en_dat.state = PATROL;
	else
		enemy->en_dat.state = STAND;
}

static void	set_speed(t_sprite *enemy)
{
	if (enemy->kind != DOG)
		enemy->en_dat.speed = GUARD_MOVE_SPEED;
	else
		enemy->en_dat.speed = DOG_MOVE_SPEED;
}

static void	set_direction(t_sprite *enemy, uint8_t	tile)
{
	enemy->en_dat.dir.x = 0;
	enemy->en_dat.dir.y = 0;
	if (tile % 4 == 0)
		enemy->en_dat.dir.x = -1.0;
	else if (tile % 4 == 1)
		enemy->en_dat.dir.x = 1.0;
	else if (tile % 4 == 2)
		enemy->en_dat.dir.y = 1.0;
	else
		enemy->en_dat.dir.y = -1.0;
}

static void	set_kind(t_sprite *enemy)
{
	switch (enemy->kind)
	{
	case GUARD_STANDING ... GUARD_PATROL:
		enemy->kind = GUARD;
		break;
	case DOG_STANDING ... DOG_PATROL:
		enemy->kind = DOG;
		break;
	case OFFICER_STANDING ... OFFICER_PATROL:
		enemy->kind = OFFICER;
		break;
	case SS_STANDING ... SS_PATROL:
		enemy->kind = SS;
		break;
	case MUTANT_STANDING ... MUTANT_PATROL:
		enemy->kind = MUTANT;
		break;
	case SPECTRE_STANDING ... SPECTRE_PATROL:
		enemy->kind = SPECTRE;
	case DEATHKNIGHT_STANDING ... DEATHKNIGHT_PATROL:
		enemy->kind = DEATHKNIGHT;
	case UBERMUTANT_STANDING ... UBERMUTANT_PATROL:
		enemy->kind = UBERMUTANT;
		break;
	default:
		enemy->kind = enemy->kind - 135;
		break;
	}
}

void	set_enemy_data(t_sprite *enemy, uint8_t ***map, t_vector_int pos)
{
	enemy->en_dat.player_detected = false;
	set_state(enemy);
	set_kind(enemy);
	set_health(enemy);
	set_speed(enemy);
	set_direction(enemy, map[pos.y][pos.x][2]);
	enemy->en_dat.frame = 0;
	enemy->en_dat.counter = 0;
	enemy->en_dat.last_attack = 0;
}
