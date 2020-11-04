#include "tmp.h"

int	len_tmp(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return i;
}

int		ft_strnequ(char const *s1, char const *s2, size_t n)
{
	size_t i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (*s1 == *s2 && ++i < n)
	{
		if (*s1 == '\0' && *s2 == '\0')
			return (1);
		if (*s1 == '\0' || *s2 == '\0')
			return (0);
		s1++;
		s2++;
	}
	if (n == 0 || *s1 == *s2)
		return (1);
	return (0);
}

char	*new_str(int len)
{
	char	*buff;
	int		i;

	buff = (char *)malloc(sizeof(char) * (len + 1));
	if (!buff)
		return (NULL);
	i = 0;
	while (i < len + 1)
		buff[i++] = '\0';
	return (buff);
}

int	get_max(char *buff, char *hist)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (buff[i])
		i++;
	while (buff[j])
		j++;
	return (i > j ? i : j);
}
