#ifndef _STAGE_FILE_
#define _STAGE_FILE_

/*#:벽, 0:상자, 1:도착점, 2:캐릭터시작위치*/
const char Stage[MAXSTAGE][20][20] =
{
	{
		"####################",
		"####################",
		"####################",
		"####################",
		"####################",
		"####################",
		"####################",
		"####################",
		"##   0           1##",
		"## 2 0           1##",
		"##   0           1##",
		"####################",
		"####################",
		"####################",
		"####################",
		"####################",
		"####################",
		"####################",
		"####################",
		"####################"
	}, //Stage 0

	{
		"####################",
		"####################",
		"########1###########",
		"######## ###########",
		"######## ###########",
		"######## ###########",
		"######## ###########",
		"######## ###########",
		"##   0           1##",
		"## 2 0   0       1##",
		"##   0           1##",
		"####################",
		"####################",
		"####################",
		"####################",
		"####################",
		"####################",
		"####################",
		"####################",
		"####################"
	}, //Stage 1

	{
		"####################",
		"####################",
		"###1     ###########",
		"###     0######  1##",
		"###               ##",
		"#######  #######1 ##",
		"####### ############",
		"####### ############",
		"##   0            ##",
		"##          0     ##",
		"##                ##",
		"############# ######",
		"#############2######",
		"####################",
		"####################",
		"####################",
		"####################",
		"####################",
		"####################",
		"####################"
	}, //Stage 2

	{
		"####################",
		"####################",
		"####################",
		"###  ###############",
		"###           1#####",
		"###  ###############",
		"#### ###############",
		"#### ###############",
		"##   0            ##",
		"##  0      2     1##",
		"##   0           1##",
		"####################",
		"####################",
		"####################",
		"####################",
		"####################",
		"####################",
		"####################",
		"####################",
		"####################"
	}, //Stage 3

	{
		"####################",
		"####################",
		"#####1 #############",
		"#     ##############",
		"#  ##     ##########",
		"#   #####  #########",
		"##  #####  #########",
		"## ####### #########",
		"##   0            ##",
		"## 2 0            ##",
		"##   0            ##",
		"########## #########",
		"########## #########",
		"#########  #########",
		"######1     ########",
		"########      ######",
		"##########      1###",
		"########### ########",
		"########### ########",
		"####################"
	}, //Stage 4

};



#endif
