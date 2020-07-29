/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   screenshot.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/03 16:11:50 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/07/29 10:43:30 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void		header_bmp(int fd, int width, int height)
{
	unsigned int size;
	unsigned int first_pix;

	first_pix = 54;
	size = height * width * 4 + 54;
	write(fd, "BM", 2);
	write(fd, &size, 4);
	write(fd, "\0\0\0\0", 4);
	write(fd, &first_pix, 4);
}

static void		header_dib_bmp(int fd, int width, int height)
{
	unsigned int	headersize;
	unsigned short	plane;
	unsigned short	bbp;

	headersize = 40;
	plane = 1;
	bbp = 32;
	write(fd, &headersize, 4);
	write(fd, &width, 4);
	write(fd, &height, 4);
	write(fd, &plane, 2);
	write(fd, &bbp, 2);
	while (plane <= 24)
	{
		write(fd, "\0", 1);
		plane++;
	}
}

static void		write_to_screenshot(int fd, t_data *data, int width, int height)
{
	int				x;
	unsigned int	color;

	height -= 1;
	while (height >= 0)
	{
		x = 0;
		while (x < width)
		{
			color = *(unsigned int *)(data->addr + (height *
				data->line_length + (x * (data->bpp / 8))));
			write(fd, &color, 3);
			write(fd, "\0", 1);
			x++;
		}
		height--;
	}
}

static void		make_screenshot(t_data *data, int width, int height)
{
	int		fd;
	char	*name;

	name = "screenshot.bmp";
	fd = open(name, O_TRUNC | O_WRONLY | O_CREAT, 0644);
	if (fd < 0)
	{
		write(1, "Could not create screenshot\n", 12);
		return ;
	}
	header_bmp(fd, width, height);
	header_dib_bmp(fd, width, height);
	write_to_screenshot(fd, data, width, height);
	write(1, "Screenshot made\n", 16);
}

int				ft_screenshot(t_info *info)
{
	if (info->scrshot == 0)
		return (0);
	if (info->det.sshx > 16384)
		info->det.sshx = 16384;
	if (info->det.sshy > 16384)
		info->det.sshy = 16384;
	make_screenshot(&info->data, info->det.sshx, info->det.sshy);
	free_struct(info);
	exit(1);
	return (0);
}
