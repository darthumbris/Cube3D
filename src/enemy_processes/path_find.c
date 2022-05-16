/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path_find.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/06 16:31:46 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/05/16 16:58:51 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static void	set_state(t_sprite *sprite, t_data *data)
{
	if (sprite->en_dat.player_detected && \
		((sprite->kind == DOG && sprite->dist < 2) || \
		(sprite->kind == GUARD && sprite->dist < 100)) && \
		sprite->en_dat.state == TRACKING)
		attack_player(sprite, data);
	//else
		//pathfind_to_player(data, sprite);	TODO do astar for tracking the player?
}

//TODO optimize this and have enemies try to move closer
//TODO and also check the rotate thing
void	path_find(t_data *data)
{
	t_sprite_lst	*lst;
	static int		delay = 0;

	lst = data->sprite_lst;
	delay++;
	while (lst)
	{
		if (is_enemy_kind(lst->sprite_data.kind) && lst->sprite_data.en_dat.state == PATROLLING)
			patrol_routine(data, &lst->sprite_data);
		if (is_enemy_kind(lst->sprite_data.kind) && (lst->sprite_data.en_dat.state == ALIVE || lst->sprite_data.en_dat.state == PATROLLING))
			check_for_player(data, &lst->sprite_data);
		else if (is_enemy_kind(lst->sprite_data.kind) && lst->sprite_data.en_dat.state == TRACKING)
		{
			track_player(data, &lst->sprite_data);
			set_state(&lst->sprite_data, data);
		}
		lst = lst->next;
	}
	if (delay > 48)
		delay = 0;
}
