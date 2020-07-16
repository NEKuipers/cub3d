/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_2.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/16 12:00:13 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/07/16 14:27:18 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int			rgb(int r, int g, int b)
{
	int	fc_color;

	fc_color = ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
	if (fc_color < 0)
		fc_color *= -1;
	return (fc_color);
}

char		*ft_strjoin_cub3d(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	new = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (new == 0)
		return (NULL);
	while (s1[i] != '\0')
	{
		new[i] = s1[i];
		i++;
	}
	new[i] = '\n';
	i++;
	while (s2[j] != '\0')
	{
		new[i] = s2[j];
		i++;
		j++;
	}
	new[i] = '\0';
	return (new);
}
