/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_2.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/16 12:00:13 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/07/29 11:06:50 by nkuipers      ########   odam.nl         */
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

char		*ft_strjoin_cub3d(char *s1, char *s2)
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
	free(s1);
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

void		check_resolution(t_info *info)
{
	if (info->scrshot == 1)
	{
		info->det.resx = info->det.sshx;
		info->det.resy = info->det.sshy;
	}
}

static void	fc_color_test_2(t_info *info, char **temp)
{
	free_grid(temp);
	errormessage("Invalid floor/ceiling colors.", info);
}

int			fc_color_test(char *line, t_info *info)
{
	int		i;
	int		j;
	int		check;
	char	**temp;

	temp = ft_split(line, ',');
	i = 0;
	while (temp[i])
	{
		j = 0;
		check = 0;
		while (temp[i][j])
		{
			if (ft_isdigit(temp[i][j]))
				check = 1;
			j++;
		}
		if (check == 0)
			fc_color_test_2(info, temp);
		i++;
	}
	free_grid(temp);
	if (i != 3)
		errormessage("Invalid floor/ceiling colors.", info);
	return (0);
}
