/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_2.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/16 12:00:13 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/07/16 12:00:39 by nkuipers      ########   odam.nl         */
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
