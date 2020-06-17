/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dda.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: nkuipers <nkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/03 14:50:00 by nkuipers      #+#    #+#                 */
/*   Updated: 2020/06/12 14:25:35 by nkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <math.h>
#include <stdio.h>

void			tracing(t_info *info, t_data *data)
{
	for(int x = 0; x < info->det.resx; x++)
    {
      //calculate ray position and direction
    	info->rays.camerax = 2 * x / (double)info->det.resx - 1; //x-coordinate in camera space
     	info->rays.rdx = info->rays.dirx + info->rays.plx * info->rays.camerax;
    	info->rays.rdy = info->rays.diry + info->rays.ply * info->rays.camerax;
      //which box of the map we're in
    	info->rays.mapx = (int)info->rays.posx;
    	info->rays.mapy = (int)info->rays.posy;
       //length of ray from one x or y-side to next x or y-side
    	info->rays.ddx = sqrt(1 + pow(info->rays.rdy, 2) / pow(info->rays.rdx, 2));
    	info->rays.ddy = sqrt(1 + pow(info->rays.rdx, 2) / pow(info->rays.rdy, 2));

      //calculate step and initial sideDist
		info->rays.hit = 0;
    	if(info->rays.rdx < 0)
     	{
        	info->rays.step_x = -1;
       	 info->rays.sdx = (info->rays.posx - info->rays.mapx) * info->rays.ddx;
    	}
    	else
    	{
    		info->rays.step_x = 1;
    		info->rays.sdx = (info->rays.mapx + 1.0 - info->rays.posx) * info->rays.ddx;
		}
    	if(info->rays.rdy < 0)
    	{
    		info->rays.step_y = -1;
    		info->rays.sdy = (info->rays.posy - info->rays.mapy) * info->rays.ddy;
    	}
    	else
    	{
    	info->rays.step_y = 1;
        info->rays.sdy = (info->rays.mapy + 1.0 - info->rays.posy) * info->rays.ddy;
      	}
      //perform DDA
      	while (info->rays.hit == 0)
    	{
        //jump to next map square, OR in x-direction, OR in y-direction
    		if(info->rays.sdx < info->rays.sdy)
        	{
        		info->rays.sdx += info->rays.ddx;
        		info->rays.mapx += info->rays.step_x;
        		info->rays.side = 0;
        	}
        	else
        	{
        		info->rays.sdy += info->rays.ddy;
        		info->rays.mapy += info->rays.step_y;
        		info->rays.side = 1;
    		}
        //Check if ray has hit a wall
    		if(info->grid.gmap[info->rays.mapx][info->rays.mapy] == '1')
				info->rays.hit = 1;
    	}
		if (info->rays.side == 0)
			info->rays.pwd = (info->rays.mapx - info->rays.posx + (1 - info->rays.step_x) / 2) / info->rays.rdx;
    	else
			info->rays.pwd = (info->rays.mapy - info->rays.posy + (1 - info->rays.step_y) / 2) / info->rays.rdy;
		info->rays.lineheight = (int)(info->det.resy / info->rays.pwd);
		info->rays.drawstart = -info->rays.lineheight / 2 + info->det.resy / 2;
		if (info->rays.drawstart < 0)
			info->rays.drawstart = 0;
		info->rays.drawend = info->rays.lineheight / 2 + info->det.resy / 2;
		if (info->rays.drawend >= info->det.resy)
			info->rays.drawend = info->det.resy - 1;
		for (int y = info->rays.drawstart; y < info->rays.drawend; y++)
		{
			if (info->rays.side == 0)
				my_mlx_pixel_put(data, x, y, 0xE1C699);
			else
				my_mlx_pixel_put(data, x, y, 0xC88254);
		}
	}
}
