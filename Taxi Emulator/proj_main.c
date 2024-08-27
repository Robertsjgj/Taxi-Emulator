/*
 - Character-oriented graphics on Windows
 - ECED 3401
 - 7 Oct 22
*/
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "emulator.h"

//extern int open_file(int, char* x[], int);
int num_of_h_buildings, num_of_v_buildings, map_x = 0, map_y = 0;
int building_scale;
int building_num = 0, ave = 0; //str = street number, ave = avenue number

int no_taxis = 0;
int no_mov_list_taxi = 0;
int no_park_list_taxi = 0;

int no_of_req = 0;
int wait_req_no = 0;
int acc_req_no = 0;
int no_of_completed_req = 0;
int total_no_req = 0;

int tick = 1;
int PC = 0; //CONDITION OF THE DIFFERENT DIRECTIONS/POSSIBILITIES OF APPROACHING A DESTINATION

int no_dropped_passengers = 0;
int no_picked_passengers = 0;

int line = 5, line1 = 5;

void move_cursor(int row, int col)
{
	/* Move cursor to specified row and column */
	COORD coord;
	coord.X = col;
	coord.Y = row;
	/* Windows function to position cursor */
	SetConsoleCursorPosition(Console, coord);

}

void draw_box(int ulr, int ulc, int scale)
{	/*
	 - Draw bot at ulr, ulc
	 - Height and width are "scaled"
	*/
	int rc;	/* Row count */
	int cc;	/* Column count */

	/* Top row */
	move_cursor(ulr, ulc);
	DISP(UL);
	for (cc = 0; cc < scale - 2; cc++)
		DISP(HBAR);
	DISP(UR);

	/* Verticals */
	int blah = scale / 2;
	for (rc = 1; rc < blah; rc++)
	{
		move_cursor(ulr + rc, ulc);
		DISP(VBAR);
		move_cursor(ulr + rc, ulc + scale - 1);
		DISP(VBAR);
	}

	/* Bottom row */
	move_cursor(ulr + (scale / 2), ulc);
	DISP(LL);
	for (rc = 0; rc < scale - 2; rc++)
		DISP(HBAR);
	DISP(LR);

}
void draw_map_boundary(int ulr, int ulc, int width, int height)
{	int rc;	/* Row count */
	int cc;	/* Column count */

	/* Top row */
	move_cursor(ulr, ulc);
	DISP(UL);
	for (cc = 0; cc < width - 2; cc++)
		DISP(HBAR);
	DISP(UR);

	/* Verticals */
	for (rc = 1; rc < height - 1; rc++)
	{
		move_cursor(ulr + rc, ulc);
		DISP(VBAR);
		move_cursor(ulr + rc, ulc + width - 1);
		DISP(VBAR);
	}

	/* Bottom row */
	move_cursor(ulr + (height - 1), ulc);
	DISP(LL);
	for (rc = 0; rc < width - 2; rc++)
		DISP(HBAR);
	DISP(LR);

}
void get_map_param() {
	//Prompt for dimensions data and scan in data
	printf("Please enter the number of horizontal and vertical buildings you would like in your map:");
	scanf_s("%d %d", &num_of_h_buildings, &num_of_v_buildings);
	//move_cursor(23, 50);
	printf("Please enter the number of starting coordinate of the map:");
	scanf_s("%d %d", &map_x, &map_y);
	//move_cursor(24, 50);
	printf("Please enter the building scale you want:");
	scanf_s("%d", &building_scale);
}
void create_buildings(void) {
	//set the mapscale
	int map_width = ((building_scale * num_of_h_buildings) + ((num_of_h_buildings + 1) * (2))) + 2;
	int map_height = ((((building_scale / 2) + 1) * num_of_v_buildings) + ((num_of_v_buildings + 1) * (2))) + 2;
	int num_of_streets = num_of_h_buildings + 1;
	int num_of_avenues = num_of_v_buildings + 1;

	//boundary_col_check1 = map_y;
	//boundary_row_check1 = map_x;
	//boundary_col_check2 = map_width;
	//boundary_row_check2 = map_height;

	//draw the outer border of the map
	draw_map_boundary(map_x, map_y, map_width, map_height);

	//intiate map coordinates for first_taxi building
	int x = map_x + 3, y = map_y + 3, x_0 = map_x + 3, y_0 = map_y + 3;

	int j = 0, b = 0;
	while (j < num_of_v_buildings) {
		int i = 0;
		while (i < num_of_h_buildings) {
			//draw horizontal buildings
			draw_box(x, y, building_scale);
			buildings[b].location.row = x;
			buildings[b].location.col = y;
			buildings[b].location.avenue = j;
			buildings[b].location.street = i;
			buildings[b].building_num = building_num + 1;

			buildings[b].NW.row = x; buildings[b].NW.col = y;
			buildings[b].NE.row = x; buildings[b].NE.col = y + (building_scale - 1);
			buildings[b].SW.row = x + (building_scale / 2); buildings[b].SW.col = y;
			buildings[b].SE.row = x + (building_scale / 2);	buildings[b].SE.col = y + (building_scale - 1);

			y = y + (building_scale + 2);
			i++; building_num++; b++;
		}

		x = x + ((building_scale / 2) + 3);
		y = y_0;
		j++;
	}
	num_of_buildings = building_num;
}

void taxi_at_origin() {
	switch (req_ptr->pick_up_corner) {
	case NW:
		//move cursor to taxi starting position
		move_cursor((*ptr).start.row, (*ptr).start.col);
		PRINT((*ptr).vin - 1000); //show taxi on the map
		(*ptr).location.col = (*ptr).start.col;
		(*ptr).location.row = (*ptr).start.row;
		(*ptr).col_state = FALSE;
		(*ptr).row_state = FALSE;
		break;
	case NE:
		//move cursor to taxi starting position
		move_cursor((*ptr).start.row, (*ptr).start.col);
		PRINT((*ptr).vin - 1000); //show taxi on the map
		(*ptr).location.col = (*ptr).start.col;
		(*ptr).location.row = (*ptr).start.row;
		(*ptr).col_state = FALSE;
		(*ptr).row_state = FALSE;
		break;
	case SW:
		//move cursor to taxi starting position
		move_cursor((*ptr).start.row, (*ptr).start.col);
		PRINT((*ptr).vin - 1000); //show taxi on the map
		(*ptr).location.col = (*ptr).start.col;
		(*ptr).location.row = (*ptr).start.row;
		(*ptr).col_state = FALSE;
		(*ptr).row_state = FALSE;
		break;
	case SE:
		//move cursor to taxi starting position
		move_cursor((*ptr).start.row, (*ptr).start.col);
		PRINT((*ptr).vin - 1000); //show taxi on the map
		(*ptr).location.col = (*ptr).start.col;
		(*ptr).location.row = (*ptr).start.row;
		(*ptr).col_state = FALSE;
		(*ptr).row_state = FALSE;
		break;
	}
	no_picked_passengers++;
	move_cursor(line1, 75);
	printf("Number of picked passengers = %d", no_picked_passengers);
	line1++;
	move_cursor(line1, 75);
	printf("%d PICKED = %d/%d", ptr->vin-1000, req_ptr->pid, ptr->passenger_id);
	line1++;
}

void move_down_to_start(int a) {
	//taxi reached its row destination
	if (((*ptr).location.row == (*ptr).start.row) && ((*ptr).location.col == (*ptr).start.col)) {
		req_ptr->p_state = PICKED;
	}
	else {

		//move cursor to previous row postion 
		move_cursor((*ptr).location.row, (*ptr).location.col);
		DISP(' '); //delete first_taxi taxi position

		//move cursor to next row postion after single clock cycle
		move_cursor((*ptr).location.row + 1, (*ptr).location.col);
		PRINT((*ptr).vin - 1000); //show taxi on the map

		//taxi reached its row destination
		if ((*ptr).location.row + 1 == (*ptr).start.row + a) {
			(*ptr).row_state_next_pass = TRUE;
			(*ptr).location.row = (*ptr).location.row + 1;

			if (((*ptr).location.row == (*ptr).start.row) && ((*ptr).location.col == (*ptr).start.col)) {
				req_ptr->p_state = PICKED;
			}
		}
		else {
			(*ptr).location.row++;
		}
	}
}
void move_up_to_start(int b) {
	//taxi reached its row destination
	if (((*ptr).location.row == (*ptr).start.row) && ((*ptr).location.col == (*ptr).start.col)) {
		req_ptr->p_state = PICKED;
	}
	else {
		//move cursor to previous row postion 
		move_cursor((*ptr).location.row, (*ptr).location.col);
		DISP(' '); //delete first_taxi taxi position

		//move cursor to next row postion after single clock cycle
		move_cursor((*ptr).location.row - 1, (*ptr).location.col);
		PRINT((*ptr).vin - 1000); //show taxi on the map

		//taxi reached its row destination
		if ((*ptr).location.row - 1 == (*ptr).start.row + b) {
			(*ptr).row_state_next_pass = TRUE;
			(*ptr).location.row = (*ptr).location.row - 1;
			if (((*ptr).location.row == (*ptr).start.row) && ((*ptr).location.col == (*ptr).start.col)) {
				req_ptr->p_state = PICKED;
			}
		}
		else {
			(*ptr).location.row--;
		}
	}
}
void move_right_to_start(int c) {
	if ((ptr->location.col == ptr->start.col) && (ptr->location.row == ptr->start.row)) {
		req_ptr->p_state = PICKED;
	}
	else {
		(*ptr).state = MOVING;

		//move cursor to previuous col postion 
		move_cursor((*ptr).location.row, (*ptr).location.col);
		DISP(' '); //delete first_taxi position taxi

		//move cursor to next col postion after single clock cycle
		move_cursor((*ptr).location.row, (*ptr).location.col + 1);
		PRINT((*ptr).vin - 1000); //show taxi on the map

		//taxi reached its row destination
		if ((*ptr).location.col + 1 == (*ptr).start.col + c) {
			(*ptr).col_state = TRUE;
			(*ptr).location.col = (*ptr).location.col + 1;
		}
		else {
			(*ptr).location.col++;
		}

		if ((req_ptr->drop_off_corner == SW) || (req_ptr->drop_off_corner == SE)) {
			if (ptr->col_state) {
				ptr->row_state_next_pass = FALSE;
			}
		}
	}
}
void move_left_to_start(int d) {
	if ((ptr->location.col == ptr->start.col) && (ptr->location.row == ptr->start.row)) {
		req_ptr->p_state = PICKED;
	}
	else {
		(*ptr).state = MOVING;

		//move cursor to previuous col postion 
		move_cursor((*ptr).location.row, (*ptr).location.col);
		DISP(' '); //delete first_taxi position taxi

		//move cursor to next col postion after single clock cycle
		move_cursor((*ptr).location.row, (*ptr).location.col - 1);
		PRINT((*ptr).vin - 1000); //show taxi on the map

		//taxi reached its row destination
		if ((*ptr).location.col - 1 == (*ptr).start.col + d) {
			(*ptr).col_state = TRUE;
			(*ptr).location.col = (*ptr).location.col - 1;
		}
		else {
			(*ptr).location.col--;
		}

		if ((req_ptr->drop_off_corner == NW) || (req_ptr->drop_off_corner == NE)) {
			if (ptr->col_state) {
				ptr->row_state_next_pass = FALSE;
			}
		}
	}
}

