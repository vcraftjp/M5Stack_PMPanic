#include <Arduino.h>

const uint8_t font_36[] = {
// #0
	159, 0, 159, 0, 139, 0, 135, 1, 139, 0, 137, 0, 138, 1, 138, 0, 136, 0, 140, 1, 137, 0, 135, 0, 132, 1, 133, 2, 131, 1, 136, 0, 
	134, 0, 131, 1, 136, 2, 131, 1, 135, 0, 133, 0, 131, 1, 138, 2, 131, 1, 134, 0, 133, 0, 2, 1, 1, 1, 140, 2, 2, 1, 1, 1, 
	134, 0, 132, 0, 131, 1, 132, 2, 2, 1, 1, 1, 132, 2, 131, 1, 133, 0, 131, 0, 131, 1, 132, 2, 132, 1, 132, 2, 2, 1, 1, 1, 
	133, 0, 131, 0, 2, 1, 1, 1, 133, 2, 132, 1, 132, 2, 2, 1, 1, 1, 133, 0, 131, 0, 2, 1, 1, 1, 132, 2, 133, 1, 132, 2, 
	2, 1, 1, 1, 133, 0, 2, 0, 0, 0, 131, 1, 132, 2, 133, 1, 132, 2, 2, 1, 1, 1, 133, 0, 5, 0, 0, 0, 1, 1, 1, 132, 
	2, 134, 1, 132, 2, 2, 1, 1, 1, 133, 0, 5, 0, 0, 0, 1, 1, 1, 132, 2, 6, 1, 1, 1, 0, 1, 1, 1, 132, 2, 2, 1, 
	1, 1, 133, 0, 1, 0, 0, 131, 1, 132, 2, 134, 1, 132, 2, 2, 1, 1, 1, 133, 0, 4, 0, 0, 1, 1, 1, 133, 2, 133, 1, 133, 
	2, 2, 1, 1, 1, 133, 0, 4, 0, 0, 1, 1, 1, 133, 2, 133, 1, 133, 2, 2, 1, 1, 1, 133, 0, 4, 0, 0, 1, 1, 1, 132, 
	2, 134, 1, 132, 2, 131, 1, 133, 0, 4, 0, 0, 1, 1, 1, 132, 2, 6, 1, 1, 1, 0, 1, 1, 1, 132, 2, 2, 1, 1, 1, 134, 
	0, 4, 0, 0, 1, 1, 1, 132, 2, 134, 1, 132, 2, 2, 1, 1, 1, 134, 0, 4, 0, 0, 1, 1, 1, 132, 2, 133, 1, 132, 2, 131, 
	1, 134, 0, 4, 0, 0, 1, 1, 1, 132, 2, 133, 1, 132, 2, 2, 1, 1, 1, 135, 0, 4, 0, 0, 1, 1, 1, 132, 2, 132, 1, 133, 
	2, 2, 1, 1, 1, 135, 0, 4, 0, 0, 1, 1, 1, 132, 2, 132, 1, 132, 2, 131, 1, 135, 0, 1, 0, 0, 131, 1, 132, 2, 2, 1, 
	1, 1, 132, 2, 131, 1, 136, 0, 5, 0, 0, 0, 1, 1, 1, 140, 2, 2, 1, 1, 1, 137, 0, 2, 0, 0, 0, 131, 1, 138, 2, 131, 
	1, 137, 0, 131, 0, 131, 1, 136, 2, 131, 1, 138, 0, 132, 0, 131, 1, 133, 2, 132, 1, 139, 0, 133, 0, 140, 1, 140, 0, 134, 0, 138, 
	1, 141, 0, 135, 0, 135, 1, 143, 0, 159, 0, 159, 0, 
// #1
	159, 0, 159, 0, 144, 0, 132, 1, 137, 0, 143, 0, 134, 1, 136, 0, 141, 0, 137, 1, 135, 0, 140, 0, 132, 1, 5, 2, 2, 2, 1, 1, 
	1, 135, 0, 139, 0, 132, 1, 131, 2, 2, 1, 1, 1, 135, 0, 137, 0, 132, 1, 133, 2, 2, 1, 1, 1, 135, 0, 135, 0, 133, 1, 134, 
	2, 2, 1, 1, 1, 135, 0, 134, 0, 133, 1, 134, 2, 131, 1, 135, 0, 133, 0, 132, 1, 136, 2, 2, 1, 1, 1, 136, 0, 132, 0, 131, 
	1, 138, 2, 2, 1, 1, 1, 136, 0, 132, 0, 2, 1, 1, 1, 139, 2, 2, 1, 1, 1, 136, 0, 131, 0, 131, 1, 139, 2, 2, 1, 1, 
	1, 136, 0, 131, 0, 2, 1, 1, 1, 133, 2, 0, 1, 132, 2, 131, 1, 136, 0, 131, 0, 2, 1, 1, 1, 131, 2, 2, 1, 1, 1, 132, 
	2, 2, 1, 1, 1, 137, 0, 131, 0, 4, 1, 1, 1, 2, 2, 132, 1, 132, 2, 2, 1, 1, 1, 137, 0, 131, 0, 137, 1, 132, 2, 2, 
	1, 1, 1, 137, 0, 132, 0, 135, 1, 133, 2, 2, 1, 1, 1, 137, 0, 133, 0, 134, 1, 132, 2, 131, 1, 137, 0, 137, 0, 2, 1, 1, 
	1, 132, 2, 2, 1, 1, 1, 138, 0, 137, 0, 2, 1, 1, 1, 132, 2, 2, 1, 1, 1, 138, 0, 136, 0, 131, 1, 132, 2, 2, 1, 1, 
	1, 138, 0, 136, 0, 2, 1, 1, 1, 133, 2, 2, 1, 1, 1, 138, 0, 136, 0, 2, 1, 1, 1, 132, 2, 131, 1, 138, 0, 136, 0, 2, 
	1, 1, 1, 132, 2, 2, 1, 1, 1, 139, 0, 136, 0, 2, 1, 1, 1, 132, 2, 2, 1, 1, 1, 139, 0, 135, 0, 131, 1, 132, 2, 2, 
	1, 1, 1, 139, 0, 135, 0, 2, 1, 1, 1, 133, 2, 2, 1, 1, 1, 139, 0, 135, 0, 2, 1, 1, 1, 132, 2, 131, 1, 139, 0, 135, 
	0, 2, 1, 1, 1, 132, 2, 2, 1, 1, 1, 140, 0, 135, 0, 138, 1, 140, 0, 136, 0, 136, 1, 141, 0, 137, 0, 134, 1, 142, 0, 159, 
	0, 159, 0, 
// #2
	159, 0, 159, 0, 138, 0, 136, 1, 139, 0, 136, 0, 139, 1, 138, 0, 135, 0, 141, 1, 137, 0, 134, 0, 132, 1, 134, 2, 131, 1, 136, 0, 
	133, 0, 131, 1, 137, 2, 131, 1, 135, 0, 132, 0, 131, 1, 139, 2, 131, 1, 134, 0, 132, 0, 2, 1, 1, 1, 141, 2, 131, 1, 133, 0, 
	131, 0, 131, 1, 133, 2, 2, 1, 1, 1, 133, 2, 2, 1, 1, 1, 133, 0, 131, 0, 2, 1, 1, 1, 133, 2, 132, 1, 132, 2, 2, 1, 
	1, 1, 133, 0, 131, 0, 2, 1, 1, 1, 132, 2, 133, 1, 132, 2, 2, 1, 1, 1, 133, 0, 131, 0, 131, 1, 131, 2, 133, 1, 132, 2, 
	2, 1, 1, 1, 133, 0, 132, 0, 140, 1, 132, 2, 2, 1, 1, 1, 133, 0, 133, 0, 138, 1, 133, 2, 2, 1, 1, 1, 133, 0, 134, 0, 
	136, 1, 133, 2, 131, 1, 133, 0, 139, 0, 131, 1, 133, 2, 2, 1, 1, 1, 134, 0, 138, 0, 131, 1, 133, 2, 131, 1, 134, 0, 137, 0, 
	131, 1, 133, 2, 131, 1, 135, 0, 136, 0, 131, 1, 133, 2, 131, 1, 136, 0, 135, 0, 131, 1, 133, 2, 131, 1, 137, 0, 134, 0, 131, 1, 
	133, 2, 131, 1, 138, 0, 133, 0, 131, 1, 133, 2, 131, 1, 139, 0, 132, 0, 131, 1, 133, 2, 134, 1, 137, 0, 131, 0, 131, 1, 133, 2, 
	136, 1, 136, 0, 131, 0, 2, 1, 1, 1, 133, 2, 138, 1, 135, 0, 2, 0, 0, 0, 131, 1, 141, 2, 2, 1, 1, 1, 135, 0, 5, 0, 
	0, 0, 1, 1, 1, 142, 2, 2, 1, 1, 1, 135, 0, 1, 0, 0, 131, 1, 142, 2, 2, 1, 1, 1, 135, 0, 4, 0, 0, 1, 1, 1, 
	142, 2, 131, 1, 135, 0, 4, 0, 0, 1, 1, 1, 142, 2, 2, 1, 1, 1, 136, 0, 1, 0, 0, 148, 1, 136, 0, 2, 0, 0, 0, 146, 
	1, 137, 0, 131, 0, 144, 1, 138, 0, 159, 0, 159, 0, 
// #3
	159, 0, 159, 0, 139, 0, 135, 1, 139, 0, 137, 0, 139, 1, 137, 0, 135, 0, 142, 1, 136, 0, 134, 0, 133, 1, 133, 2, 132, 1, 135, 0, 
	133, 0, 132, 1, 137, 2, 131, 1, 134, 0, 133, 0, 2, 1, 1, 1, 140, 2, 2, 1, 1, 1, 134, 0, 132, 0, 131, 1, 140, 2, 131, 1, 
	133, 0, 132, 0, 2, 1, 1, 1, 133, 2, 2, 1, 1, 1, 133, 2, 2, 1, 1, 1, 133, 0, 131, 0, 131, 1, 132, 2, 132, 1, 132, 2, 
	2, 1, 1, 1, 133, 0, 131, 0, 2, 1, 1, 1, 132, 2, 133, 1, 132, 2, 2, 1, 1, 1, 133, 0, 131, 0, 133, 1, 1, 2, 2, 133, 
	1, 132, 2, 2, 1, 1, 1, 133, 0, 132, 0, 139, 1, 133, 2, 2, 1, 1, 1, 133, 0, 133, 0, 137, 1, 133, 2, 131, 1, 133, 0, 136, 
	0, 131, 1, 136, 2, 2, 1, 1, 1, 134, 0, 136, 0, 131, 1, 135, 2, 131, 1, 134, 0, 136, 0, 2, 1, 1, 1, 134, 2, 132, 1, 135, 
	0, 136, 0, 2, 1, 1, 1, 135, 2, 131, 1, 135, 0, 136, 0, 133, 1, 133, 2, 131, 1, 134, 0, 131, 0, 139, 1, 133, 2, 2, 1, 1, 
	1, 134, 0, 2, 0, 0, 0, 141, 1, 132, 2, 2, 1, 1, 1, 134, 0, 1, 0, 0, 137, 1, 4, 0, 0, 1, 1, 1, 132, 2, 2, 1, 
	1, 1, 134, 0, 0, 0, 131, 1, 131, 2, 7, 1, 1, 1, 0, 0, 1, 1, 1, 132, 2, 2, 1, 1, 1, 134, 0, 3, 0, 1, 1, 1, 
	132, 2, 135, 1, 132, 2, 2, 1, 1, 1, 134, 0, 3, 0, 1, 1, 1, 133, 2, 133, 1, 132, 2, 131, 1, 134, 0, 0, 0, 131, 1, 133, 
	2, 131, 1, 133, 2, 2, 1, 1, 1, 135, 0, 4, 0, 0, 1, 1, 1, 142, 2, 131, 1, 135, 0, 1, 0, 0, 131, 1, 140, 2, 131, 1, 
	136, 0, 2, 0, 0, 0, 131, 1, 138, 2, 131, 1, 137, 0, 131, 0, 132, 1, 134, 2, 132, 1, 138, 0, 132, 0, 142, 1, 139, 0, 133, 0, 
	140, 1, 140, 0, 135, 0, 136, 1, 142, 0, 159, 0, 159, 0, 
// #4
	159, 0, 159, 0, 143, 0, 135, 1, 135, 0, 142, 0, 137, 1, 134, 0, 141, 0, 139, 1, 133, 0, 140, 0, 131, 1, 133, 2, 2, 1, 1, 1, 
	133, 0, 140, 0, 2, 1, 1, 1, 134, 2, 2, 1, 1, 1, 133, 0, 139, 0, 131, 1, 133, 2, 131, 1, 133, 0, 138, 0, 131, 1, 134, 2, 
	2, 1, 1, 1, 134, 0, 137, 0, 131, 1, 135, 2, 2, 1, 1, 1, 134, 0, 137, 0, 2, 1, 1, 1, 136, 2, 2, 1, 1, 1, 134, 0, 
	136, 0, 131, 1, 136, 2, 2, 1, 1, 1, 134, 0, 135, 0, 131, 1, 137, 2, 2, 1, 1, 1, 134, 0, 134, 0, 131, 1, 137, 2, 131, 1, 
	134, 0, 134, 0, 2, 1, 1, 1, 132, 2, 0, 1, 132, 2, 2, 1, 1, 1, 135, 0, 133, 0, 131, 1, 132, 2, 0, 1, 132, 2, 2, 1, 
	1, 1, 135, 0, 132, 0, 131, 1, 132, 2, 1, 1, 1, 132, 2, 2, 1, 1, 1, 135, 0, 131, 0, 131, 1, 132, 2, 2, 1, 1, 1, 132, 
	2, 2, 1, 1, 1, 135, 0, 131, 0, 2, 1, 1, 1, 132, 2, 2, 1, 1, 1, 132, 2, 131, 1, 135, 0, 2, 0, 0, 0, 131, 1, 132, 
	2, 2, 1, 1, 1, 132, 2, 131, 1, 135, 0, 1, 0, 0, 131, 1, 132, 2, 131, 1, 132, 2, 132, 1, 134, 0, 4, 0, 0, 1, 1, 1, 
	132, 2, 132, 1, 132, 2, 133, 1, 133, 0, 4, 0, 0, 1, 1, 1, 145, 2, 2, 1, 1, 1, 133, 0, 0, 0, 131, 1, 145, 2, 2, 1, 
	1, 1, 133, 0, 3, 0, 1, 1, 1, 145, 2, 131, 1, 133, 0, 3, 0, 1, 1, 1, 145, 2, 2, 1, 1, 1, 134, 0, 0, 0, 140, 1, 
	132, 2, 133, 1, 134, 0, 1, 0, 0, 139, 1, 132, 2, 132, 1, 135, 0, 2, 0, 0, 0, 137, 1, 133, 2, 131, 1, 136, 0, 137, 0, 2, 
	1, 1, 1, 132, 2, 131, 1, 137, 0, 137, 0, 2, 1, 1, 1, 132, 2, 2, 1, 1, 1, 138, 0, 137, 0, 138, 1, 138, 0, 138, 0, 136, 
	1, 139, 0, 139, 0, 134, 1, 140, 0, 159, 0, 159, 0, 
// #5
	159, 0, 159, 0, 136, 0, 143, 1, 134, 0, 135, 0, 145, 1, 133, 0, 134, 0, 147, 1, 132, 0, 134, 0, 2, 1, 1, 1, 141, 2, 2, 1, 
	1, 1, 132, 0, 133, 0, 131, 1, 141, 2, 2, 1, 1, 1, 132, 0, 133, 0, 2, 1, 1, 1, 142, 2, 2, 1, 1, 1, 132, 0, 133, 0, 
	2, 1, 1, 1, 141, 2, 131, 1, 132, 0, 132, 0, 131, 1, 141, 2, 2, 1, 1, 1, 133, 0, 132, 0, 2, 1, 1, 1, 133, 2, 139, 1, 
	133, 0, 132, 0, 2, 1, 1, 1, 132, 2, 139, 1, 134, 0, 132, 0, 2, 1, 1, 1, 132, 2, 138, 1, 135, 0, 131, 0, 131, 1, 138, 2, 
	131, 1, 136, 0, 131, 0, 2, 1, 1, 1, 140, 2, 131, 1, 135, 0, 131, 0, 2, 1, 1, 1, 141, 2, 131, 1, 134, 0, 2, 0, 0, 0, 
	131, 1, 142, 2, 131, 1, 133, 0, 5, 0, 0, 0, 1, 1, 1, 133, 2, 131, 1, 134, 2, 2, 1, 1, 1, 133, 0, 5, 0, 0, 0, 1, 
	1, 1, 132, 2, 134, 1, 132, 2, 2, 1, 1, 1, 133, 0, 2, 0, 0, 0, 142, 1, 132, 2, 2, 1, 1, 1, 133, 0, 131, 0, 136, 1, 
	4, 0, 0, 1, 1, 1, 132, 2, 2, 1, 1, 1, 133, 0, 2, 0, 0, 0, 136, 1, 5, 0, 0, 0, 1, 1, 1, 132, 2, 2, 1, 1, 
	1, 133, 0, 1, 0, 0, 138, 1, 4, 0, 0, 1, 1, 1, 132, 2, 2, 1, 1, 1, 133, 0, 4, 0, 0, 1, 1, 1, 132, 2, 3, 1, 
	1, 1, 0, 131, 1, 132, 2, 2, 1, 1, 1, 133, 0, 4, 0, 0, 1, 1, 1, 132, 2, 134, 1, 132, 2, 131, 1, 133, 0, 4, 0, 0, 
	1, 1, 1, 132, 2, 133, 1, 133, 2, 2, 1, 1, 1, 134, 0, 1, 0, 0, 131, 1, 132, 2, 131, 1, 133, 2, 131, 1, 134, 0, 5, 0, 
	0, 0, 1, 1, 1, 141, 2, 131, 1, 135, 0, 2, 0, 0, 0, 131, 1, 139, 2, 131, 1, 136, 0, 131, 0, 131, 1, 137, 2, 131, 1, 137, 
	0, 132, 0, 132, 1, 133, 2, 132, 1, 138, 0, 133, 0, 141, 1, 139, 0, 134, 0, 139, 1, 140, 0, 136, 0, 135, 1, 142, 0, 159, 0, 159, 
	0, 
// #6
	159, 0, 159, 0, 140, 0, 134, 1, 139, 0, 138, 0, 138, 1, 137, 0, 137, 0, 140, 1, 136, 0, 136, 0, 132, 1, 132, 2, 132, 1, 135, 0, 
	135, 0, 131, 1, 136, 2, 131, 1, 134, 0, 134, 0, 131, 1, 138, 2, 2, 1, 1, 1, 134, 0, 133, 0, 131, 1, 139, 2, 131, 1, 133, 0, 
	132, 0, 131, 1, 133, 2, 1, 1, 1, 133, 2, 2, 1, 1, 1, 133, 0, 132, 0, 2, 1, 1, 1, 133, 2, 131, 1, 132, 2, 2, 1, 1, 
	1, 133, 0, 132, 0, 2, 1, 1, 1, 132, 2, 132, 1, 132, 2, 2, 1, 1, 1, 133, 0, 131, 0, 131, 1, 132, 2, 140, 1, 133, 0, 131, 
	0, 2, 1, 1, 1, 133, 2, 139, 1, 134, 0, 131, 0, 2, 1, 1, 1, 132, 2, 0, 1, 132, 2, 133, 1, 135, 0, 2, 0, 0, 0, 131, 
	1, 140, 2, 131, 1, 135, 0, 5, 0, 0, 0, 1, 1, 1, 142, 2, 2, 1, 1, 1, 135, 0, 5, 0, 0, 0, 1, 1, 1, 142, 2, 131, 
	1, 134, 0, 5, 0, 0, 0, 1, 1, 1, 134, 2, 2, 1, 1, 1, 133, 2, 2, 1, 1, 1, 134, 0, 5, 0, 0, 0, 1, 1, 1, 133, 
	2, 132, 1, 132, 2, 2, 1, 1, 1, 134, 0, 5, 0, 0, 0, 1, 1, 1, 133, 2, 132, 1, 132, 2, 2, 1, 1, 1, 134, 0, 5, 0, 
	0, 0, 1, 1, 1, 132, 2, 133, 1, 132, 2, 2, 1, 1, 1, 134, 0, 5, 0, 0, 0, 1, 1, 1, 132, 2, 133, 1, 132, 2, 2, 1, 
	1, 1, 134, 0, 5, 0, 0, 0, 1, 1, 1, 132, 2, 133, 1, 132, 2, 2, 1, 1, 1, 134, 0, 5, 0, 0, 0, 1, 1, 1, 132, 2, 
	132, 1, 133, 2, 2, 1, 1, 1, 134, 0, 5, 0, 0, 0, 1, 1, 1, 132, 2, 132, 1, 132, 2, 131, 1, 134, 0, 2, 0, 0, 0, 131, 
	1, 132, 2, 2, 1, 1, 1, 133, 2, 2, 1, 1, 1, 135, 0, 131, 0, 2, 1, 1, 1, 140, 2, 131, 1, 135, 0, 131, 0, 131, 1, 138, 
	2, 131, 1, 136, 0, 132, 0, 131, 1, 136, 2, 131, 1, 137, 0, 133, 0, 132, 1, 132, 2, 132, 1, 138, 0, 134, 0, 140, 1, 139, 0, 135, 
	0, 138, 1, 140, 0, 137, 0, 134, 1, 142, 0, 159, 0, 159, 0, 
// #7
	159, 0, 159, 0, 134, 0, 146, 1, 133, 0, 133, 0, 148, 1, 132, 0, 132, 0, 150, 1, 131, 0, 132, 0, 2, 1, 1, 1, 144, 2, 2, 1, 
	1, 1, 131, 0, 131, 0, 131, 1, 144, 2, 2, 1, 1, 1, 131, 0, 131, 0, 2, 1, 1, 1, 144, 2, 131, 1, 131, 0, 131, 0, 2, 1, 
	1, 1, 144, 2, 2, 1, 1, 1, 132, 0, 131, 0, 2, 1, 1, 1, 143, 2, 131, 1, 132, 0, 131, 0, 141, 1, 132, 2, 2, 1, 1, 1, 
	133, 0, 132, 0, 139, 1, 132, 2, 131, 1, 133, 0, 133, 0, 137, 1, 132, 2, 131, 1, 134, 0, 139, 0, 131, 1, 131, 2, 131, 1, 135, 0, 
	138, 0, 131, 1, 132, 2, 2, 1, 1, 1, 136, 0, 138, 0, 2, 1, 1, 1, 132, 2, 131, 1, 136, 0, 137, 0, 131, 1, 131, 2, 131, 1, 
	137, 0, 137, 0, 2, 1, 1, 1, 132, 2, 2, 1, 1, 1, 138, 0, 136, 0, 131, 1, 131, 2, 131, 1, 138, 0, 136, 0, 2, 1, 1, 1, 
	132, 2, 2, 1, 1, 1, 139, 0, 135, 0, 131, 1, 131, 2, 131, 1, 139, 0, 135, 0, 2, 1, 1, 1, 132, 2, 2, 1, 1, 1, 140, 0, 
	134, 0, 131, 1, 132, 2, 2, 1, 1, 1, 140, 0, 134, 0, 2, 1, 1, 1, 132, 2, 131, 1, 140, 0, 134, 0, 2, 1, 1, 1, 132, 2, 
	2, 1, 1, 1, 141, 0, 133, 0, 131, 1, 132, 2, 2, 1, 1, 1, 141, 0, 133, 0, 2, 1, 1, 1, 132, 2, 131, 1, 141, 0, 133, 0, 
	2, 1, 1, 1, 132, 2, 2, 1, 1, 1, 142, 0, 132, 0, 131, 1, 132, 2, 2, 1, 1, 1, 142, 0, 132, 0, 2, 1, 1, 1, 132, 2, 
	131, 1, 142, 0, 132, 0, 2, 1, 1, 1, 132, 2, 2, 1, 1, 1, 143, 0, 132, 0, 138, 1, 143, 0, 133, 0, 136, 1, 144, 0, 134, 0, 
	134, 1, 145, 0, 159, 0, 159, 0, 
// #8
	159, 0, 159, 0, 138, 0, 136, 1, 139, 0, 136, 0, 140, 1, 137, 0, 135, 0, 142, 1, 136, 0, 134, 0, 132, 1, 134, 2, 132, 1, 135, 0, 
	133, 0, 131, 1, 138, 2, 131, 1, 134, 0, 132, 0, 131, 1, 140, 2, 2, 1, 1, 1, 134, 0, 132, 0, 2, 1, 1, 1, 141, 2, 131, 1, 
	133, 0, 131, 0, 131, 1, 133, 2, 2, 1, 1, 1, 133, 2, 2, 1, 1, 1, 133, 0, 131, 0, 2, 1, 1, 1, 133, 2, 132, 1, 132, 2, 
	2, 1, 1, 1, 133, 0, 131, 0, 2, 1, 1, 1, 132, 2, 133, 1, 132, 2, 2, 1, 1, 1, 133, 0, 131, 0, 2, 1, 1, 1, 132, 2, 
	133, 1, 132, 2, 2, 1, 1, 1, 133, 0, 131, 0, 2, 1, 1, 1, 132, 2, 132, 1, 133, 2, 2, 1, 1, 1, 133, 0, 131, 0, 131, 1, 
	132, 2, 2, 1, 1, 1, 133, 2, 131, 1, 133, 0, 132, 0, 2, 1, 1, 1, 140, 2, 131, 1, 134, 0, 132, 0, 132, 1, 137, 2, 131, 1, 
	135, 0, 131, 0, 131, 1, 138, 2, 131, 1, 136, 0, 2, 0, 0, 0, 131, 1, 140, 2, 131, 1, 135, 0, 5, 0, 0, 0, 1, 1, 1, 133, 
	2, 131, 1, 132, 2, 131, 1, 134, 0, 1, 0, 0, 131, 1, 132, 2, 133, 1, 132, 2, 2, 1, 1, 1, 134, 0, 4, 0, 0, 1, 1, 1, 
	133, 2, 133, 1, 132, 2, 2, 1, 1, 1, 134, 0, 4, 0, 0, 1, 1, 1, 132, 2, 134, 1, 132, 2, 2, 1, 1, 1, 134, 0, 4, 0, 
	0, 1, 1, 1, 132, 2, 134, 1, 132, 2, 2, 1, 1, 1, 134, 0, 4, 0, 0, 1, 1, 1, 132, 2, 133, 1, 133, 2, 2, 1, 1, 1, 
	134, 0, 4, 0, 0, 1, 1, 1, 132, 2, 133, 1, 132, 2, 131, 1, 134, 0, 4, 0, 0, 1, 1, 1, 133, 2, 131, 1, 133, 2, 2, 1, 
	1, 1, 135, 0, 1, 0, 0, 131, 1, 141, 2, 131, 1, 135, 0, 2, 0, 0, 0, 131, 1, 139, 2, 131, 1, 136, 0, 131, 0, 131, 1, 137, 
	2, 131, 1, 137, 0, 132, 0, 132, 1, 133, 2, 132, 1, 138, 0, 133, 0, 141, 1, 139, 0, 134, 0, 139, 1, 140, 0, 136, 0, 135, 1, 142, 
	0, 159, 0, 159, 0, 
// #9
	159, 0, 159, 0, 138, 0, 135, 1, 140, 0, 136, 0, 139, 1, 138, 0, 135, 0, 141, 1, 137, 0, 134, 0, 132, 1, 133, 2, 132, 1, 136, 0, 
	133, 0, 131, 1, 137, 2, 131, 1, 135, 0, 132, 0, 131, 1, 139, 2, 131, 1, 134, 0, 131, 0, 131, 1, 141, 2, 2, 1, 1, 1, 134, 0, 
	131, 0, 2, 1, 1, 1, 133, 2, 131, 1, 132, 2, 2, 1, 1, 1, 134, 0, 2, 0, 0, 0, 131, 1, 132, 2, 133, 1, 131, 2, 131, 1, 
	133, 0, 5, 0, 0, 0, 1, 1, 1, 133, 2, 133, 1, 132, 2, 2, 1, 1, 1, 133, 0, 5, 0, 0, 0, 1, 1, 1, 132, 2, 134, 1, 
	132, 2, 2, 1, 1, 1, 133, 0, 5, 0, 0, 0, 1, 1, 1, 132, 2, 6, 1, 1, 1, 0, 1, 1, 1, 132, 2, 2, 1, 1, 1, 133, 
	0, 5, 0, 0, 0, 1, 1, 1, 132, 2, 134, 1, 132, 2, 2, 1, 1, 1, 133, 0, 5, 0, 0, 0, 1, 1, 1, 132, 2, 133, 1, 133, 
	2, 2, 1, 1, 1, 133, 0, 5, 0, 0, 0, 1, 1, 1, 132, 2, 133, 1, 133, 2, 2, 1, 1, 1, 133, 0, 5, 0, 0, 0, 1, 1, 
	1, 133, 2, 131, 1, 134, 2, 2, 1, 1, 1, 133, 0, 2, 0, 0, 0, 131, 1, 143, 2, 2, 1, 1, 1, 133, 0, 131, 0, 131, 1, 142, 
	2, 2, 1, 1, 1, 133, 0, 132, 0, 131, 1, 140, 2, 131, 1, 133, 0, 131, 0, 133, 1, 139, 2, 2, 1, 1, 1, 134, 0, 2, 0, 0, 
	0, 140, 1, 133, 2, 2, 1, 1, 1, 134, 0, 1, 0, 0, 141, 1, 132, 2, 131, 1, 134, 0, 4, 0, 0, 1, 1, 1, 132, 2, 132, 1, 
	133, 2, 2, 1, 1, 1, 135, 0, 4, 0, 0, 1, 1, 1, 132, 2, 132, 1, 132, 2, 131, 1, 135, 0, 4, 0, 0, 1, 1, 1, 133, 2, 
	2, 1, 1, 1, 133, 2, 2, 1, 1, 1, 136, 0, 1, 0, 0, 131, 1, 140, 2, 131, 1, 136, 0, 5, 0, 0, 0, 1, 1, 1, 139, 2, 
	131, 1, 137, 0, 2, 0, 0, 0, 131, 1, 137, 2, 131, 1, 138, 0, 131, 0, 132, 1, 133, 2, 132, 1, 139, 0, 132, 0, 141, 1, 140, 0, 
	133, 0, 139, 1, 141, 0, 135, 0, 135, 1, 143, 0, 159, 0, 159, 0, 
// #10
	159, 0, 159, 0, 159, 0, 159, 0, 159, 0, 159, 0, 159, 0, 132, 0, 132, 1, 139, 0, 132, 1, 132, 0, 131, 0, 5, 1, 1, 2, 2, 2, 
	1, 139, 0, 5, 1, 2, 2, 2, 1, 1, 131, 0, 9, 0, 0, 0, 1, 1, 2, 2, 2, 1, 1, 139, 0, 6, 1, 1, 2, 2, 2, 1, 
	1, 130, 0, 6, 0, 0, 1, 1, 2, 2, 2, 133, 1, 133, 0, 133, 1, 4, 2, 2, 2, 1, 1, 129, 0, 5, 0, 0, 1, 2, 2, 2, 
	131, 1, 2, 2, 2, 1, 133, 0, 2, 1, 2, 2, 131, 1, 3, 2, 2, 2, 1, 129, 0, 12, 0, 1, 1, 2, 2, 2, 1, 1, 1, 2, 
	2, 2, 1, 133, 0, 11, 1, 2, 2, 2, 1, 1, 1, 2, 2, 2, 1, 1, 128, 0, 10, 0, 1, 2, 2, 2, 1, 1, 1, 2, 2, 2, 
	137, 1, 9, 2, 2, 2, 1, 1, 1, 2, 2, 2, 1, 128, 0, 9, 0, 1, 2, 2, 2, 1, 1, 1, 2, 2, 131, 1, 131, 2, 131, 1, 
	8, 2, 2, 1, 1, 1, 2, 2, 2, 1, 128, 0, 12, 0, 1, 2, 2, 1, 1, 1, 2, 2, 2, 1, 1, 1, 133, 2, 11, 1, 1, 1, 
	2, 2, 2, 1, 1, 1, 2, 2, 1, 128, 0, 11, 0, 1, 2, 2, 1, 0, 1, 2, 2, 2, 1, 1, 135, 2, 10, 1, 1, 2, 2, 2, 
	1, 0, 1, 2, 2, 1, 128, 0, 11, 0, 1, 2, 2, 1, 0, 1, 2, 2, 1, 1, 1, 135, 2, 10, 1, 1, 1, 2, 2, 1, 0, 1, 
	2, 2, 1, 128, 0, 11, 0, 1, 2, 2, 1, 0, 1, 2, 2, 1, 1, 1, 135, 2, 10, 1, 1, 1, 2, 2, 1, 0, 1, 2, 2, 1, 
	128, 0, 11, 0, 1, 2, 2, 1, 0, 1, 2, 2, 2, 1, 1, 135, 2, 10, 1, 1, 2, 2, 2, 1, 0, 1, 2, 2, 1, 128, 0, 12, 
	0, 1, 2, 2, 1, 1, 1, 2, 2, 2, 1, 1, 1, 133, 2, 11, 1, 1, 1, 2, 2, 2, 1, 1, 1, 2, 2, 1, 128, 0, 9, 0, 
	1, 2, 2, 2, 1, 1, 1, 2, 2, 131, 1, 131, 2, 12, 1, 1, 1, 2, 2, 2, 1, 1, 1, 2, 2, 2, 1, 128, 0, 10, 0, 1, 
	2, 2, 2, 1, 1, 1, 2, 2, 2, 137, 1, 9, 2, 2, 2, 1, 1, 1, 2, 2, 2, 1, 128, 0, 12, 0, 1, 1, 2, 2, 2, 1, 
	1, 1, 2, 2, 2, 1, 133, 0, 11, 1, 2, 2, 2, 1, 1, 1, 2, 2, 2, 1, 1, 128, 0, 5, 0, 0, 1, 2, 2, 2, 131, 1, 
	2, 2, 2, 1, 133, 0, 2, 1, 2, 2, 131, 1, 3, 2, 2, 2, 1, 129, 0, 6, 0, 0, 1, 1, 2, 2, 2, 133, 1, 133, 0, 133, 
	1, 4, 2, 2, 2, 1, 1, 129, 0, 9, 0, 0, 0, 1, 1, 2, 2, 2, 1, 1, 139, 0, 6, 1, 1, 2, 2, 2, 1, 1, 130, 0, 
	131, 0, 5, 1, 1, 2, 2, 2, 1, 139, 0, 5, 1, 2, 2, 2, 1, 1, 131, 0, 132, 0, 132, 1, 139, 0, 132, 1, 132, 0, 159, 0, 
	159, 0, 159, 0, 159, 0, 159, 0, 159, 0, 159, 0, 
};