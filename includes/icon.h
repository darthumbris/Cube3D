/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   icon.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/09 14:52:42 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/15 14:50:12 by shoogenb      ########   odam.nl         */
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
	unsigned char	tile_value_begin;
	unsigned char	tile_value_end;
}	t_icon;

static const t_icon	wall_icon_lst[] = \
	{
		{"greybrick1",0,0,"WALL001.png", 1, 1},
		{"greybrick2",0,1,"WALL002.png", 2, 2},
		{"greybrick3",0,2,"WALL003.png", 3, 3},
		{"gbrick eagle",0,3,"WALL004.png", 4, 4},
		{"gbrick flag",0,4,"WALL005.png", 5, 5},
		{"gbrick hit",0,5,"WALL006.png", 6, 6},
		{"gbrick sign",0,6,"WALL030.png", 7, 7},
		{"bluebrick1",1,0,"WALL007.png", 8, 8},
		{"bluebrick2",1,1,"WALL023.png", 9, 9},
		{"bbrick sign",1,2,"WALL032.png", 10, 10},
		{"blue line",1,4,"WALL051.png", 11, 11},
		{"blue cross",1,5,"WALL052.png", 12, 12},
		{"blue skull",1,6,"WALL053.png", 13, 13},
		{"mossybrick1",1,7,"WALL028.png", 14, 14},
		{"mossybrick2",1,8,"WALL029.png", 15, 15},
		{"wood",2,0,"WALL028.png", 16, 16},
		{"wood eagle",2,1,"WALL019.png", 17, 17},
		{"wood cross",2,2,"WALL041.png", 18, 18},
		{"wood hit",2,3,"WALL049.png", 19, 19},
		{"purple1",2,5,"WALL059.png", 20, 20},
		{"purple2",2,6,"WALL060.png", 21, 21},
		{"messybrick1",2,7,"WALL021.png", 22, 22},
		{"messybrick2",2,8,"WALL022.png", 23, 23},
		{"steel wall",3,0,"WALL024.png", 24, 24},
		{"steel sign",3,1,"WALL025.png", 25, 25},
		{"tilebrick1",3,2,"WALL040.png", 26, 26},
		{"tilebrick2",3,3,"WALL042.png", 27, 27},
		{"tile flag",3,4,"WALL041.png", 28, 28},
		{"stone1",3,5,"WALL043.png", 29, 29},
		{"stone2",3,6,"WALL044.png", 30, 30},
		{"stone3",3,7,"WALL054.png", 31, 31},
		{"whitebrick1",4,0,"WALL034.png", 32, 32},
		{"wbrick hole",4,1,"WALL035.png", 33, 33},
		{"wbrick crack",4,2,"WALL036.png", 34, 34},
		{"wbrick hit,4",4,3,"WALL037.png", 35, 35},
		{"wbrick map",4,4,"WALL038.png", 36, 36},
		{"mosiac",4,5,"WALL047.png", 37, 37},
		{"redbrick",5,0,"WALL008.png", 38, 38},
		{"rbrick eagle",5,1,"WALL009.png", 39, 39},
		{"rbrick cross",5,2,"WALL010.png", 40, 40},
		{"mixedbrick",5,3,"WALL039.png", 41, 41},
		{"wood arch",2,4,"WALL050.png", 42, 42},
		{"railing",3,8,"WALL017.png", 43, 43},
		{"prison cell",1,3,"WALL020.png", 44, 44},
		{"switch",5,4,"WALL061.png", 45, 45},
		{"steel door",0,7,"WALL011.png", 169, 172},
		{"door1",4,6,"WALL014.png", 173, 176},
		{"door2",4,7,"WALL015.png", 177, 180},
		{"door3",4,8,"WALL016.png", 181, 184},
		{"door4",5,5,"WALL018.png", 185, 188},
	};

