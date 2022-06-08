/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   menu_key_handler_utils.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/08 15:56:00 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/08 15:56:22 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

bool	is_movement_key(enum keys key)
{
	return (key == MLX_KEY_UP || key == MLX_KEY_DOWN || key == MLX_KEY_LEFT || \
			key == MLX_KEY_RIGHT || key == MLX_KEY_W || key == MLX_KEY_S || \
			key == MLX_KEY_A || key == MLX_KEY_S);
}