void move_down(int a) {
	//switch ((*req_ptr).drop_off_corner) {
	//case NW:
		//taxi reached its row destination
	if (((*ptr).location.row == (*ptr).stop.row) && ((*ptr).location.col == (*ptr).stop.col)) {
		req_ptr->p_state = DROPPED;
	}
	else {
		//if ((*ptr).location.row != boundary_col_check1) {
			//move cursor to previous row postion 
		move_cursor((*ptr).location.row, (*ptr).location.col);
		DISP(' '); //delete first_taxi taxi position
	//}

	//move cursor to next row postion after single clock cycle
		move_cursor((*ptr).location.row + 1, (*ptr).location.col);
		PRINT((*ptr).vin - 1000); //show taxi on the map

		//taxi reached its row destination
		if ((*ptr).location.row + 1 == (*ptr).stop.row + a) {
			(*ptr).row_state = TRUE;
			(*ptr).location.row = (*ptr).location.row + 1;

			if (((*ptr).location.row == (*ptr).stop.row) && ((*ptr).location.col == (*ptr).stop.col)) {
				//	req_ptr->p_state = DROPPED;
			}
		}
		else {
			(*ptr).location.row++;
		}
	}
}
void move_up(int b) {
	//switch ((*req_ptr).pick_up_corner) {
	//case NW:
		//taxi reached its row destination
	if (((*ptr).location.row == (*ptr).stop.row) && ((*ptr).location.col == (*ptr).stop.col)) {
		req_ptr->p_state = DROPPED;
	}
	else {
		//move cursor to previous row postion 
		move_cursor((*ptr).location.row, (*ptr).location.col);
		DISP(' '); //delete first_taxi taxi position

		//move cursor to next row postion after single clock cycle
		move_cursor((*ptr).location.row - 1, (*ptr).location.col);
		PRINT((*ptr).vin - 1000); //show taxi on the map

		//taxi reached its row destination
		if ((*ptr).location.row - 1 == (*ptr).stop.row + b) {
			(*ptr).row_state = TRUE;
			(*ptr).location.row = (*ptr).location.row - 1;
			//if (((*ptr).location.row == (*ptr).stop.row) && ((*ptr).location.col == (*ptr).stop.col)) {
				//req_ptr->p_state = DROPPED;
			//}
		}
		else {
			(*ptr).location.row--;
		}
	}
}
void move_right(int c) {
	if ((ptr->location.col == ptr->stop.col) && (ptr->location.row == ptr->stop.row)) {
		req_ptr->p_state = DROPPED;
	}
	else {
		(*ptr).state = MOVING;
		//switch ((*req_ptr).drop_off_corner) {
		//case NW:
			//move cursor to previuous col postion 
		move_cursor((*ptr).location.row, (*ptr).location.col);
		DISP(' '); //delete first_taxi position taxi

		//move cursor to next col postion after single clock cycle
		move_cursor((*ptr).location.row, (*ptr).location.col + 1);
		PRINT((*ptr).vin - 1000); //show taxi on the map

		//taxi reached its row destination
		if ((*ptr).location.col + 1 == (*ptr).stop.col + c) {
			(*ptr).col_state = TRUE;
			(*ptr).location.col = (*ptr).location.col + 1;
			if ((ptr->location.col == ptr->stop.col) && (ptr->location.row == ptr->stop.row)) {
				//				req_ptr->p_state = DROPPED;
			}
		}
		else {
			(*ptr).location.col++;
		}

		if ((req_ptr->drop_off_corner == SW) || (req_ptr->drop_off_corner == SE)) {
			if (ptr->col_state) {
				ptr->row_state = FALSE;
			}
		}
	}
}
void move_left(int d) {
	if ((ptr->location.col == ptr->stop.col) && (ptr->location.row == ptr->stop.row)) {
		req_ptr->p_state = DROPPED;
	}
	else {
		(*ptr).state = MOVING;
		//if (ptr->row_move > 0) {
			//switch ((*req_ptr).drop_off_corner) {
			//case NW:
				//move cursor to previuous col postion 
		move_cursor((*ptr).location.row, (*ptr).location.col);
		DISP(' '); //delete first_taxi position taxi

		//move cursor to next col postion after single clock cycle
		move_cursor((*ptr).location.row, (*ptr).location.col - 1);
		PRINT((*ptr).vin - 1000); //show taxi on the map

		//taxi reached its row destination
		if ((*ptr).location.col - 1 == (*ptr).stop.col + d) {
			(*ptr).col_state = TRUE;
			(*ptr).location.col = (*ptr).location.col - 1;
		}
		else {
			(*ptr).location.col--;
		}

		if ((req_ptr->drop_off_corner == NW) || (req_ptr->drop_off_corner == NE)) {
			if (ptr->col_state) {
				ptr->row_state = FALSE;
			}
		}
	}
}

void row_move(int a, int b) {
	if (ptr->taxi_pass_state == NEXT_PASS) {
		if (ptr->journey_state_next_pass == JOURNEY_1) {
			if ((*ptr).state == MOVING) {
				if ((*ptr).row_move_next_pass > 0) {
					move_down_to_start(a);
				}
				else {
					move_up_to_start(b);
				}
			}
			else {
				if ((*ptr).row_move > 0) {
					//move_down_to_start();
				}
				else {
					//move_up_to_start();
				}
			}
		}
		else {
			//if ((*ptr).state == MOVING) {
			if ((*ptr).row_move1 > 0) {
				move_down_tostart_j0();
			}
			else {
				move_up_tostart_j0();
			}
			//}

		}
	}
	else {
		if (ptr->journey_state == JOURNEY_1) {
			switch (req_ptr->drop_off_corner) {
			case SW:
				if ((*ptr).state == MOVING) {
					if ((*ptr).row_move > 0) {
						move_down(1);
					}
					else {
						move_up(b);
					}
				}
				else {
					if ((*ptr).row_move > 0) {
						//move_down_to_start();
					}
					else {
						//move_up_to_start();
					}
				}
				break;
			case SE:
				if ((*ptr).state == MOVING) {
					if ((*ptr).row_move > 0) {
						move_down(1);
					}
					else {
						move_up(b);
					}
				}
				else {
					if ((*ptr).row_move > 0) {
						//move_down_to_start();
					}
					else {
						//move_up_to_start();
					}
				}
				break;
			default:
				if ((*ptr).state == MOVING) {
					if ((*ptr).row_move > 0) {
						move_down(a);
					}
					else {
						move_up(b);
					}
				}
				else {
					if ((*ptr).row_move > 0) {
						//move_down_to_start();
					}
					else {
						//move_up_to_start();
					}
				}
				break;
			}
		}
		else {
			//if ((*ptr).state == MOVING) {
			if ((*ptr).row_move1 > 0) {
				move_down_j0();
			}
			else {
				move_up_j0();
			}
			//}

		}
	}

}


