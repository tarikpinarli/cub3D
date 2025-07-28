#ifndef MOVE_H
# define MOVE_H

#define MOVE_SPEED 0.035
#define ROT_SPEED 0.020
#define HOR_MOVE 0.019
#define COLLISION_MARGIN 0.05

typedef struct s_move
{
	double	offset_x;
	double	offset_y;
	double	target_x;
	double	target_y;
	bool	can_move_x;
	bool	can_move_y;
}	t_move;

#endif