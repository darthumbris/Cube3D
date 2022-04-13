#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	if (src < dst)
	{
		i = len;
		while (i > 0)
		{
			i--;
			((char *)dst)[i] = ((char *)src)[i];
		}
	}	
	else
	{
		i = 0;
		while (i < len)
		{
			((char *)dst)[i] = ((char *)src)[i];
			i++;
		}
	}
	return (dst);
}

char	*ft_strdup(const char *src)
{
	char	*copy;
	int		i;

	i = 0;
	copy = (char *)malloc((ft_strlen(src) + 1) * sizeof(char));
	if (!copy)
		return (NULL);
	while (src[i])
	{
		copy[i] = src[i];
		i++;
	}
	copy[i] = 0;
	return (copy);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*out;
	size_t	i;
	size_t	strlen;

	strlen = (ft_strlen(s));
	if (!s)
		return (NULL);
	if (start > strlen)
		return (ft_strdup(""));
	if (len > strlen - start)
		return (ft_strdup(s + start));
	out = (char *)malloc((len + 1) * sizeof(char));
	if (!out)
		return (NULL);
	i = 0;
	while (i < len && s[start] != 0)
	{
		out[i] = s[start];
		i++;
		start++;
	}
	out[i] = 0;
	return (out);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*out;
	size_t	i1;
	size_t	i2;

	if (!s1)
		return (ft_strdup(s2));
	i1 = ft_strlen(s1);
	i2 = ft_strlen(s2);
	out = malloc(sizeof(char) * (i1 + i2 + 1));
	if (!out)
		return (NULL);
	ft_memmove(out, s1, i1);
	free(s1);
	s1 = NULL;
	ft_memmove(out + i1, s2, i2);
	out[i1 + i2] = 0;
	return (out);
}