void convert_to_internal_map() {
	int i = 0;
	struct taxi* tmp;
	struct passenger_request* tmp1;
	tmp = mov_list_ptr;
	ptr = tmp;

	//int T = 0;

	tmp1 = accepted_req;
	req_ptr = tmp1;
	//enum building_corner corner;

	while (req_ptr) {
		if (ptr->state == IDLE) {
			int orig_r = FALSE, orig_c = FALSE;
			int dest_r = FALSE, dest_c = FALSE;
			int j = 0;
			while (j < num_of_buildings) {
				if (!orig_c && ((*req_ptr).origin.street == buildings[j].location.street)) {
					switch ((*req_ptr).pick_up_corner) {
					case NW:
						(*ptr).start.col = buildings[j].NW.col;
						break;
					case NE:
						(*ptr).start.col = buildings[j].NE.col;
						break;
					case SW:
						(*ptr).start.col = buildings[j].SW.col;
						break;
					case SE:
						(*ptr).start.col = buildings[j].SE.col;
						break;
					}
					orig_c = TRUE; //the origin column is set
				}
				if (!orig_r && ((*req_ptr).origin.avenue == buildings[j].location.avenue)) {
					switch ((*req_ptr).pick_up_corner) {
					case NW:
						(*ptr).start.row = buildings[j].NW.row;
						(*ptr).start.row--;
						break;
					case NE:
						(*ptr).start.row = buildings[j].NE.row;
						(*ptr).start.row--;
						break;
					case SW:
						(*ptr).start.row = buildings[j].SW.row;
						(*ptr).start.row++;
						break;
					case SE:
						(*ptr).start.row = buildings[j].SE.row;
						(*ptr).start.row++;
						break;
					}
					orig_r = TRUE;
				}
				if (!dest_c && ((*req_ptr).destination.street == buildings[j].location.street)) {
					switch ((*req_ptr).drop_off_corner) {
					case NW:
						(*ptr).stop.col = buildings[j].NW.col;
						break;
					case NE:
						(*ptr).stop.col = buildings[j].NE.col;
						break;
					case SW:
						(*ptr).stop.col = buildings[j].SW.col;
						break;
					case SE:
						(*ptr).stop.col = buildings[j].SE.col;
						break;
					}
					dest_c = TRUE;
				}
				if (!dest_r && ((*req_ptr).destination.avenue == buildings[j].location.avenue)) {
					switch ((*req_ptr).drop_off_corner) {
					case NW:
						(*ptr).stop.row = buildings[j].NW.row;
						(*ptr).stop.row--;
						break;
					case NE:
						(*ptr).stop.row = buildings[j].NE.row;
						(*ptr).stop.row--;
						break;
					case SW:
						(*ptr).stop.row = buildings[j].SW.row;
						(*ptr).stop.row++;
						break;
					case SE:
						(*ptr).stop.row = buildings[j].SE.row;
						(*ptr).stop.row++;
						break;
					}
					dest_r = TRUE;
				}
				if (orig_r == TRUE && orig_c == TRUE && dest_r == TRUE && dest_c == TRUE) {
					j = num_of_buildings;

				}
				j++;
			}
			ptr->row_state = ptr->col_state = 0;
			(*ptr).row_move = (*ptr).stop.row - (*ptr).start.row;
			(*ptr).col_move = (*ptr).stop.col - (*ptr).start.col;
						
			//set_route();
			if ((ptr->col_move < 0) && (req_ptr->origin.street != req_ptr->destination.street)) {
				//if (ptr->journey_state == JOURNEY_0) {
					switch (req_ptr->pick_up_corner) {
					case NW:
						ptr->start1.col = ptr->start.col;
						ptr->start1.row = ptr->start.row;

						if (ptr->row_move < 0) {
							ptr->stop1.col = ptr->start.col - 1;
							ptr->stop1.row = ptr->start.row - 1;
						}
						else {
							ptr->stop1.col = ptr->start.col - 2;
							ptr->stop1.row = ptr->start.row - 1;
						}

						ptr->row_state1 = ptr->col_state1 = 0;
						ptr->col_move1 = ptr->stop1.col - ptr->start1.col;
						ptr->row_move1 = ptr->stop1.row - ptr->start1.row;
						break;
					case NE:
						ptr->start1.col = ptr->start.col;
						ptr->start1.row = ptr->start.row;

						if (ptr->row_move < 0) {
							ptr->stop1.col = ptr->start.col - building_scale;
							ptr->stop1.row = ptr->start.row - 1;
						}
						else {
							ptr->stop1.col = ptr->start.col - (building_scale+1);
							ptr->stop1.row = ptr->start.row - 1;
						}

						ptr->row_state1 = ptr->col_state1 = 0;
						ptr->col_move1 = ptr->stop1.col - ptr->start1.col;
						ptr->row_move1 = ptr->stop1.row - ptr->start1.row;
						break;
					case SW:
						ptr->start1.col = ptr->start.col;
						ptr->start1.row = ptr->start.row;

						if (ptr->row_move < 0) {
							ptr->stop1.col = ptr->start.col - 1;
							ptr->stop1.row = ptr->start.row;
						}
						else {
							ptr->stop1.col = ptr->start.col - 2;
							ptr->stop1.row = ptr->start.row;
						}

						ptr->row_state1 = ptr->col_state1 = 0;
						ptr->col_move1 = ptr->stop1.col - ptr->start1.col;
						ptr->row_move1 = ptr->stop1.row - ptr->start1.row;
						break;
					case SE:
						ptr->start1.col = ptr->start.col;
						ptr->start1.row = ptr->start.row;

						if (ptr->row_move < 0) {
							ptr->stop1.col = ptr->start.col - (building_scale);
							ptr->stop1.row = ptr->start.row;
						}
						else {
							ptr->stop1.col = ptr->start.col - (building_scale+1);
							ptr->stop1.row = ptr->start.row;
						}

						ptr->row_state1 = ptr->col_state1 = 0;
						ptr->col_move1 = ptr->stop1.col - ptr->start1.col;
						ptr->row_move1 = ptr->stop1.row - ptr->start1.row;
						break;
					}
			}
			else if ((ptr->col_move > 0) && (req_ptr->origin.street != req_ptr->destination.street)) {
				switch (req_ptr->pick_up_corner) {
				case NW:
					ptr->start1.col = ptr->start.col;
					ptr->start1.row = ptr->start.row;

					if (ptr->row_move < 0) {
						ptr->stop1.col = ptr->start.col + (building_scale+1);
						ptr->stop1.row = ptr->start.row;
					}
					else {
						ptr->stop1.col = ptr->start.col + (building_scale);
						ptr->stop1.row = ptr->start.row;
					}

					ptr->row_state1 = ptr->col_state1 = 0;
					ptr->col_move1 = ptr->stop1.col - ptr->start1.col;
					ptr->row_move1 = ptr->stop1.row - ptr->start1.row;
					break;
				case NE:
					ptr->start1.col = ptr->start.col;
					ptr->start1.row = ptr->start.row;

					if (ptr->row_move < 0) {
						ptr->stop1.col = ptr->start.col + 2;
						ptr->stop1.row = ptr->start.row;
					}
					else {
						ptr->stop1.col = ptr->start.col + 1;
						ptr->stop1.row = ptr->start.row;
					}

					ptr->row_state1 = ptr->col_state1 = 0;
					ptr->col_move1 = ptr->stop1.col - ptr->start1.col;
					ptr->row_move1 = ptr->stop1.row - ptr->start1.row;
					break;
				case SW:
					ptr->start1.col = ptr->start.col;
					ptr->start1.row = ptr->start.row;

					if (ptr->row_move < 0) {
						ptr->stop1.col = ptr->start.col + (building_scale+1);
						ptr->stop1.row = ptr->start.row + 1;
					}
					else {
						ptr->stop1.col = ptr->start.col + (building_scale);
						ptr->stop1.row = ptr->start.row + 1;
					}

					ptr->row_state1 = ptr->col_state1 = 0;
					ptr->col_move1 = ptr->stop1.col - ptr->start1.col;
					ptr->row_move1 = ptr->stop1.row - ptr->start1.row;
					break;
				case SE:
					ptr->start1.col = ptr->start.col;
					ptr->start1.row = ptr->start.row;

					if (ptr->row_move < 0) {
						ptr->stop1.col = ptr->start.col + 2;
						ptr->stop1.row = ptr->start.row + 1;
					}
					else {
						ptr->stop1.col = ptr->start.col + 1;
						ptr->stop1.row = ptr->start.row + 1;
					}

					ptr->row_state1 = ptr->col_state1 = 0;
					ptr->col_move1 = ptr->stop1.col - ptr->start1.col;
					ptr->row_move1 = ptr->stop1.row - ptr->start1.row;
					break;
				}
			}
			else {
				switch (req_ptr->pick_up_corner) {
				case NW:
					ptr->start1.col = ptr->start.col;
					ptr->start1.row = ptr->start.row;

					if (ptr->row_move < 0) {
						ptr->stop1.col = ptr->start.col + (building_scale + 1);
						ptr->stop1.row = ptr->start.row;
					}
					else {
						ptr->stop1.col = ptr->start.col + (building_scale);
						ptr->stop1.row = ptr->start.row;
					}

					ptr->row_state1 = ptr->col_state1 = 0;
					ptr->col_move1 = ptr->stop1.col - ptr->start1.col;
					ptr->row_move1 = ptr->stop1.row - ptr->start1.row;
					break;
				case NE:
					ptr->start1.col = ptr->start.col;
					ptr->start1.row = ptr->start.row;

					if (ptr->row_move < 0) {
						ptr->stop1.col = ptr->start.col + 2;
						ptr->stop1.row = ptr->start.row;
					}
					else {
						ptr->stop1.col = ptr->start.col + 1;
						ptr->stop1.row = ptr->start.row;
					}

					ptr->row_state1 = ptr->col_state1 = 0;
					ptr->col_move1 = ptr->stop1.col - ptr->start1.col;
					ptr->row_move1 = ptr->stop1.row - ptr->start1.row;
					break;
				case SW:
					ptr->start1.col = ptr->start.col;
					ptr->start1.row = ptr->start.row;

					if (ptr->row_move < 0) {
						ptr->stop1.col = ptr->start.col + (building_scale + 1);
						ptr->stop1.row = ptr->start.row + 1;
					}
					else {
						ptr->stop1.col = ptr->start.col + (building_scale);
						ptr->stop1.row = ptr->start.row + 1;
					}

					ptr->row_state1 = ptr->col_state1 = 0;
					ptr->col_move1 = ptr->stop1.col - ptr->start1.col;
					ptr->row_move1 = ptr->stop1.row - ptr->start1.row;
					break;
				case SE:
					ptr->start1.col = ptr->start.col;
					ptr->start1.row = ptr->start.row;

					if (ptr->row_move < 0) {
						ptr->stop1.col = ptr->start.col + 2;
						ptr->stop1.row = ptr->start.row + 1;
					}
					else {
						ptr->stop1.col = ptr->start.col + 1;
						ptr->stop1.row = ptr->start.row + 1;
					}

					ptr->row_state1 = ptr->col_state1 = 0;
					ptr->col_move1 = ptr->stop1.col - ptr->start1.col;
					ptr->row_move1 = ptr->stop1.row - ptr->start1.row;
					break;
				}
			}

			if (ptr->col_move1 == 0)
				ptr->col_state1 = TRUE;

			if (ptr->row_move1 == 0)
				ptr->row_state1 = TRUE;

			if ((*ptr).taxi_pass_state == FIRST_PASS) {
				taxi_at_origin();
				(*ptr).state = MOVING;
			}

		}
		if (((*ptr).taxi_pass_state == NEXT_PASS) && (ptr->state == IDLE)) {
			//set_journey_to_start();
			(*ptr).state = MOVING;
			req_ptr->p_state = WAITING;
			
			ptr->col_move_next_pass = ptr->start.col - ptr->location.col;
			ptr->row_move_next_pass = ptr->start.row - ptr->location.row;
			
			if (ptr->col_move_next_pass < 0) {
				//if (ptr->journey_state == JOURNEY_0) {
				switch (ptr->corner_parked) {
				case NW:
					ptr->temp_start.col = ptr->location.col;
					ptr->temp_start.row = ptr->location.row;

					if (ptr->row_move_next_pass < 0) {
						ptr->temp_stop.col = ptr->location.col - 1;
						ptr->temp_stop.row = ptr->location.row - 1;
					}
					else {
						ptr->temp_stop.col = ptr->location.col - 2;
						ptr->temp_stop.row = ptr->location.row - 1;
					}

					ptr->row_state_next_pass1 = ptr->col_state_next_pass1 = 0;
					ptr->col_move_next_pass1 = ptr->temp_stop.col - ptr->temp_start.col;
					ptr->row_move_next_pass1 = ptr->temp_stop.row - ptr->temp_start.row;
					break;
				case NE:
					ptr->temp_start.col = ptr->location.col;
					ptr->temp_start.row = ptr->location.row;

					if (ptr->row_move_next_pass < 0) {
						ptr->temp_stop.col = ptr->location.col - building_scale;
						ptr->temp_stop.row = ptr->location.row - 1;
					}
					else {
						ptr->temp_stop.col = ptr->location.col - (building_scale + 1);
						ptr->temp_stop.row = ptr->location.row - 1;
					}

					ptr->row_state_next_pass1 = ptr->col_state_next_pass1 = 0;
					ptr->col_move_next_pass1 = ptr->temp_stop.col - ptr->temp_start.col;
					ptr->row_move_next_pass1 = ptr->temp_stop.row - ptr->temp_start.row;
					break;
				case SW:
					ptr->temp_start.col = ptr->location.col;
					ptr->temp_start.row = ptr->location.row;

					if (ptr->row_move_next_pass < 0) {
						ptr->temp_stop.col = ptr->location.col - 1;
						ptr->temp_stop.row = ptr->location.row;
					}
					else {
						ptr->temp_stop.col = ptr->location.col - 2;
						ptr->temp_stop.row = ptr->location.row;
					}

					ptr->row_state_next_pass1 = ptr->col_state_next_pass1 = 0;
					ptr->col_move_next_pass1 = ptr->temp_stop.col - ptr->temp_start.col;
					ptr->row_move_next_pass1 = ptr->temp_stop.row - ptr->temp_start.row;
					break;
				case SE:
					ptr->temp_start.col = ptr->location.col;
					ptr->temp_start.row = ptr->location.row;

					if (ptr->row_move_next_pass < 0) {
						ptr->temp_stop.col = ptr->location.col - (building_scale);
						ptr->temp_stop.row = ptr->location.row;
					}
					else {
						ptr->temp_stop.col = ptr->location.col - (building_scale + 1);
						ptr->temp_stop.row = ptr->location.row;
					}

					ptr->row_state_next_pass1 = ptr->col_state_next_pass1 = 0;
					ptr->col_move_next_pass1 = ptr->temp_stop.col - ptr->temp_start.col;
					ptr->row_move_next_pass1 = ptr->temp_stop.row - ptr->temp_start.row;
					break;
				}
			}
			else {
				switch (ptr->corner_parked) {
				case NW:
					ptr->temp_start.col = ptr->location.col;
					ptr->temp_start.row = ptr->location.row;

					if (ptr->row_move_next_pass < 0) {
						ptr->temp_stop.col = ptr->location.col + (building_scale + 1);
						ptr->temp_stop.row = ptr->location.row;
					}
					else {
						ptr->temp_stop.col = ptr->location.col + (building_scale);
						ptr->temp_stop.row = ptr->location.row;
					}

					ptr->row_state_next_pass1 = ptr->col_state_next_pass1 = 0;
					ptr->col_move_next_pass1 = ptr->temp_stop.col - ptr->temp_start.col;
					ptr->row_move_next_pass1 = ptr->temp_stop.row - ptr->temp_start.row;
					break;
				case NE:
					ptr->temp_start.col = ptr->location.col;
					ptr->temp_start.row = ptr->location.row;

					if (ptr->row_move_next_pass < 0) {
						ptr->temp_stop.col = ptr->location.col + 2;
						ptr->temp_stop.row = ptr->location.row;
					}
					else {
						ptr->temp_stop.col = ptr->location.col + 1;
						ptr->temp_stop.row = ptr->location.row;
					}

					ptr->row_state_next_pass1 = ptr->col_state_next_pass1 = 0;
					ptr->col_move_next_pass1 = ptr->temp_stop.col - ptr->temp_start.col;
					ptr->row_move_next_pass1 = ptr->temp_stop.row - ptr->temp_start.row;
					break;
				case SW:
					ptr->temp_start.col = ptr->location.col;
					ptr->temp_start.row = ptr->location.row;

					if (ptr->row_move_next_pass < 0) {
						ptr->temp_stop.col = ptr->location.col + (building_scale + 1);
						ptr->temp_stop.row = ptr->location.row + 1;
					}
					else {
						ptr->temp_stop.col = ptr->location.col + (building_scale);
						ptr->temp_stop.row = ptr->location.row + 1;
					}

					ptr->row_state_next_pass1 = ptr->col_state_next_pass1 = 0;
					ptr->col_move_next_pass1 = ptr->temp_stop.col - ptr->temp_start.col;
					ptr->row_move_next_pass1 = ptr->temp_stop.row - ptr->temp_start.row;
					break;
				case SE:
					ptr->temp_start.col = ptr->location.col;
					ptr->temp_start.row = ptr->location.row;

					if (ptr->row_move_next_pass < 0) {
						ptr->temp_stop.col = ptr->location.col + 2;
						ptr->temp_stop.row = ptr->location.row + 1;
					}
					else {
						ptr->temp_stop.col = ptr->location.col + 1;
						ptr->temp_stop.row = ptr->location.row + 1;
					}

					ptr->row_state_next_pass1 = ptr->col_state_next_pass1 = 0;
					ptr->col_move_next_pass1 = ptr->temp_stop.col - ptr->temp_start.col;
					ptr->row_move_next_pass1 = ptr->temp_stop.row - ptr->temp_start.row;
					break;
				}
			}

			if (ptr->col_move_next_pass == 0)
				ptr->col_state_next_pass = TRUE;

			if (ptr->row_move_next_pass == 0)
				ptr->row_state_next_pass = TRUE;
		}

		//(*ptr).state = MOVING;

		ptr = mov_list_ptr->next;
		mov_list_ptr = ptr;

		req_ptr = accepted_req->next;
		accepted_req = req_ptr;
		i++;
	}
	mov_list_ptr = ptr = tmp;
	accepted_req = req_ptr = tmp1;
}

