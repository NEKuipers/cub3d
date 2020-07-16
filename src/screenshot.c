/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   screenshot.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/03 16:11:50 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/07/16 14:01:51 by nkuipers      ########   odam.nl         */
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

static void		header_dip_bmp(int fd, int width, int height)
{
	unsigned int	headersize;
	unsigned short	plain;
	unsigned short	bbp;

	headersize = 40;
	plain = 1;
	bbp = 32;
	write(fd, &headersize, 4);
	write(fd, &width, 4);
	write(fd, &height, 4);
	write(fd, &plain, 2);
	write(fd, &bbp, 2);
	while (plain <= 24)
	{
		write(fd, "\0", 1);
		plain++;
	}
}

static void		write_to_screenshot(int fd, char *addr, int width, int height)
{
	int x;
	int line_length;

	line_length = 0;
	if (width % 64 != 0)
		line_length = 1;
	line_length = (line_length + (width / 64)) * 256;
	x = 0;
	height -= 1;
	while (height >= 0)
	{
		while (x < width)
		{
			write(fd, &addr[height * line_length + x * 4], 4);
			x++;
		}
		x = 0;
		height--;
	}
}

static void		make_screenshot(char *addr, int width, int height)
{
	int		fd;
	char	*name;

	name = "screenshot.bmp";
	fd = open(name, O_TRUNC | O_WRONLY | O_CREAT, 0777);
	if (fd < 0)
	{
		write(1, "Could not create screenshot\n", 12);
		return ;
	}
	header_bmp(fd, width, height);
	header_dip_bmp(fd, width, height);
	write_to_screenshot(fd, addr, width, height);
	write(1, "Screenshot made\n", 16);
}

int				ft_screenshot(t_info *info)
{
	if (info->scrshot == 0)
		return (0);
	make_screenshot(info->data.addr, info->det.sshx, info->det.sshy);
	if (info->det.sshx > info->det.resx || info->det.sshy > info->det.resy)
	{
		free_struct(info);
		exit(1);
	}
	return (0);
}
