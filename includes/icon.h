/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   icon.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/09 14:52:42 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/09 16:15:52 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ICON_H
# define ICON_H

typedef struct s_icon
{
	char			*name;
	int				y;
	int				x;
	char			*tex_name;
}	t_icon;

static const t_icon	wall_icon_lst[51] = \
	{
		{"greybrick1",0,0,"WALL001.png"},
		{"greybrick2",0,1,"WALL002.png"},
		{"greybrick3",0,2,"WALL003.png"},
		{"gbrick eagle",0,3,"WALL004.png"},
		{"gbrick flag",0,4,"WALL005.png"},
		{"gbrick hit",0,5,"WALL006.png"},
		{"gbrick sign",0,6,"WALL030.png"},
		{"steel door1",0,7,"WALL011.png"},
		{"steel door2",0,8,"WALL012.png"},
		{"bluebrick1",1,0,"WALL007.png"},
		{"bluebrick2",1,1,"WALL023.png"},
		{"bbrick sign",1,2,"WALL032.png"},
		{"prison cell",1,3,"WALL020.png"},
		{"blue line",1,4,"WALL051.png"},
		{"blue cross",1,5,"WALL052.png"},
		{"blue skull",1,6,"WALL053.png"},
		{"mossybrick1",1,7,"WALL028.png"},
		{"mossybrick2",1,8,"WALL029.png"},
		{"wood",2,0,"WALL028.png"},
		{"wood eagle",2,1,"WALL019.png"},
		{"wood cross",2,2,"WALL041.png"},
		{"wood hit",2,3,"WALL049.png"},
		{"wood arch",2,4,"WALL050.png"},
		{"purple1",2,5,"WALL059.png"},
		{"purple2",2,6,"WALL060.png"},
		{"messybrick1",2,7,"WALL021.png"},
		{"messybrick2",2,8,"WALL022.png"},
		{"steel wall",3,0,"WALL024.png"},
		{"steel sign",3,1,"WALL025.png"},
		{"tilebrick1",3,2,"WALL040.png"},
		{"tilebrick2",3,3,"WALL042.png"},
		{"tile flag",3,4,"WALL041.png"},
		{"stone1",3,5,"WALL043.png"},
		{"stone2",3,6,"WALL044.png"},
		{"stone3",3,7,"WALL054.png"},
		{"railing",3,8,"WALL017.png"},
		{"whitebrick1",4,0,"WALL034.png"},
		{"wbrick hole",4,1,"WALL035.png"},
		{"wbrick crack",4,2,"WALL036.png"},
		{"wbrick hit,4",4,3,"WALL037.png"},
		{"wbrick map",4,4,"WALL038.png"},
		{"mosiac",4,5,"WALL047.png"},
		{"door1",4,6,"WALL014.png"},
		{"door2",4,7,"WALL015.png"},
		{"door3",4,8,"WALL016.png"},
		{"redbrick",5,0,"WALL008.png"},
		{"rbrick eagle",5,1,"WALL009.png"},
		{"rbrick cross",5,2,"WALL010.png"},
		{"mixedbrick",5,3,"WALL039.png"},
		{"switch",5,4,"WALL061.png"},
		{"door4",5,5,"WALL018.png"}
	};

static const t_icon	obj_icon_lst[49] = \
	{
		{"barrel gr",0,0,"WALL001.png"},
		{"bones1",0,1,"WALL002.png"},
		{"bones2",0,2,"WALL003.png"},
		{"bones3",0,3,"WALL004.png"},
		{"bones4",0,4,"WALL005.png"},
		{"bones5",0,5,"WALL006.png"},
		{"bones6",0,6,"WALL030.png"},
		{"bones7",0,7,"WALL011.png"},
		{"bones8",1,0,"WALL012.png"},
		{"lamp g",1,1,"WALL007.png"},
		{"stnd lamp g",1,2,"WALL023.png"},
		{"chandelier",1,3,"WALL032.png"},
		{"lamp r",1,4,"WALL020.png"},
		{"well empt",1,5,"WALL051.png"},
		{"well water",1,6,"WALL052.png"},
		{"well blood",1,7,"WALL053.png"},
		{"table",2,0,"WALL028.png"},
		{"table chair",2,1,"WALL019.png"},
		{"statue",2,2,"WALL041.png"},
		{"tree1",2,3,"WALL049.png"},
		{"barrel norm",2,4,"WALL050.png"},
		{"pillar grey",2,5,"WALL059.png"},
		{"orb",2,6,"WALL060.png"},
		{"pike",2,7,"WALL021.png"},
		{"cage1",3,0,"WALL024.png"},
		{"cage2",3,1,"WALL025.png"},
		{"cage3",3,2,"WALL040.png"},
		{"cage4",3,3,"WALL042.png"},
		{"hook",3,4,"WALL041.png"},
		{"gargoyle",3,5,"WALL043.png"},
		{"blood pudl",3,6,"WALL044.png"},
		{"spikes",3,7,"WALL054.png"},
		{"vines",4,0,"WALL034.png"},
		{"pans1",4,1,"WALL035.png"},
		{"pans2",4,2,"WALL036.png"},
		{"sink",4,3,"WALL037.png"},
		{"puddle wtr",4,4,"WALL038.png"},
		{"furnace",4,5,"WALL047.png"},
		{"pillar brwn",4,6,"WALL014.png"},
		{"dogfood",4,7,"WALL015.png"},
		{"pot",5,0,"WALL016.png"},
		{"spears",5,1,"WALL008.png"},
		{"bed",5,2,"WALL010.png"},
		{"flag",5,3,"WALL039.png"},
		{"tree2",5,4,"WALL061.png"},
		{"plant1",5,5,"WALL018.png"},
		{"truck",5,6,"WALL018.png"},
		{"plant2",5,7,"WALL018.png"},
		{"spout",6,0,"WALL018.png"}
	};

#endif
