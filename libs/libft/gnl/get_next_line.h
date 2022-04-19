#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

# define MAX_FD 1024
# define BUFFER_SIZE 100

char	*get_next_line(int fd);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *src);
char	*ft_strjoin(char *s1, char *s2);

void	*ft_memmove(void *dst, const void *src, size_t len);

size_t	ft_strlen(const char *str);

#endif