void check_taxi() {
	const char* taxi_binaryfile = "taxi_binary.bin";

	/* open the relative / binary file for reading and writing*/
	FILE* vfd = fopen(taxi_binaryfile, "r+");

	/* read file sequentially */
	TAXI taxi_struct;
	TAXI_HEADER header_tax_rec;
	long rec_num;

	/*
		- position the file pointer to the start-of-file (header)
		- read the header record(aka zeroth record)
		  it indicates the first available passenger id */
	fseek(vfd, 0, SEEK_SET);
	fread(&header_tax_rec, sizeof(TAXI_HEADER), 1, vfd);

	rec_num = 1;

	while (rec_num < header_tax_rec.first_vin && fread(&taxi_struct, sizeof(TAXI), 1, vfd)) {
		ptr = (struct taxi*)malloc(sizeof(struct taxi));
		ptr->vin = taxi_struct.vin;
		ptr->battery_soc = taxi_struct.battery_soc;
		ptr->battery_capacity = taxi_struct.battery_capacity;
		ptr->charge_rate = taxi_struct.charge_rate;
		(*ptr).building_parked = taxi_struct.building_parked;
		(*ptr).corner_parked = taxi_struct.corner_parked;
		(*ptr).state = taxi_struct.state;
		(*ptr).distance = taxi_struct.distance;
		no_taxis++;

		if (!first_taxi) {
			first_taxi = ptr;
			last_taxi = ptr;
			ptr->next = NULL;
		}
		else {
			last_taxi->next = ptr;
			last_taxi = last_taxi->next;
			ptr->next = NULL;
		}
	}

	fclose(vfd); //close binary file
}

void check_requests() {
	const char* passenger_binaryfile = "passenger_binary.bin";

	/* open the relative / binary file for reading and writing*/
	FILE* pfd = fopen(passenger_binaryfile, "r+");

	/* read the file sequentially*/
	PASSENGER passeng_rec;
	HEADER header_pass_rec;
	long rec_num;


	/*
		- position the file pointer to the start-of-file (header)
		- read the header record(aka zeroth record)
			it indicates the first available passenger id */
	fseek(pfd, 0, SEEK_SET);
	fread(&header_pass_rec, sizeof(HEADER), 1, pfd);


	rec_num = 1;

	while (rec_num < header_pass_rec.first_id && fread(&passeng_rec, sizeof(PASSENGER), 1, pfd)) {
		if (passeng_rec.time_req == tick) {
			//free(req_ptr);
			req_ptr = (struct passenger_request*)malloc(sizeof(struct passenger_request));
			(*req_ptr).time_req = passeng_rec.time_req;
			(*req_ptr).origin.street = passeng_rec.origin.street;
			(*req_ptr).origin.avenue = passeng_rec.origin.avenue;
			(*req_ptr).pick_up_corner = passeng_rec.pick_up_corner;
			(*req_ptr).destination.street = passeng_rec.destination.street;
			(*req_ptr).destination.avenue = passeng_rec.destination.avenue;
			(*req_ptr).drop_off_corner = passeng_rec.drop_off_corner;
			(*req_ptr).status = passeng_rec.status;
			(*req_ptr).pid = passeng_rec.pid;
			no_of_req++;

			if (!first_req) {
				first_req = req_ptr;
				last_req = req_ptr;
				req_ptr->next = NULL;
			}
			else {
				last_req->next = req_ptr;
				last_req = last_req->next;
				req_ptr->next = NULL;
			}
		}
	}

	fclose(pfd); //close binary file
}

void find_building_parked_at(struct taxi* temp) {
	int i = 0;

	while (i < building_num) {
		switch (temp->corner_parked) {
		case NW:
			if ((temp->stop.col == buildings[i].NW.col) && (temp->stop.row == buildings[i].NW.row-1))
				temp->building_parked = buildings[i].building_num;
			break;
		case NE:
			if ((temp->stop.col == buildings[i].NE.col) && (temp->stop.row == buildings[i].NE.row-1))
				temp->building_parked = buildings[i].building_num;
			break;
		case SW:
			if ((temp->stop.col == buildings[i].SW.col) && (temp->stop.row == buildings[i].SW.row+1))
				temp->building_parked = buildings[i].building_num;
			break;
		case SE:
			if ((temp->stop.col == buildings[i].SE.col) && (temp->stop.row == buildings[i].SE.row+1))
				temp->building_parked = buildings[i].building_num;
			break;
		}
		i++;
	}
}

void find_building(struct passenger_request* temp) {
	int i = 0;

	while (i < building_num) {
		switch (temp->pick_up_corner) {
		case NW:
			if ((temp->origin.col == buildings[i].NW.col) && (temp->origin.row == buildings[i].NW.row - 1))
				temp->building_pickup = buildings[i].building_num;
			break;
		case NE:
			if ((temp->origin.col == buildings[i].NE.col) && (temp->origin.row == buildings[i].NE.row - 1))
				temp->building_pickup = buildings[i].building_num;
			break;
		case SW:
			if ((temp->origin.col == buildings[i].SW.col) && (temp->origin.row == buildings[i].SW.row + 1))
				temp->building_pickup = buildings[i].building_num;
			break;
		case SE:
			if ((temp->origin.col == buildings[i].SE.col) && (temp->origin.row == buildings[i].SE.row + 1))
				temp->building_pickup = buildings[i].building_num;
			break;
		}
		i++;
	}
}

void check_dest_reached() {
	struct taxi* tmp;
	struct passenger_request* tmp1, * curr1;
	struct taxi* curr;
	tmp = mov_list_ptr;
	curr = ptr = tmp;

	tmp1 = accepted_req;
	curr1 = req_ptr = tmp1;


	while (req_ptr) {
		if ((*req_ptr).p_state == DROPPED) { //TAXI HAS ARRIVED AT DESTINATION
			//if ((*ptr).vin == (*mov_list_ptr).vin) { //CURRENT TAXI IS FIRST TAXI
				(*ptr).state = IDLE; //TAXI IS NOW FREE
				(*ptr).row_state = (*ptr).col_state = 0;

				no_dropped_passengers++;
				move_cursor(line, 40);
				printf("Number of dropped passengers = %d", no_dropped_passengers);
				line++;
				move_cursor(line, 40);
				printf("%d DROPPED PASSENGER %d/%d", ptr->vin-1000, req_ptr->pid, ptr->passenger_id);
				line++;
				ptr->corner_parked = req_ptr->drop_off_corner;

				find_building_parked_at(ptr);


		if (ptr == mov_list_ptr) {
			//curr = ptr;
			mov_list_ptr = mov_list_ptr->next; //MOVE TAXI TO PARKING LIST
			ptr->next = park_list_ptr;
			park_list_ptr = ptr;
			//	curr = mov_list_ptr;
			tmp = mov_list_ptr;
			ptr = mov_list_ptr;

			//curr1 = req_ptr;
			accepted_req = accepted_req->next; //MOVE ACEPTED REQUEST TO COMPLETED REQUEST
			req_ptr->next = completed_req;
			completed_req = req_ptr;

			tmp1 = accepted_req;
			req_ptr = accepted_req;

			ptr = mov_list_ptr;
			mov_list_ptr = ptr;

			req_ptr = accepted_req;
			accepted_req = req_ptr;
		}
		else {
			//curr = ptr;
			mov_list_ptr->next = ptr->next; //MOVE TAXI TO PARKING LIST
			ptr->next = park_list_ptr;
			park_list_ptr = ptr;
			ptr = mov_list_ptr->next;
			//	curr = mov_list_ptr;


			//curr1 = req_ptr;
			accepted_req->next = req_ptr->next; //MOVE ACEPTED REQUEST TO COMPLETED REQUEST
			req_ptr->next = completed_req;
			completed_req = req_ptr;
			req_ptr = accepted_req->next;
		}
				//completed_req->next = req_ptr->next;
				//curr1 = accepted_req;
		//	}
			/*else {
				(*ptr).state = IDLE;
				(*ptr).row_state = (*ptr).col_state = 0;

				ptr->corner_parked = req_ptr->drop_off_corner;

				mov_list_ptr = mov_list_ptr->next;
				ptr->next = park_list_ptr;
				park_list_ptr = ptr;
				park_list_ptr->next = ptr->next;
				ptr = mov_list_ptr;

				accepted_req = accepted_req->next; //MOVE ACEPTED REQUEST TO COMPLETED REQUEST
				req_ptr->next = completed_req;
				completed_req = req_ptr;
				completed_req->next = req_ptr->next;
				req_ptr = accepted_req;
			}*/
			no_mov_list_taxi--;
			no_park_list_taxi++;

			no_of_completed_req++;

			
		}
		else {
			if (ptr) {
				mov_list_ptr = ptr;
				ptr = ptr->next;
				accepted_req = req_ptr;
				req_ptr = req_ptr->next;
			}
		}
	}
	mov_list_ptr = tmp;
	accepted_req = tmp1;
}

