/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   new_map_parser.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/25 14:49:23 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/25 14:51:12 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

char	**new_map_parser(int fd, char **temp)
{
	char	buf[10001];
	char	*map;
	int		bytes_read;

	bytes_read = 1;
	map = NULL;
	if (fd == -1)
		return (map_error_msg("Failed to open map"));
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buf, 10000);
		if (bytes_read == -1)
			return (map_error_msg("Failed to read from map"));
		buf[bytes_read] = 0;
		if (bytes_read == 0)
			break ;
		map = ft_strjoin(map, buf);
	}
	temp = ft_split(map, '\n');
	free(map);
	return (temp);
}
