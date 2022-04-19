/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/19 16:59:30 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/04/19 16:59:31 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*stringcircumcise(char *files, char *out)
{
	int	i;

	i = 0;
	while (files[i] != '\n' && files[i])
		i++;
	out = ft_substr(files, 0, i + 1);
	if (!out)
		return (NULL);
	ft_memmove(files, files + i + 1, (ft_strlen(files) - i));
	return (out);
}

static int	checknl(char *buf)
{	
	int	i;

	i = 0;
	if (!buf)
		return (0);
	while (buf[i])
	{
		if (buf[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static char	*helper(char **files, char *out, char *buf)
{
	*files = ft_strjoin(*files, buf);
	out = *files;
	*files = NULL;
	return (out);
}

char	*get_next_line(int fd)
{
	static char	*files[MAX_FD];
	static char	buf[BUFFER_SIZE + 1];
	int			bread;
	char		*out;

	out = NULL;
	if (fd < 0 || fd > MAX_FD || read(fd, buf, 0) < 0)
		return (NULL);
	if (checknl(files[fd]))
		return (stringcircumcise(files[fd], out));
	bread = 1;
	while (bread > 0)
	{
		bread = read(fd, buf, BUFFER_SIZE);
		buf[bread] = 0;
		if (bread == 0)
			break ;
		files[fd] = ft_strjoin(files[fd], buf);
		if (checknl(files[fd]))
			return (stringcircumcise(files[fd], out));
	}
	if (files[fd])
		return (helper(&files[fd], out, buf));
	return (NULL);
}