static const t_icon	zone_icon_lst[] = \
	{
		{"zone01",0,0,"WALL001.png", 189, 189},
		{"zone02",0,1,"WALL002.png", 190, 190},
		{"zone03",0,2,"WALL003.png", 191, 191},
		{"zone04",0,3,"WALL004.png", 192, 192},
		{"zone05",0,4,"WALL005.png", 193, 193},
		{"zone06",0,5,"WALL006.png", 194, 194},
		{"zone07",0,6,"WALL030.png", 195, 195},
		{"zone08",0,7,"WALL011.png", 196, 196},
		{"zone09",0,8,"WALL012.png", 197, 197},
		{"zone10",1,0,"WALL007.png", 198, 198},
		{"zone11",1,1,"WALL023.png", 199, 199},
		{"zone12",1,2,"WALL032.png", 201, 201},
		{"zone13",1,3,"WALL020.png", 202, 202},
		{"zone14",1,4,"WALL051.png", 203, 203},
		{"zone15",1,5,"WALL052.png", 204, 204},
		{"zone16",1,6,"WALL053.png", 205, 205},
		{"zone17",1,7,"WALL028.png", 206, 206},
		{"zone18",1,8,"WALL029.png", 207, 207},
		{"zone19",2,0,"WALL028.png", 208, 208},
		{"zone20",2,1,"WALL019.png", 209, 209},
		{"zone21",2,2,"WALL041.png", 210, 210},
		{"zone22",2,3,"WALL049.png", 211, 211},
		{"zone23",2,4,"WALL050.png", 212, 212},
		{"zone24",2,5,"WALL059.png", 213, 213},
		{"zone25",2,6,"WALL060.png", 214, 214},
		{"zone26",2,7,"WALL021.png", 215, 215},
		{"zone27",2,8,"WALL022.png", 216, 216},
		{"zone28",3,0,"WALL024.png", 217, 217},
		{"zone29",3,1,"WALL025.png", 218, 218},
		{"zone30",3,2,"WALL040.png", 219, 219},
		{"zone31",3,3,"WALL042.png", 220, 220},
		{"zone32",3,4,"WALL041.png", 221, 221},
		{"zone33",3,5,"WALL043.png", 222, 222},
		{"zone34",3,6,"WALL044.png", 223, 223},
		{"zone35",3,7,"WALL054.png", 224, 224},
		{"zone36",3,8,"WALL017.png", 225, 225}
	};

static const t_icon	obj_icon_lst[] = \
	{
		{"barrel gr",0,0,"BAR1A0.png" , 1, 1},
		{"bones1",0,1,"BONES5.png", 2, 2},
		{"bones2",0,2,"BRS1A0.png", 3, 3},
		{"bones3",0,3,"GOR4A0.png", 4, 4},
		{"bones4",0,4,"POB1A0.png", 5, 5},
		{"bones5",0,5,"POL5A0.png", 6, 6},
		{"bones6",0,6,"SMBTA0.png", 7, 7},
		{"bones7",0,7,"SMGTA0.png", 8, 8},
		{"bones8",1,0,"SMRTA0.png", 9, 9},
		{"lamp g",1,1,"CANDA0.png", 10, 10},
		{"stnd lamp g",1,2,"CBRAA0.png", 11, 11},
		{"chandelier",1,3,"COLUA0.png", 12, 12},
		{"lamp r",1,4,"CEYEB0.png", 13, 13},
		{"well empt",1,5,"CEYEA0.png", 14, 14},
		{"well water",1,6,"COL6A0.png", 15, 15},
		{"well blood",1,7,"HDB5B0.png", 16, 16},
		{"table",2,0,"WALL028.png", 17, 17},
		{"table chair",2,1,"WALL019.png", 18, 18},
		{"statue",2,2,"WALL041.png", 19, 19},
		{"tree1",2,3,"WALL049.png", 20, 20},
		{"barrel norm",2,4,"WALL050.png", 21, 21},
		{"pillar grey",2,5,"WALL059.png", 22, 22},
		{"orb",2,6,"WALL060.png", 23, 23},
		{"pike",2,7,"WALL021.png", 24, 24},
		{"cage1",3,0,"WALL024.png", 25, 25},
		{"cage2",3,1,"WALL025.png", 26, 26},
		{"cage3",3,2,"WALL040.png", 27, 27},
		{"cage4",3,3,"WALL042.png", 28, 28},
		{"hook",3,4,"WALL041.png", 29, 29},
		{"gargoyle",3,5,"WALL043.png", 30, 30},
		{"blood pudl",3,6,"WALL044.png", 31, 31},
		{"spikes",3,7,"WALL054.png", 32, 32},
		{"vines",4,0,"WALL034.png", 33, 33},
		{"pans1",4,1,"WALL035.png", 34, 34},
		{"pans2",4,2,"WALL036.png", 35, 35},
		{"sink",4,3,"WALL037.png", 36, 36},
		{"puddle wtr",4,4,"WALL038.png", 37, 37},
		{"furnace",4,5,"WALL047.png", 38, 38},
		{"pillar brwn",4,6,"WALL014.png", 39, 39},
		{"dogfood",4,7,"WALL015.png", 40, 40},
		{"pot",5,0,"WALL016.png", 41, 41},
		{"spears",5,1,"WALL008.png", 42, 42},
		{"bed",5,2,"WALL010.png", 43, 43},
		{"flag",5,3,"WALL039.png", 44, 44},
		{"tree2",5,4,"WALL061.png", 45, 45},
		{"plant1",5,5,"WALL018.png", 46, 46},
		{"truck",5,6,"WALL018.png", 47, 47},
		{"plant2",5,7,"WALL018.png", 48, 48},
		{"spout",6,0,"WALL018.png", 49, 49}
	};

