/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   enemies.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/20 10:03:47 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/22 12:19:23 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENEMIES_H
# define ENEMIES_H

enum e_enemy_kinds
{
	GUARD_STANDING = 127,
	GUARD_PATROL,
	OFFICER_STANDING,
	OFFICER_PATROL,
	SS_STANDING,
	SS_PATROL,
	DOG_STANDING,
	DOG_PATROL,
	MUTANT_STANDING,
	MUTANT_PATROL,
	SPECTRE_STANDING,
	SPECTRE_PATROL,
	DEATHKNIGHT_STANDING,
	DEATHKNIGHT_PATROL,
	UBERMUTANT_STANDING,
	UBERMUTANT_PATROL,
	BARNEY,
	DEVIL,
	FAKE,
	FATFACE,
	GRETEL,
	HANS,
	HITLER,
	MECHHITLER,
	OTTO,
	SCHABS,
	TRANS,
	GHOST1,
	GHOST2,
	GHOST3,
	GHOST4,
};

enum e_enemies
{
	GUARD = 255,
	DOG,
	OFFICER,
	SS,
	MUTANT,
	SPECTRE,
	DEATHKNIGHT,
	UBERMUTANT,
	BOSS_BARNEY,
	BOSS_DEVIL,
	BOSS_FAKE,
	BOSS_FAT,
	BOSS_GRET,
	BOSS_HANS,
	BOSS_HITL,
	BOSS_MECH,
	BOSS_OTTO,
	BOSS_SCHAB,
	BOSS_TRANS,
	PAC_1,
	PAC_2,
	PAC_3,
	PAC_4,
};

int	get_enemy_kind(uint8_t c);

#endif