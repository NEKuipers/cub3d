/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/02 10:51:16 by nkuipers       #+#    #+#                */
/*   Updated: 2019/12/02 16:01:12 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char		*ft_strchr(const char *s, int c)
{
	char	*string;
	int		i;
	char	d;

	d = (char)c;
	i = 0;
	string = (char *)s;
	while (string[i] != '\0')
	{
		if (string[i] == d)
			return (&string[i]);
		i++;
	}
	if (d == '\0')
		return (&string[i]);
	else
		return (NULL);
}

char		*ft_strdup(const char *s1)
{
	int		i;
	char	*new;

	i = 0;
	while (s1[i])
		i++;
	new = (char *)malloc(sizeof(char) * (i + 1));
	if (new == 0)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		new[i] = s1[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	if (s1 == 0 || s2 == 0)
		return (NULL);
	new = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (new == 0)
		return (NULL);
	while (s1[i] != '\0')
	{
		new[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		new[i] = s2[j];
		i++;
		j++;
	}
	new[i] = '\0';
	return (new);
}

size_t		ft_strlen(const char *s)
{
	int i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char		*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	i;
	size_t	j;

	new = 0;
	i = 0;
	if (s == 0)
		return (NULL);
	if (start + len <= ft_strlen(s))
		new = (char *)malloc(sizeof(char) * (len + 1));
	else
		new = (char *)malloc(sizeof(char) * (ft_strlen(s) - start + 1));
	if (new == 0)
		return (NULL);
	j = start;
	while (j < start + len && s[j])
	{
		new[i] = s[j];
		i++;
		j++;
	}
	new[i] = '\0';
	return (new);
}