void match_req_to_taxi() {
	struct taxi* tmp;
	struct passenger_request* tmp1, * curr1;
	struct taxi* curr;
	tmp = mov_list_ptr;
	curr = ptr = tmp;
	int i = 0;

	tmp1 = accepted_req;
	curr1 = req_ptr = tmp1;

	int min = INT_MAX;

	if (first_req) {
		if (park_list_ptr) {
			if (no_park_list_taxi <= no_of_req) {
				ptr = park_list_ptr;
				req_ptr = first_req;
				while (req_ptr) {
					(*ptr).passenger_id = (*req_ptr).pid;
					(*ptr).state = IDLE;
					(*ptr).taxi_pass_state = NEXT_PASS;
					ptr->col_state_next_pass = ptr->row_state_next_pass = 0;
					(*req_ptr).p_state = WAITING;
					ptr->journey_state = JOURNEY_0;
					ptr->journey_state_next_pass = JOURNEY_0;

					find_building(req_ptr);

					curr = ptr;
					park_list_ptr = park_list_ptr->next;
					curr->next = mov_list_ptr;
					mov_list_ptr = curr;

					curr1 = req_ptr;
					first_req = first_req->next; 
					curr1->next = accepted_req;
					accepted_req = curr1;

					ptr = park_list_ptr;
					req_ptr = first_req;

					no_mov_list_taxi++;
					no_park_list_taxi--;
				}
			}
			else {
				if (first_taxi) {
					ptr = park_list_ptr;
					req_ptr = first_req;
					while (first_req) {

						(*ptr).passenger_id = (*req_ptr).pid;
						(*ptr).state = IDLE;
						(*ptr).taxi_pass_state = NEXT_PASS;
						ptr->col_state_next_pass = ptr->row_state_next_pass = 0;
						(*req_ptr).p_state = WAITING;
						ptr->journey_state = JOURNEY_0;
						ptr->journey_state_next_pass = JOURNEY_0;

						find_building(req_ptr);

						curr = ptr;
						first_taxi = first_taxi->next;
						curr->next = mov_list_ptr;
						mov_list_ptr = curr;

						curr1 = req_ptr;
						first_req = first_req->next;
						curr1->next = accepted_req;
						accepted_req = curr1;

						ptr = first_taxi;
						req_ptr = first_req;

						no_mov_list_taxi++;
						no_park_list_taxi--;
						wait_req_no--;
					}
				}
				else {
					req_ptr = first_req;
					while (first_req) {
						first_req = first_req->next;
						if (!waiting_req) {
							waiting_req = req_ptr;
							l_waiting_req = req_ptr;
							req_ptr->next = NULL;
						}
						else {
							l_waiting_req->next = req_ptr;
							l_waiting_req = l_waiting_req->next;
							req_ptr->next = NULL;
						}

						req_ptr = first_req;						
						wait_req_no++;
						no_of_req--;
					}
				}
			}
		}
		else if (first_taxi) {
			ptr = first_taxi;
			req_ptr = first_req;
			while (req_ptr) {
				if (first_taxi) {
					(*ptr).passenger_id = (*req_ptr).pid;
					(*ptr).state = IDLE;
					(*ptr).taxi_pass_state = FIRST_PASS;
					(*req_ptr).p_state = PICKED;
					ptr->journey_state = JOURNEY_0;

					find_building(req_ptr);

					curr = ptr;
					first_taxi = first_taxi->next; //MOVE TAXI TO PARKING LIST
					curr->next = mov_list_ptr;
					mov_list_ptr = curr;

					curr1 = req_ptr;
					first_req = first_req->next; //MOVE ACEPTED REQUEST TO COMPLETED REQUEST
					curr1->next = accepted_req;
					accepted_req = curr1;

					ptr = first_taxi;
					req_ptr = first_req;
					
					no_mov_list_taxi++;
					no_of_req--;
				}
				else {
					first_req = first_req->next;
					if (!waiting_req) {
						waiting_req = req_ptr;
						l_waiting_req = req_ptr;
						req_ptr->next = NULL;
					}
					else {
						l_waiting_req->next = req_ptr;
						l_waiting_req = l_waiting_req->next;
						req_ptr->next = NULL;
					}

					req_ptr = first_req;
					wait_req_no++;
					no_of_req--;
				}

				i++;
			}
		}
		else {
			req_ptr = first_req;
			while (first_req) {
				first_req = first_req->next;
				if (!waiting_req) {
					waiting_req = req_ptr;
					l_waiting_req = req_ptr;
					req_ptr->next = NULL;
				}
				else {
					l_waiting_req->next = req_ptr;
					l_waiting_req = l_waiting_req->next;
					req_ptr->next = NULL;
				}

				req_ptr = first_req;
				wait_req_no++;
				no_of_req--;
			}
		}
	}
	else if (waiting_req) {
		req_ptr = waiting_req;
		if (park_list_ptr) {
			if (no_park_list_taxi <= wait_req_no) {
				ptr = park_list_ptr;
				req_ptr = waiting_req;
				while (park_list_ptr) {
					(*ptr).passenger_id = (*req_ptr).pid;
					(*ptr).state = IDLE;
					(*ptr).taxi_pass_state = NEXT_PASS;
					ptr->col_state_next_pass = ptr->row_state_next_pass = 0;
					(*req_ptr).p_state = WAITING;
					ptr->journey_state = JOURNEY_0;
					ptr->journey_state_next_pass = JOURNEY_0;

					find_building(req_ptr);

					curr = ptr;
					park_list_ptr = park_list_ptr->next;
					curr->next = mov_list_ptr;
					mov_list_ptr = curr;

					curr1 = req_ptr;
					waiting_req = waiting_req->next;
					curr1->next = accepted_req;
					accepted_req = curr1;

					ptr = park_list_ptr;
					req_ptr = waiting_req;

					wait_req_no--;
					no_mov_list_taxi++;
					no_park_list_taxi--;
				}
			}
			else {
				if (first_taxi) {
					ptr = park_list_ptr;
					req_ptr = first_req;
					while (waiting_req) {
						(*ptr).passenger_id = (*req_ptr).pid;
						(*ptr).state = IDLE;
						(*ptr).taxi_pass_state = NEXT_PASS;
						ptr->col_state_next_pass = ptr->row_state_next_pass = 0;
						(*req_ptr).p_state = WAITING;
						ptr->journey_state = JOURNEY_0;
						ptr->journey_state_next_pass = JOURNEY_0;

						find_building(req_ptr);

						curr = ptr;
						first_taxi = first_taxi->next;
						curr->next = mov_list_ptr;
						mov_list_ptr = curr;

						curr1 = req_ptr;
						waiting_req = waiting_req->next;
						curr1->next = accepted_req;
						accepted_req = curr1;

						ptr = first_taxi;
						req_ptr = waiting_req;

						no_mov_list_taxi++;
						no_park_list_taxi--;
					}
				}				
			}
		}
		else if (first_taxi) {
			ptr = first_taxi;
			req_ptr = first_req;
			while (i < no_of_req) {
				if (first_taxi) {
					(*ptr).passenger_id = (*req_ptr).pid;
					(*ptr).state = IDLE;
					(*ptr).taxi_pass_state = FIRST_PASS;
					(*req_ptr).p_state = PICKED;
					ptr->journey_state = JOURNEY_0;

					find_building(req_ptr);

					curr = ptr;
					first_taxi = first_taxi->next;
					curr->next = mov_list_ptr;
					mov_list_ptr = curr;

					curr1 = req_ptr;
					waiting_req = waiting_req->next;
					curr1->next = accepted_req;
					accepted_req = curr1;

					ptr = first_taxi;
					req_ptr = waiting_req;

					no_mov_list_taxi++;
					no_of_req--;
				}				
				i++;
			}
		}		
	}
}