static const t_icon	item_icon_lst[] = \
	{
		{"ammo1",0,0,"AMMOA0.png", 50, 50},
		{"silver key",0,1,"BKEYA0.png", 51, 51},
		{"dog meal",0,2,"BON1A0.png", 52, 52},
		{"cross",0,3,"BON2A0.png", 53, 53},
		{"chalice",0,4,"BON2B0.png", 54, 54},
		{"chest",0,5,"BON2C0.png", 55, 55},
		{"crown",0,6,"BON2D0.png", 56, 56},
		{"backpack",0,7,"BPAKA0.png", 57, 57},
		{"fuel",1,0,"CELLA0.png", 58, 58},
		{"clip",1,1,"CLIPA0.png", 59, 59},
		{"launcher",1,2,"LAUNA0.png", 60, 60},
		{"medkit",1,3,"MEDIA0.png", 61, 61},
		{"mach gun",1,4,"MGUNA0.png", 62, 62},
		{"plasmarifle",1,5,"PLASA0.png", 63, 63},
		{"rockets",1,6,"ROCKA0.png", 64, 64},
		{"shells",1,7,"SHELA0.png", 65, 65},
		{"shotgun",2,0,"SHOTA0.png", 66, 66},
		{"soul",2,1,"SOULA0.png", 67, 67},
		{"stimulant",2,2,"STIMA0.png", 68, 68},
		{"gold key",2,3,"YKEYA0.png", 69, 69}
	};

static const t_icon	enemy_icon_lst[] = \
	{
		{"player",2,7,"WSAF", 1, 4},
		{"push wall", 3, 0, "ads", 250, 253},
		{"guard",0,1,"guardspritesheet.png", 5, 16},
		{"dog",0,0,"dogspritesheet.png", 17, 28},
		{"mutant",0,2,"WALL003.png", 29, 40},
		{"officer",0,3,"WALL004.png", 41, 52},
		{"spectre",0,4,"WALL005.png", 53, 64},
		{"ss",0,5,"WALL006.png", 65, 76},
		{"barney",1,2,"WALL023.png", 125, 136},
		{"deathknight",1,3,"WALL032.png", 137, 148},
		{"devil",1,4,"WALL020.png", 149, 160},
		{"fake",1,5,"WALL051.png", 161, 172},
		{"fatface",1,6,"WALL052.png", 173, 184},
		{"gretel",1,7,"WALL053.png", 185, 196},
		{"hans",2,0,"WALL028.png", 197, 208},
		{"hitler",2,1,"WALL019.png", 209, 220},
		{"mechhitler",2,2,"WALL041.png", 221, 232},
		{"otto",2,3,"WALL049.png", 233, 244},
		{"schabs",2,4,"WALL050.png", 77, 88},
		{"trans",2,5,"WALL059.png", 89, 100},
		{"ubermutant",2,6,"WALL060.png", 101, 112},
		{"ghost1",0,6,"WALL030.png", 113, 116},
		{"ghost2",0,7,"WALL011.png", 117, 120},
		{"ghost3",1,0,"WALL012.png", 121, 124},
		{"ghost4",1,1,"WALL007.png", 245, 249}
	};

#endif
