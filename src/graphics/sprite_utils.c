/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: y: shoogenb <shoogenb@student.codam.nl>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/21 11:51:11 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/20 10:56:45 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

int	get_enemy_kind(uint8_t c)
{
	switch (c)
	{
	case 5 ... 16:
		return (GUARD_STANDING);
	case 17 ... 28:
		return (GUARD_PATROL);
	case 29 ... 40:
		return (DOG_STANDING);
	case 173 ... 184:
		return (DOG_PATROL);
	case 41 ... 52:
		return (MUTANT_STANDING);
	case 53 ... 64:
		return (MUTANT_PATROL);
	case 65 ... 76:
		return (OFFICER_STANDING);
	case 77 ... 88:
		return (OFFICER_PATROL);
	case 89 ... 100:
		return (SS_STANDING);
	case 185 ... 196:
		return (SS_PATROL);
	case 101 ... 104:
		return (SPECTRE_STANDING);
	case 105 ... 108:
		return (SPECTRE_PATROL);
	case 109 ... 112:
		return (DEATHKNIGHT_STANDING);
	case 113 ... 116:
		return (DEATHKNIGHT_PATROL);
	case 117 ... 120:
		return (UBERMUTANT_STANDING);
	case 121 ... 124:
		return (UBERMUTANT_PATROL);
	case 125 ... 128:
		return (BARNEY);
	case 129 ... 132:
		return (DEVIL);
	case 133 ... 136:
		return (FAKE);
	case 137 ... 140:
		return (FATFACE);
	case 141 ... 144:
		return (GRETEL);
	case 145 ... 148:
		return (HANS);
	case 149 ... 152:
		return (HITLER);
	case 153 ... 156:
		return (MECHHITLER);
	case 157 ... 160:
		return (OTTO);
	case 161 ... 164:
		return (SCHABS);
	case 165 ... 168:
		return (TRANS);
	case 169:
		return (GHOST1);
	case 170:
		return (GHOST2);
	case 171:
		return (GHOST3);
	case 172:
		return (GHOST4);
	default:
		return (127);
	}
}

double	sprite_dist(t_vector_double start, t_vector_double end)
{
	end.x -= start.x;
	end.y -= start.y;
	return (end.x * end.x + end.y * end.y);
}

//optimize by swapping pointers instead of data
static void	swap_sprite(t_sprite_lst *lst, t_sprite_lst *lst2)
{
	t_sprite	temp;

	temp = lst->sprite_data;
	lst->sprite_data = lst2->sprite_data;
	lst2->sprite_data = temp;
}

static void	sort_only_valid(t_sprite_lst **current, t_sprite_lst **begin, \
							t_vector_double pos)
{
	double			dist1;
	double			dist2;

	dist1 = sprite_dist((*current)->sprite_data.map_pos, pos);
	dist2 = sprite_dist((*current)->next->sprite_data.map_pos, pos);
	if (dist1 < dist2)
	{
		swap_sprite(*current, (*current)->next);
		(*current)->sprite_data.dist = dist2;
		(*current)->next->sprite_data.dist = dist1;
		(*current) = *begin;
	}
	else
	{
		(*current)->sprite_data.dist = dist1;
		(*current)->next->sprite_data.dist = dist2;
	}
}

void	sort_sprites(t_data *data, t_sprite_lst **begin)
{
	t_sprite_lst	*current;

	current = *begin;
	while (current && current->next)
	{
		if (current->sprite_data.kind)
			sort_only_valid(&current, begin, data->cam.pos);
		current = current->next;
	}
}