/*void move_taxis_to_start(int a, int b, int c, int d) {
	if (ptr->journey_state_next_pass == JOURNEY_1) {
		if ((*ptr).col_move_next_pass > 0) {
			if (ptr->temp_start.row == ptr->start.row) {
				switch (ptr->corner_parked) {
				case NW:
					move_right_to_start(0);
					break;
				case NE:
					move_right_to_start(0);
					break;
				case SW:
					if (!ptr->col_state_next_pass) {
						if (!ptr->row_state_next_pass) {
							row_move(1, 1);
						}
						else {
							move_right_to_start(0);
						}
					}
					else {
						row_move(0, 0);
					}
					break;
				case SE:
					if (!ptr->col_state_next_pass) {
						if (!ptr->row_state_next_pass) {
							row_move(1, 1);
						}
						else {
							move_right_to_start(0);
						}
					}
					else {
						row_move(0, 0);
					}
					break;
				}
			}
			else if (ptr->temp_start.row + 1 == ptr->start.row) {
				switch (ptr->corner_parked) {
				case NW:
					break;
				case NE:
					break;
				case SW:
					if (!ptr->row_state_next_pass) {
						row_move(0, 0);
					}
					else {
						move_right_to_start(0);
					}
					break;
				case SE:
					if (!ptr->row_state_next_pass) {
						row_move(0, 0);
					}
					else {
						move_right_to_start(0);
					}
					break;
				}
			}
			else if (ptr->temp_start.row - 1 == ptr->start.row) {
				switch (ptr->corner_parked) {
				case NW:
					if (!ptr->col_state_next_pass) {
						move_right_to_start(0);
					}
					else {
						row_move(0, 0);
					}
					break;
				case NE:
					if (!ptr->col_state_next_pass) {
						move_right_to_start(0);
					}
					else {
						row_move(0, 0);
					}
					break;
				case SW:
					break;
				case SE:
					break;
				}
			}
			else if ((ptr->temp_start.col + (building_scale - 1) == ptr->start.col) && (ptr->building_parked == req_ptr->building_pickup)) {
				switch (ptr->corner_parked) {
				case NW:
					switch (req_ptr->drop_off_corner) {
					case NE:
						if (!ptr->col_state_next_pass) {
							if (!(*ptr).row_state_next_pass) {
								row_move(-1, -1); //move right by one step
							}
							else {
								move_left_to_start(0);
							}
						}
						else {
							row_move(0, 0);
						}
						break;
					default:
						if (!(*ptr).row_state_next_pass) {
							row_move(0, 0); //move right by one step
						}
						else {
							move_left_to_start(0);
						}
						break;
					}
					break;
				default:
					switch (req_ptr->drop_off_corner) {
					case NE:
						if (!ptr->col_state) {
							if (!(*ptr).row_state_next_pass) {
								row_move(-1, -1); //move right by one step
							}
							else {
								move_left_to_start(0);
							}
						}
						else {
							row_move(0, 0);
						}
						break;
					default:
						if (!(*ptr).row_state_next_pass) {
							row_move(0, 0); //move right by one step
						}
						else {
							move_left_to_start(0);
						}
						break;
					}
					break;
				}
			}
			else if (ptr->temp_start.col - (building_scale - 1) == ptr->start.col) {
				switch (req_ptr->pick_up_corner) {
				case NW:
					if (!(*ptr).row_state_next_pass) {
						row_move(0, -1); //move right by one step
					}
					else {
						move_right_to_start(0);
					}
					break;
				case NE:
					if (!(*ptr).row_state_next_pass) {
						row_move(0, -1); //move right by one step
					}
					else {
						move_right_to_start(0);
					}
					break;
				default:
					if (!ptr->col_state_next_pass) {
						if (!(*ptr).row_state_next_pass) {
							row_move(0, 1); //move right by one step
						}
						else {
							move_right_to_start(0);
						}
					}
					else {
						row_move(0, 0);
					}
				}
			}
			else {
				switch (req_ptr->pick_up_corner) {
				case SW:
					if (!ptr->col_state_next_pass) {
						if (!(*ptr).row_state_next_pass) {
							row_move(1, 1);//move right by one step
						}
						else {
							move_right_to_start(0);
						}
					}
					else {
						row_move(0, 0);
					}
					break;
				case SE:
					if (!ptr->col_state_next_pass) {
						if (!(*ptr).row_state_next_pass) {
							row_move(1, 1);//move right by one step
						}
						else {
							move_right_to_start(0);
						}
					}
					else {
						row_move(0, 0);
					}
					break;
				default:
					if (!(*ptr).row_state_next_pass) {
						row_move(0, 0); //move right by one step
					}
					else {
						move_right_to_start(0);
					}
					break;
				}
			}
		}
		else if (ptr->col_move_next_pass) {
			if (ptr->temp_start.row == ptr->start.row) {
				switch (ptr->corner_parked) {
				case NW:
					if (!ptr->col_state_next_pass) {
						move_left_to_start(0);
					}
					else {
						row_move(0, 0);
					}
					break;
				case NE:
					if (!ptr->col_state_next_pass) {
						move_left_to_start(0);
					}
					else {
						row_move(0, 0);
					}
					break;
				case SW:
					move_left_to_start(0);
					break;
				case SE:
					move_left_to_start(0);
					break;
				}
			}
			else if (ptr->temp_start.row - 1 == ptr->start.row) {
				switch (ptr->corner_parked) {
				case NW:
					move_left_to_start(0);
					break;
				case NE:
					move_left_to_start(0);
					break;
				case SW:
					break;
				case SE:
					break;
				}
			}
			else if (ptr->temp_start.row + 1 == ptr->start.row) {
				switch (ptr->corner_parked) {
				case NW:
					break;
				case NE:
					break;
				case SW:
					if (!ptr->col_state_next_pass) {
						move_left_to_start(0);
					}
					else {
						row_move(0, 0);
					}
					break;
				case SE:
					if (!ptr->col_state_next_pass) {
						move_left_to_start(0);
					}
					else {
						row_move(0, 0);
					}
					break;
				}
			}
			else {
				switch (req_ptr->pick_up_corner) {
				case NW:
					if (!ptr->col_state_next_pass) {
						if (!(*ptr).row_state_next_pass) {
							row_move(-1, -1);
						}
						else {
							move_left_to_start(0);
						}
					}
					else {
						row_move(0, 0);
					}
					break;
				case NE:
					if (!ptr->col_state_next_pass) {
						if (!(*ptr).row_state_next_pass) {
							row_move(-1, -1);//move right by one step
						}
						else {
							move_left_to_start(0);
						}
					}
					else {
						row_move(0, 0);
					}
					break;
				default:
					if (!(*ptr).row_state_next_pass) {
						row_move(0, 0); //move right by one step
					}
					else {
						move_left_to_start(0);
					}
					break;
				}
			}
		}
		else {
			if (ptr->row_move_next_pass > 0) {
				switch (req_ptr->pick_up_corner) {
				case NW:
					if (!(*ptr).row_state_next_pass) {
						row_move(0, 0);//move right by one step
					}
					else {
						move_right_to_start(0);
					}
					break;
				case NE:
					if (!(*ptr).row_state_next_pass) {
						row_move(0, 0);//move right by one step
					}
					else {
						move_right_to_start(0);
					}
					break;
				case SW:
					if (!ptr->col_state_next_pass) {
						if (!(*ptr).row_state_next_pass) {
							row_move(0, 1);
						}
						else {
							move_right_to_start(0);
						}
					}
					else {
						move_up_to_start(0);
					}
					break;
				case SE:
					if (!ptr->col_state_next_pass) {
						if (!(*ptr).row_state_next_pass) {
							row_move(0, 1);//move right by one step
						}
						else {
							move_right_to_start(0);
						}
					}
					else {
						move_up_to_start(0);
					}
					break;
				}
			}
		}
	}
	else {
		if ((*ptr).col_move_next_pass1 > 0) {
			switch (ptr->corner_parked) {
			case NW:
				move_right_tostart_j0();
				break;
			case NE:
				move_right_tostart_j0();
				break;
			case SW:
				if (!(*ptr).row_state_next_pass1) {
					move_down_tostart_j0(); //move right by one step
				}
				else {
					move_right_tostart_j0();
				}
				break;
			case SE:
				if (!(*ptr).row_state_next_pass1) {
					row_move(0, 0); //move right by one step
				}
				else {
					move_right_tostart_j0();
				}
				break;
			}
		}
		else if (ptr->col_move_next_pass1 < 0) {
			switch (ptr->corner_parked) {
			case NW:
				if (!(*ptr).row_state_next_pass1) {
					row_move(a, b); //move up or down
				}
				else {
					move_left_tostart_j0();
				}
				break;
			case NE:
				if (!(*ptr).row_state_next_pass1) {
					row_move(a, b); //move up or down
				}
				else {
					move_left_tostart_j0();
				}
				break;
			case SE:
				move_left_tostart_j0();
				break;
			case SW:
				move_left_tostart_j0();
				break;
			}
		}
		else {
			if (!(*ptr).col_state_next_pass1) {
				move_right_tostart_j0(); //move right by one step
			}
			else {

				if ((ptr->row_state_next_pass) && (ptr->temp_start.col != ptr->start.col)) {
					move_right_tostart_j0();
				}
				else {
					row_move(a, b); //move up or down
				}
			}
		}
	}
}
*/
/*void move_taxis(int a, int b, int c, int d) {
	if (ptr->journey_state == JOURNEY_1) {
		if ((*ptr).col_move > 0) {
			if (ptr->start.row == ptr->stop.row) {
				switch (req_ptr->pick_up_corner) {
				case NW:
					move_right(0);
					break;
				case NE:
					move_right(0);
					break;
				case SW:
					if (!ptr->col_state) {
						if (!ptr->row_state) {
							row_move(1, 1);
						}
						else {
							move_right(0);
						}
					}
					else {
						row_move(0, 0);
					}
					break;
				case SE:
					if (!ptr->col_state) {
						if (!ptr->row_state) {
							row_move(1, 1);
						}
						else {
							move_right(0);
						}
					}
					else {
						row_move(0, 0);
					}
					break;
				}
			}
			else if (ptr->start.row + 1 == ptr->stop.row) {
				switch (req_ptr->pick_up_corner) {
				case NW:
					break;
				case NE:
					break;
				case SW:
					if (!ptr->row_state) {
						row_move(0, 0);
					}
					else {
						move_right(0);
					}
					break;
				case SE:
					if (!ptr->row_state) {
						row_move(0, 0);
					}
					else {
						move_right(0);
					}
					break;
				}
			}
			else if (ptr->start.row - 1 == ptr->stop.row) {
				switch (req_ptr->pick_up_corner) {
				case NW:
					if (!ptr->col_state) {
						move_right(0);
					}
					else {
						row_move(0, 0);
					}
					break;
				case NE:
					if (!ptr->col_state) {
						move_right(0);
					}
					else {
						row_move(0, 0);
					}
					break;
				case SW:
					break;
				case SE:
					break;
				}
			}
			else if ((ptr->start.col + (building_scale - 1) == ptr->stop.col) && (ptr->building_parked == req_ptr->building_pickup)) {
				switch (req_ptr->pick_up_corner) {
				case NW:
					switch (req_ptr->drop_off_corner) {
					case NE:
						if (!ptr->col_state) {
							if (!(*ptr).row_state) {
								row_move(-1, -1); //move right by one step
							}
							else {
								move_left(0);
							}
						}
						else {
							row_move(0, 0);
						}
						break;
					default:
						if (!(*ptr).row_state) {
							row_move(0, 0); //move right by one step
						}
						else {
							move_left(0);
						}
						break;
					}
					break;
				default:
					switch (req_ptr->drop_off_corner) {
					case NE:
						if (!ptr->col_state) {
							if (!(*ptr).row_state) {
								row_move(-1, -1); //move right by one step
							}
							else {
								move_left(0);
							}
						}
						else {
							row_move(0, 0);
						}
						break;
					default:
						if (!(*ptr).row_state) {
							row_move(0, 0); //move right by one step
						}
						else {
							move_left(0);
						}
						break;
					}
					break;
				}
			}
			else if (ptr->start.col - (building_scale - 1) == ptr->stop.col) {
				switch (req_ptr->drop_off_corner) {
				case NW:
					if (!(*ptr).row_state) {
						row_move(0, -1); //move right by one step
					}
					else {
						move_right(0);
					}
					break;
				case NE:
					if (!(*ptr).row_state) {
						row_move(0, -1); //move right by one step
					}
					else {
						move_right(0);
					}
					break;
				default:
					if (!ptr->col_state) {
						if (!(*ptr).row_state) {
							row_move(0, 1); //move right by one step
						}
						else {
							move_right(0);
						}
					}
					else {
						row_move(0, 0);
					}
				}
			}
			else if ((*ptr).col_move > 0) {
				switch (req_ptr->drop_off_corner) {
				case SW:
					if (!ptr->col_state) {
						if (!(*ptr).row_state) {
							row_move(1, 1);//move right by one step
						}
						else {
							move_right(0);
						}
					}
					else {
						row_move(0, 0);
					}
					break;
				case SE:
					if (!ptr->col_state) {
						if (!(*ptr).row_state) {
							row_move(1, 1);//move right by one step
						}
						else {
							move_right(0);
						}
					}
					else {
						row_move(0, 0);
					}
					break;
				default:
					if (!(*ptr).row_state) {
						row_move(0, 0); //move right by one step
					}
					else {
						move_right(0);
					}
					break;
				}
			}
		}
		else if (ptr->col_move < 0) {
			if (ptr->start.row == ptr->stop.row) {
				switch (req_ptr->pick_up_corner) {
				case NW:
					if (!ptr->col_state) {
						move_left(0);
					}
					else {
						move_down(0);
					}
					break;
				case NE:
					if (!ptr->col_state) {
						move_left(0);
					}
					else {
						move_down(0);
					}
					break;
				case SW:
					move_left(0);
					break;
				case SE:
					move_left(0);
					break;
				}
			}
			else if (ptr->start.row - 1 == ptr->stop.row) {
				switch (req_ptr->pick_up_corner) {
				case NW:
					move_left(0);
					break;
				case NE:
					move_left(0);
					break;
				case SW:
					break;
				case SE:
					break;
				}
			}
			else if (ptr->start.row + 1 == ptr->stop.row) {
				switch (req_ptr->pick_up_corner) {
				case NW:
					break;
				case NE:
					break;
				case SW:
					if (!ptr->col_state) {
						move_left(0);
					}
					else {
						row_move(0, 0);
					}
					break;
				case SE:
					if (!ptr->col_state) {
						move_left(0);
					}
					else {
						row_move(0, 0);
					}
					break;
				}
			}
			else {
				switch (req_ptr->drop_off_corner) {
				case NW:
					if (!ptr->col_state) {
						if (!(*ptr).row_state) {
							row_move(-1, -1);
						}
						else {
							move_left(0);
						}
					}
					else {
						row_move(0, 0);
					}
					break;
				case NE:
					if (!ptr->col_state) {
						if (!(*ptr).row_state) {
							row_move(-1, -1);//move right by one step
						}
						else {
							move_left(0);
						}
					}
					else {
						row_move(0, 0);
					}
					break;
				default:
					if (!(*ptr).row_state) {
						row_move(0, 0); //move right by one step
					}
					else {
						move_left(0);
					}
					break;
				}
			}
		}
		else {
			if (ptr->row_move > 0) {
				switch (req_ptr->drop_off_corner) {
				case NW:
					if (!(*ptr).row_state) {
						row_move(0, 0);//move right by one step
					}
					else {
						move_right(0);
					}
					break;
				case NE:
					if (!(*ptr).row_state) {
						row_move(0, 0);//move right by one step
					}
					else {
						move_right(0);
					}
					break;
				case SW:
					if (!ptr->col_state) {
						if (!(*ptr).row_state) {
							row_move(0, 1);
						}
						else {
							move_right(0);
						}
					}
					else {
						move_up(0);
					}
					break;
				case SE:
					if (!ptr->col_state_next_pass) {
						if (!(*ptr).row_state_next_pass) {
							row_move(0, 1);//move right by one step
						}
						else {
							move_right(0);
						}
					}
					else {
						move_up(0);
					}
					break;
				}
			}
		}
	}
	else {
		if ((*ptr).col_move1 > 0) {
			switch (req_ptr->pick_up_corner) {
			case NW:					
				move_right_j0();										
				break;
			case NE:
				move_right_j0();
				break;
			case SW:
				if (!(*ptr).row_state1) {
					move_down_j0(); //move right by one step
				}
				else {
					move_right_j0();
				}						
				break;
			case SE:
				if (!(*ptr).row_state1) {
					row_move(0, 0); //move right by one step
				}
				else {
					move_right_j0();
				}
				break;
			}
		}
		else if (ptr->col_move1 < 0) {
			switch (req_ptr->pick_up_corner) {
			case NW:
				if (!(*ptr).row_state1) {
					row_move(a, b); //move up or down
				}
				else {
					move_left_j0();
				}
				break;
			case NE:
				if (!(*ptr).row_state1) {
					row_move(a, b); //move up or down
				}
				else {
					move_left_j0();
				}
				break;
			case SE:
				move_left_j0();					
				break;
			case SW:
				move_left_j0();
				break;
			}
		}
		else {
			if (!(*ptr).col_state1) {
				move_right_j0(); //move right by one step
			}
			else {

				if ((ptr->row_state) && (ptr->location.col != ptr->stop.col)) {
					move_right_j0();
				}
				else {
					row_move(a, b); //move up or down
				}
			}
		}
	}
	
}*/

/*void move_taxis() {
	// Determine the direction of the first journey
	int row_direction = ptr->stop.row - ptr->start.row;
	int col_direction = ptr->stop.col - ptr->start.col;

	// Make first journey to the correct lane
	while (ptr->start.row != ptr->stop.row || ptr->start.col != ptr->stop.col) {
		// Move towards destination along row
		if (ptr->start.row != ptr->stop.row) {
			row_move(ptr, row_direction > 0 ? 1 : -1);
		}
		// Move towards destination along column
		if (ptr->start.col != ptr->stop.col) {
			move_right(ptr, col_direction > 0 ? 1 : -1);
		}
	}

	// Make second journey to the drop-off point
	int drop_off_row = req_ptr->destination.row;
	int drop_off_col = req_ptr->destination.col;

	while (ptr->start.row != drop_off_row || ptr->start.col != drop_off_col) {
		// Move towards drop-off point along row
		if (ptr->start.row != drop_off_row) {
			row_move(ptr, drop_off_row > ptr->start.row ? 1 : -1);
		}
		// Move towards drop-off point along column
		if (ptr->start.col != drop_off_col) {
			move_right(ptr, drop_off_col > ptr->start.col ? 1 : -1);
		}
	}
}
*/

