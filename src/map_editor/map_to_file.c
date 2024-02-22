/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_to_file.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/14 15:25:38 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/23 13:35:34 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	change_size_values(int i, int j, t_vector_int *width, \
							t_vector_int *height)
{
	if (i < height->x)
		height->x = i;
	if (i > height->y)
		height->y = i;
	if (j < width->x)
		width->x = j;
	if (j > width->y)
		width->y = j;
}

t_vector_int	check_map_size(uint8_t map[200][200][3], int i, int j, int k)
{
	t_vector_int	width;
	t_vector_int	height;

	width.x = 200;
	height.x = 200;
	width.y = 0;
	height.y = 0;
	while (++i < 200)
	{
		j = -1;
		while (++j < 200)
		{
			k = -1;
			while (++k < 3)
			{
				if (map[i][j][k])
					change_size_values(i, j, &width, &height);
			}
		}
	}
	return ((t_vector_int){width.y - width.x, height.y - height.x});
}

t_vector_int	get_map_start(uint8_t map[200][200][3], int i, int j, int k)
{
	t_vector_int	start;

	start.x = 200;
	start.y = 200;
	while (++i < 200)
	{
		j = -1;
		while (++j < 200)
		{
			k = -1;
			while (++k < 3)
			{
				if (map[i][j][k])
				{
					if (i < start.y)
						start.y = i;
					if (j < start.x)
						start.x = j;
				}
			}
		}
	}
	return (start);
}

void	write_tile_coord(int fd, int i, int j, int k, int tile, bool first)
{
	if (!first)
		ft_putchar_fd(',', fd);
	ft_putnbr_fd(i, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd(j, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd(k, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd(tile, fd);
}

void	write_map_coords(t_map_edit *editor, int fd, int i, int j)
{
	int					k;
	const t_vector_int	start = get_map_start(editor->map, -1, -1, -1);
	bool				first;

	first = true;
	while (++i < 200)
	{
		j = -1;
		while (++j < 200)
		{
			k = -1;
			while (++k < 3)
			{
				if (editor->map[i][j][k])
				{
					write_tile_coord(fd, i - start.y, j - start.x, k, \
						editor->map[i][j][k], first);
					first = false;
				}
			}
		}
	}
}

void	write_to_file(t_map_edit *editor, int fd, t_vector_int wh)
{
	ft_putnbr_fd(wh.x + 1, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd(wh.y + 1, fd);
	ft_putchar_fd('\n', fd);
	ft_putendl_fd("128", fd);
	write_map_coords(editor, fd, -1, -1);
}

void	map_to_file(t_data *data)
{
	int				fd;
	char			*full_path;
	t_vector_int	wh;
	t_map_edit		*editor;

	editor = &data->menu.editor;
	wh = check_map_size(editor->map, -1, -1, -1);
	if (wh.x == 0 || wh.y == 0)
	{
		printf("Map is empty\n");
		return ;
	}
	full_path = ft_strjoin_r("saves/", editor->file.filenname);
	if (access(full_path, F_OK) == 0)
		printf("File already exists. Change filename\n");
	else
	{
		fd = open(full_path, O_WRONLY | O_CREAT, 0644);
		if (fd < 0)
		{
			printf("Failed to save file\n");
			free(full_path);
			return ;
		}
		write_to_file(editor, fd, wh);
		printf("Succesfully saved file\n");
		load_map(data);
	}
	free(full_path);
}