void move_taxis_to_start(int a, int b, int c, int d) {
	if (ptr->journey_state_next_pass == JOURNEY_1) {
		if ((*ptr).col_move_next_pass > 0) {
			if (ptr->temp_start.row == ptr->start.row) {
				switch (ptr->corner_parked) {
				case NW:
					move_right_to_start(0);
					break;
				case NE:
					move_right_to_start(0);
					break;
				case SW:
					if (!ptr->col_state_next_pass) {
						if (!ptr->row_state_next_pass) {
							row_move(1, 1);
						}
						else {
							move_right_to_start(0);
						}
					}
					else {
						row_move(0, 0);
					}
					break;
				case SE:
					if (!ptr->col_state_next_pass) {
						if (!ptr->row_state_next_pass) {
							row_move(1, 1);
						}
						else {
							move_right_to_start(0);
						}
					}
					else {
						row_move(0, 0);
					}
					break;
				}
			}
			else if (ptr->temp_start.row + 1 == ptr->start.row) {
				switch (ptr->corner_parked) {
				case NW:
					break;
				case NE:
					break;
				case SW:
					if (!ptr->row_state_next_pass) {
						row_move(0, 0);
					}
					else {
						move_right_to_start(0);
					}
					break;
				case SE:
					if (!ptr->row_state_next_pass) {
						row_move(0, 0);
					}
					else {
						move_right_to_start(0);
					}
					break;
				}
			}
			else if (ptr->temp_start.row - 1 == ptr->start.row) {
				switch (ptr->corner_parked) {
				case NW:
					if (!ptr->col_state_next_pass) {
						move_right_to_start(0);
					}
					else {
						row_move(0, 0);
					}
					break;
				case NE:
					if (!ptr->col_state_next_pass) {
						move_right_to_start(0);
					}
					else {
						row_move(0, 0);
					}
					break;
				case SW:
					break;
				case SE:
					break;
				}
			}
			else if ((ptr->temp_start.col + (building_scale - 1) == ptr->start.col) && (ptr->building_parked == req_ptr->building_pickup)) {
				switch (ptr->corner_parked) {
				case NW:
					switch (req_ptr->drop_off_corner) {
					case NE:
						if (!ptr->col_state_next_pass) {
							if (!(*ptr).row_state_next_pass) {
								row_move(-1, -1); //move right by one step
							}
							else {
								move_left_to_start(0);
							}
						}
						else {
							row_move(0, 0);
						}
						break;
					default:
						if (!(*ptr).row_state_next_pass) {
							row_move(0, 0); //move right by one step
						}
						else {
							move_left_to_start(0);
						}
						break;
					}
					break;
				default:
					switch (req_ptr->drop_off_corner) {
					case NE:
						if (!ptr->col_state) {
							if (!(*ptr).row_state_next_pass) {
								row_move(-1, -1); //move right by one step
							}
							else {
								move_left_to_start(0);
							}
						}
						else {
							row_move(0, 0);
						}
						break;
					default:
						if (!(*ptr).row_state_next_pass) {
							row_move(0, 0); //move right by one step
						}
						else {
							move_left_to_start(0);
						}
						break;
					}
					break;
				}
			}
			else if (ptr->temp_start.col - (building_scale - 1) == ptr->start.col) {
				switch (req_ptr->pick_up_corner) {
				case NW:
					if (!(*ptr).row_state_next_pass) {
						row_move(0, -1); //move right by one step
					}
					else {
						move_right_to_start(0);
					}
					break;
				case NE:
					if (!(*ptr).row_state_next_pass) {
						row_move(0, -1); //move right by one step
					}
					else {
						move_right_to_start(0);
					}
					break;
				default:
					if (!ptr->col_state_next_pass) {
						if (!(*ptr).row_state_next_pass) {
							row_move(0, 1); //move right by one step
						}
						else {
							move_right_to_start(0);
						}
					}
					else {
						row_move(0, 0);
					}
				}
			}
			else {
				switch (req_ptr->pick_up_corner) {
				case SW:
					if (!ptr->col_state_next_pass) {
						if (!(*ptr).row_state_next_pass) {
							row_move(1, 1);//move right by one step
						}
						else {
							move_right_to_start(0);
						}
					}
					else {
						row_move(0, 0);
					}
					break;
				case SE:
					if (!ptr->col_state_next_pass) {
						if (!(*ptr).row_state_next_pass) {
							row_move(1, 1);//move right by one step
						}
						else {
							move_right_to_start(0);
						}
					}
					else {
						row_move(0, 0);
					}
					break;
				default:
					if (!(*ptr).row_state_next_pass) {
						row_move(0, 0); //move right by one step
					}
					else {
						move_right_to_start(0);
					}
					break;
				}
			}
		}
		else if (ptr->col_move_next_pass) {
			if (ptr->temp_start.row == ptr->start.row) {
				switch (ptr->corner_parked) {
				case NW:
					if (!ptr->col_state_next_pass) {
						move_left_to_start(0);
					}
					else {
						row_move(0, 0);
					}
					break;
				case NE:
					if (!ptr->col_state_next_pass) {
						move_left_to_start(0);
					}
					else {
						row_move(0, 0);
					}
					break;
				case SW:
					move_left_to_start(0);
					break;
				case SE:
					move_left_to_start(0);
					break;
				}
			}
			else if (ptr->temp_start.row - 1 == ptr->start.row) {
				switch (ptr->corner_parked) {
				case NW:
					move_left_to_start(0);
					break;
				case NE:
					move_left_to_start(0);
					break;
				case SW:
					break;
				case SE:
					break;
				}
			}
			else if (ptr->temp_start.row + 1 == ptr->start.row) {
				switch (ptr->corner_parked) {
				case NW:
					break;
				case NE:
					break;
				case SW:
					if (!ptr->col_state_next_pass) {
						move_left_to_start(0);
					}
					else {
						row_move(0, 0);
					}
					break;
				case SE:
					if (!ptr->col_state_next_pass) {
						move_left_to_start(0);
					}
					else {
						row_move(0, 0);
					}
					break;
				}
			}
			else {
				switch (req_ptr->pick_up_corner) {
				case NW:
					if (!ptr->col_state_next_pass) {
						if (!(*ptr).row_state_next_pass) {
							row_move(-1, -1);
						}
						else {
							move_left_to_start(0);
						}
					}
					else {
						row_move(0, 0);
					}
					break;
				case NE:
					if (!ptr->col_state_next_pass) {
						if (!(*ptr).row_state_next_pass) {
							row_move(-1, -1);//move right by one step
						}
						else {
							move_left_to_start(0);
						}
					}
					else {
						row_move(0, 0);
					}
					break;
				default:
					if (!(*ptr).row_state_next_pass) {
						row_move(0, 0); //move right by one step
					}
					else {
						move_left_to_start(0);
					}
					break;
				}
			}
		}
		else {
			if (ptr->row_move_next_pass > 0) {
				switch (req_ptr->pick_up_corner) {
				case NW:
					if (!(*ptr).row_state_next_pass) {
						row_move(0, 0);//move right by one step
					}
					else {
						move_right_to_start(0);
					}
					break;
				case NE:
					if (!(*ptr).row_state_next_pass) {
						row_move(0, 0);//move right by one step
					}
					else {
						move_right_to_start(0);
					}
					break;
				case SW:
					if (!ptr->col_state_next_pass) {
						if (!(*ptr).row_state_next_pass) {
							row_move(0, 1);
						}
						else {
							move_right_to_start(0);
						}
					}
					else {
						move_up_to_start(0);
					}
					break;
				case SE:
					if (!ptr->col_state_next_pass) {
						if (!(*ptr).row_state_next_pass) {
							row_move(0, 1);//move right by one step
						}
						else {
							move_right_to_start(0);
						}
					}
					else {
						move_up_to_start(0);
					}
					break;
				}
			}
		}
	}
	else {
		if ((*ptr).col_move_next_pass1 > 0) {
			switch (ptr->corner_parked) {
			case NW:
				move_right_tostart_j0();
				break;
			case NE:
				move_right_tostart_j0();
				break;
			case SW:
				if (!(*ptr).row_state_next_pass1) {
					move_down_tostart_j0(); //move right by one step
				}
				else {
					move_right_tostart_j0();
				}
				break;
			case SE:
				if (!(*ptr).row_state_next_pass1) {
					row_move(0, 0); //move right by one step
				}
				else {
					move_right_tostart_j0();
				}
				break;
			}
		}
		else if (ptr->col_move_next_pass1 < 0) {
			switch (ptr->corner_parked) {
			case NW:
				if (!(*ptr).row_state_next_pass1) {
					row_move(a, b); //move up or down
				}
				else {
					move_left_tostart_j0();
				}
				break;
			case NE:
				if (!(*ptr).row_state_next_pass1) {
					row_move(a, b); //move up or down
				}
				else {
					move_left_tostart_j0();
				}
				break;
			case SE:
				move_left_tostart_j0();
				break;
			case SW:
				move_left_tostart_j0();
				break;
			}
		}
		else {
			if (!(*ptr).col_state_next_pass1) {
				move_right_tostart_j0(); //move right by one step
			}
			else {

				if ((ptr->row_state_next_pass) && (ptr->temp_start.col != ptr->start.col)) {
					move_right_tostart_j0();
				}
				else {
					row_move(a, b); //move up or down
				}
			}
		}
	}
}

void move_taxis(int a, int b, int c, int d) {
	if (ptr->journey_state == JOURNEY_1) {
		if ((*ptr).col_move > 0) {
			if (ptr->start.row == ptr->stop.row) {
				switch (req_ptr->pick_up_corner) {
				case NW:
					move_right(0);
					break;
				case NE:
					move_right(0);
					break;
				case SW:
					if (!ptr->col_state) {
						if (!ptr->row_state) {
							row_move(1, 1);
						}
						else {
							move_right(0);
						}
					}
					else {
						row_move(0, 0);
					}
					break;
				case SE:
					if (!ptr->col_state) {
						if (!ptr->row_state) {
							row_move(1, 1);
						}
						else {
							move_right(0);
						}
					}
					else {
						row_move(0, 0);
					}
					break;
				}
			}
			else if (ptr->start.row + 1 == ptr->stop.row) {
				switch (req_ptr->pick_up_corner) {
				case NW:
					break;
				case NE:
					break;
				case SW:
					if (!ptr->row_state) {
						row_move(0, 0);
					}
					else {
						move_right(0);
					}
					break;
				case SE:
					if (!ptr->row_state) {
						row_move(0, 0);
					}
					else {
						move_right(0);
					}
					break;
				}
			}
			else if (ptr->start.row - 1 == ptr->stop.row) {
				switch (req_ptr->pick_up_corner) {
				case NW:
					if (!ptr->col_state) {
						move_right(0);
					}
					else {
						row_move(0, 0);
					}
					break;
				case NE:
					if (!ptr->col_state) {
						move_right(0);
					}
					else {
						row_move(0, 0);
					}
					break;
				case SW:
					break;
				case SE:
					break;
				}
			}
			else if ((ptr->start.col + (building_scale - 1) == ptr->stop.col) && (ptr->building_parked == req_ptr->building_pickup)) {
				switch (req_ptr->pick_up_corner) {
				case NW:
					switch (req_ptr->drop_off_corner) {
					case NE:
						if (!ptr->col_state) {
							if (!(*ptr).row_state) {
								row_move(-1, -1); //move right by one step
							}
							else {
								move_left(0);
							}
						}
						else {
							row_move(0, 0);
						}
						break;
					default:
						if (!(*ptr).row_state) {
							row_move(0, 0); //move right by one step
						}
						else {
							move_left(0);
						}
						break;
					}
					break;
				default:
					switch (req_ptr->drop_off_corner) {
					case NE:
						if (!ptr->col_state) {
							if (!(*ptr).row_state) {
								row_move(-1, -1); //move right by one step
							}
							else {
								move_left(0);
							}
						}
						else {
							row_move(0, 0);
						}
						break;
					default:
						if (!(*ptr).row_state) {
							row_move(0, 0); //move right by one step
						}
						else {
							move_left(0);
						}
						break;
					}
					break;
				}
			}
			else if (ptr->start.col - (building_scale - 1) == ptr->stop.col) {
				switch (req_ptr->drop_off_corner) {
				case NW:
					if (!(*ptr).row_state) {
						row_move(0, -1); //move right by one step
					}
					else {
						move_right(0);
					}
					break;
				case NE:
					if (!(*ptr).row_state) {
						row_move(0, -1); //move right by one step
					}
					else {
						move_right(0);
					}
					break;
				default:
					if (!ptr->col_state) {
						if (!(*ptr).row_state) {
							row_move(0, 1); //move right by one step
						}
						else {
							move_right(0);
						}
					}
					else {
						row_move(0, 0);
					}
				}
			}
			else if ((*ptr).col_move > 0) {
				switch (req_ptr->drop_off_corner) {
				case SW:
					if (!ptr->col_state) {
						if (!(*ptr).row_state) {
							row_move(1, 1);//move right by one step
						}
						else {
							move_right(0);
						}
					}
					else {
						row_move(0, 0);
					}
					break;
				case SE:
					if (!ptr->col_state) {
						if (!(*ptr).row_state) {
							row_move(1, 1);//move right by one step
						}
						else {
							move_right(0);
						}
					}
					else {
						row_move(0, 0);
					}
					break;
				default:
					if (!(*ptr).row_state) {
						row_move(0, 0); //move right by one step
					}
					else {
						move_right(0);
					}
					break;
				}
			}
		}
		else if (ptr->col_move < 0) {
			if (ptr->start.row == ptr->stop.row) {
				switch (req_ptr->pick_up_corner) {
				case NW:
					if (!ptr->col_state) {
						move_left(0);
					}
					else {
						move_down(0);
					}
					break;
				case NE:
					if (!ptr->col_state) {
						move_left(0);
					}
					else {
						move_down(0);
					}
					break;
				case SW:
					move_left(0);
					break;
				case SE:
					move_left(0);
					break;
				}
			}
			else if (ptr->start.row - 1 == ptr->stop.row) {
				switch (req_ptr->pick_up_corner) {
				case NW:
					move_left(0);
					break;
				case NE:
					move_left(0);
					break;
				case SW:
					break;
				case SE:
					break;
				}
			}
			else if (ptr->start.row + 1 == ptr->stop.row) {
				switch (req_ptr->pick_up_corner) {
				case NW:
					break;
				case NE:
					break;
				case SW:
					if (!ptr->col_state) {
						move_left(0);
					}
					else {
						row_move(0, 0);
					}
					break;
				case SE:
					if (!ptr->col_state) {
						move_left(0);
					}
					else {
						row_move(0, 0);
					}
					break;
				}
			}
			else {
				switch (req_ptr->drop_off_corner) {
				case NW:
					if (!ptr->col_state) {
						if (!(*ptr).row_state) {
							row_move(-1, -1);
						}
						else {
							move_left(0);
						}
					}
					else {
						row_move(0, 0);
					}
					break;
				case NE:
					if (!ptr->col_state) {
						if (!(*ptr).row_state) {
							row_move(-1, -1);//move right by one step
						}
						else {
							move_left(0);
						}
					}
					else {
						row_move(0, 0);
					}
					break;
				default:
					if (!(*ptr).row_state) {
						row_move(0, 0); //move right by one step
					}
					else {
						move_left(0);
					}
					break;
				}
			}
		}
		else {
			if (ptr->row_move > 0) {
				switch (req_ptr->drop_off_corner) {
				case NW:
					if (!(*ptr).row_state) {
						row_move(0, 0);//move right by one step
					}
					else {
						move_right(0);
					}
					break;
				case NE:
					if (!(*ptr).row_state) {
						row_move(0, 0);//move right by one step
					}
					else {
						move_right(0);
					}
					break;
				case SW:
					if (!ptr->col_state) {
						if (!(*ptr).row_state) {
							row_move(0, 1);
						}
						else {
							move_right(0);
						}
					}
					else {
						move_up(0);
					}
					break;
				case SE:
					if (!ptr->col_state_next_pass) {
						if (!(*ptr).row_state_next_pass) {
							row_move(0, 1);//move right by one step
						}
						else {
							move_right(0);
						}
					}
					else {
						move_up(0);
					}
					break;
				}
			}
		}
	}
	else {
		if ((*ptr).col_move1 > 0) {
			switch (req_ptr->pick_up_corner) {
			case NW:
				move_right_j0();
				break;
			case NE:
				move_right_j0();
				break;
			case SW:
				if (!(*ptr).row_state1) {
					move_down_j0(); //move right by one step
				}
				else {
					move_right_j0();
				}
				break;
			case SE:
				if (!(*ptr).row_state1) {
					row_move(0, 0); //move right by one step
				}
				else {
					move_right_j0();
				}
				break;
			}
		}
		else if (ptr->col_move1 < 0) {
			switch (req_ptr->pick_up_corner) {
			case NW:
				if (!(*ptr).row_state1) {
					row_move(a, b); //move up or down
				}
				else {
					move_left_j0();
				}
				break;
			case NE:
				if (!(*ptr).row_state1) {
					row_move(a, b); //move up or down
				}
				else {
					move_left_j0();
				}
				break;
			case SE:
				move_left_j0();
				break;
			case SW:
				move_left_j0();
				break;
			}
		}
		else {
			if (!(*ptr).col_state1) {
				move_right_j0(); //move right by one step
			}
			else {

				if ((ptr->row_state) && (ptr->location.col != ptr->stop.col)) {
					move_right_j0();
				}
				else {
					row_move(a, b); //move up or down
				}
			}
		}
	}

}


void init_taxi_movement() {
	int i = 0;
	int state = FALSE, row_state = FALSE;
	int y = 0;
	int next = 0, no_t_row_s = 0;
	int p = 0;
	int T = 0;
	int taxi_exist = 0;

	struct taxi* tmp;
	struct passenger_request* tmp1;



	check_requests();
	check_taxi();
	match_req_to_taxi();
	convert_to_internal_map();
	while (state == FALSE) { // state = false means taxi has not reached destination

		int no_t_row_s = 0; //number of taxis with true row state
		int q = 0;

		tmp = mov_list_ptr;
		ptr = mov_list_ptr;

		tmp1 = accepted_req;
		req_ptr = tmp1;

		while (ptr) {
			if ((ptr->taxi_pass_state == CURR_PASS) || (ptr->taxi_pass_state == FIRST_PASS)) {
				if ((ptr->location.col == ptr->stop.col) && (ptr->location.row == ptr->stop.row)) {
					req_ptr->p_state = DROPPED;
					ptr->taxi_pass_state = NO_PASS;
					ptr->state = PARKED;
					ptr->journey_state_next_pass = ptr->journey_state = JOURNEY_0;
				}
				else {					
					move_taxis(0, 0, 0, 0);
					ptr->battery_soc = ptr->battery_soc - 0.5;
					ptr->distance++;
				}
			}
			else if ((*ptr).taxi_pass_state == NEXT_PASS) {
				if (ptr->col_move == 0 && ptr->row_move == 0) {
					ptr->taxi_pass_state = CURR_PASS;
					ptr->row_state = TRUE;
					ptr->col_state = TRUE;
				}
				else {
					if ((ptr->location.col == ptr->start.col) && (ptr->location.row == ptr->start.row)) {
						req_ptr->p_state = PICKED;
						ptr->taxi_pass_state = CURR_PASS;
						ptr->journey_state_next_pass = ptr->journey_state = JOURNEY_0;
						no_picked_passengers++;
						move_cursor(line1, 75);
						printf("Number of picked passengers = %d", no_picked_passengers);
						line1++;
						move_cursor(line1, 75);
						printf("%d PICKED PASSNGER %d/%d", ptr->vin-1000, req_ptr->pid, ptr->passenger_id);
						line1++;
					}
					else {
						move_taxis_to_start(0, 0, 0, 0);;
						ptr->battery_soc = ptr->battery_soc - 0.5;
						ptr->distance++;
					}
				}
			}
				ptr = mov_list_ptr->next;
				mov_list_ptr = ptr;
				
				req_ptr = accepted_req->next;
				accepted_req = req_ptr;
				
			q++;
		}
		mov_list_ptr = tmp;
		accepted_req = tmp1;
			
		check_dest_reached(); //IF TAXI HAS REACHED DESTINATION MOVE TAXI TO PARKED LIST
			
		tick++;
		move_cursor(0, 40);
		printf("CLOCK TICK = %d", tick);

		check_requests(); //GET NEW REQUESTS FOR DESIGNATED TIME
		match_req_to_taxi(); //MOVE TAXIS TO MOVING LIST AND REQUESTS OR WAITING REQUESTS TO ACCEPTED REQUESTS

		convert_to_internal_map(); //SET START AND STOP COORDINATES FOR MOVING LIST TAXIS
			
		Sleep(250);
		if (!accepted_req && !first_req && !waiting_req) {
			state = TRUE;
		}
	}

	//display all taxis at their destinations incase they got deleted
	free(ptr);
	free(req_ptr);

}

void display_taxis() {
	ptr = mov_list_ptr;
	while (ptr) {
		mov_list_ptr = mov_list_ptr->next; //MOVE TAXI TO PARKING LIST
		ptr->next = taxis;
		taxis = ptr;
		
		ptr = mov_list_ptr;
	}

	ptr = first_taxi;
	while (ptr) {
		first_taxi = first_taxi->next; //MOVE TAXI TO PARKING LIST
		ptr->next = taxis;
		taxis = ptr;

		ptr = first_taxi;
	}

	ptr = park_list_ptr;
	while (ptr) {
		park_list_ptr = park_list_ptr->next; //MOVE TAXI TO PARKING LIST
		ptr->next = taxis;
		taxis = ptr;

		ptr = park_list_ptr;
	}

	ptr = taxis;
	while (ptr) {
		printf("VIN: %-6d battery state of charge:%-6d battery capacity:%-6d charge rate:%d\n",
		ptr->vin, ptr->battery_soc, ptr->battery_capacity, ptr->charge_rate);
		printf("building parked at:%-6d  corner parked at:%-6d  distance traveled: %d\n",
		ptr->building_parked, ptr->corner_parked, ptr->distance);

		ptr = ptr->next;
	}
}

void display_buildings() {

}

void init_sys() {
	create_buildings();
	init_taxi_movement();
	move_cursor(30, 0);
}

int main() {
	/*
	 - Examples of simple character graphics
	 - Must establish channel (stream) to Windows
	*/
	COORD scrsize;
	int row;
	int col;

	unsigned char ch;

	/* For console output via Windows */
	Console = GetStdHandle(STD_OUTPUT_HANDLE);
	/* Determine screen size */
	scrsize = GetLargestConsoleWindowSize(Console);

	int choice1 = 0;
	while (1) {
		printf("\nMenu 1\n\n");
		printf("1: Set Map parameters\n");
		printf("2: Add/Edit/Delete Requests\n");
		printf("3: Add/Edit/Delete/Display Taxis\n");
		printf("4: Run Simulation\n");
		printf("5: EXIT\n");
		printf("6: Display Taxis\n");
		scanf_s("%d", &choice1);

		switch (choice1)
		{
		case 1:/* Create map*/
			system("cls");
			get_map_param();
			break;
		case 2:/*Add request*/
			system("cls");
			passenger_control();
			break;
		case 3:/*Add taxi*/
			system("cls"); 
			taxi_control();
			break;
		case 4:/*Start simulation*/
			system("cls");
			tick = 1;
			init_sys();
			break;
		case 5:
			system("cls");
			printf("goodbye");
			break;
		case 6:
			system("cls");
			display_taxis();
			break;

		default:
			system("cls");
			printf("\nwrong choice.Enter Again");
			break;
		}

		if (choice1 == 5) {
			break;
		}

	}
	return 0;
}
