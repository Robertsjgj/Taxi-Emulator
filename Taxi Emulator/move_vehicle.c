#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "emulator.h"

void move_down_tostart_j0() {
	switch (ptr->corner_parked) {
	case NW:
		//taxi reached its row destination
		if (((*ptr).location.row == (*ptr).temp_stop.row) && ((*ptr).location.col == (*ptr).temp_stop.col)) {
			(*ptr).row_state_next_pass1 = TRUE;
			(*ptr).state = IDLE;
			ptr->journey_state_next_pass = JOURNEY_1;
		}
		else {
			//if ((*ptr).location.row != boundary_col_check1) {
				//move cursor to previous row postion 
			move_cursor((*ptr).location.row, (*ptr).location.col);
			DISP(' '); //delete last taxi position
		//}

		//move cursor to next row postion after single clock cycle
			move_cursor((*ptr).location.row + 1, (*ptr).location.col);
			PRINT((*ptr).vin - 1000); //show taxi on the map

			//taxi reached its row destination
			if ((*ptr).location.row + 1 == (*ptr).temp_stop.row) {
				(*ptr).row_state_next_pass1 = TRUE;
				(*ptr).location.row = (*ptr).location.row + 1;
				if (((*ptr).location.row == (*ptr).temp_stop.row) && ((*ptr).location.col == (*ptr).temp_stop.col)) {
					ptr->journey_state_next_pass = JOURNEY_1;
				}
			}
			else {
				(*ptr).location.row++;
			}
		}
		break;
	case NE:
		//taxi reached its row destination
		if (((*ptr).location.row == (*ptr).temp_stop.row) && ((*ptr).location.col == (*ptr).temp_stop.col)) {
			(*ptr).row_state_next_pass1 = TRUE;
			(*ptr).state = IDLE;
			ptr->journey_state_next_pass = JOURNEY_1;
		}
		else {
			//move cursor to previous row postion 
			move_cursor((*ptr).location.row, (*ptr).location.col);
			DISP(' '); //delete last taxi position

			//move cursor to next row postion after single clock cycle
			move_cursor((*ptr).location.row + 1, (*ptr).location.col);
			PRINT((*ptr).vin - 1000); //show taxi on the map

			//taxi reached its row destination
			if ((*ptr).location.row + 1 == (*ptr).temp_stop.row) {
				(*ptr).row_state_next_pass1 = TRUE;
				(*ptr).location.row = (*ptr).location.row + 1;
				if (((*ptr).location.row == (*ptr).temp_stop.row) && ((*ptr).location.col == (*ptr).temp_stop.col)) {
					ptr->journey_state_next_pass = JOURNEY_1;
				}
			}
			else {
				(*ptr).location.row++;
			}
		}
		break;
	case SW:
		//taxi reached its row destination
		if (((*ptr).location.row == (*ptr).temp_stop.row) && ((*ptr).location.col == (*ptr).temp_stop.col)) {
			(*ptr).row_state_next_pass1 = TRUE;
			(*ptr).state = IDLE;
			ptr->journey_state_next_pass = JOURNEY_1;
		}
		else {
			//move cursor to previous row postion 
			move_cursor((*ptr).location.row, (*ptr).location.col);
			DISP(' '); //delete last taxi position

			//move cursor to next row postion after single clock cycle
			move_cursor((*ptr).location.row + 1, (*ptr).location.col);
			PRINT((*ptr).vin - 1000); //show taxi on the map

			//taxi reached its row destination
			if ((*ptr).location.row + 1 == (*ptr).temp_stop.row) {
				(*ptr).row_state_next_pass1 = TRUE;
				(*ptr).location.row = (*ptr).location.row + 1;
				if (((*ptr).location.row == (*ptr).temp_stop.row) && ((*ptr).location.col == (*ptr).temp_stop.col)) {
					ptr->journey_state_next_pass = JOURNEY_1;
				}
			}
			else {
				(*ptr).location.row++;
			}
		}
		break;
	case SE:
		//taxi reached its row destination
		if (((*ptr).location.row == (*ptr).temp_stop.row) && ((*ptr).location.col == (*ptr).temp_stop.col)) {
			(*ptr).row_state_next_pass1 = TRUE;
			(*ptr).state = IDLE;
			ptr->journey_state_next_pass = JOURNEY_1;
		}
		else {
			//move cursor to previous row postion 
			move_cursor((*ptr).location.row, (*ptr).location.col);
			DISP(' '); //delete last taxi position

			//move cursor to next row postion after single clock cycle
			move_cursor((*ptr).location.row + 1, (*ptr).location.col);
			PRINT((*ptr).vin - 1000); //show taxi on the map

			//taxi reached its row destination
			if ((*ptr).location.row + 1 == (*ptr).temp_stop.row) {
				(*ptr).row_state_next_pass1 = TRUE;
				(*ptr).location.row = (*ptr).location.row + 1;
				if (((*ptr).location.row == (*ptr).temp_stop.row) && ((*ptr).location.col == (*ptr).temp_stop.col)) {
					ptr->journey_state_next_pass = JOURNEY_1;
				}
			}
			else {
				(*ptr).location.row++;
			}
		}
		break;
	}
	//if ((ptr->location.row == ptr->stop.row) && (ptr->journey_state == JOURNEY_1))
		//ptr->row_state = TRUE;


}
void move_up_tostart_j0() {

	switch (ptr->corner_parked) {
	case NW:
		//taxi reached its row destination
		if (((*ptr).location.row == (*ptr).temp_stop.row) && ((*ptr).location.col == (*ptr).temp_stop.col)) {
			(*ptr).row_state_next_pass1 = TRUE;
			(*ptr).state = IDLE;
			ptr->journey_state_next_pass = JOURNEY_1;
		}
		else {
			//move cursor to previous row postion 
			move_cursor((*ptr).location.row, (*ptr).location.col);
			DISP(' '); //delete last taxi position

			//move cursor to next row postion after single clock cycle
			move_cursor((*ptr).location.row - 1, (*ptr).location.col);
			PRINT((*ptr).vin - 1000); //show taxi on the map

			//taxi reached its row destination
			if ((*ptr).location.row - 1 == (*ptr).temp_stop.row) {
				(*ptr).row_state_next_pass1 = TRUE;
				(*ptr).location.row = (*ptr).location.row - 1;
				if (((*ptr).location.row == (*ptr).temp_stop.row) && ((*ptr).location.col == (*ptr).temp_stop.col)) {
					ptr->journey_state_next_pass = JOURNEY_1;
				}
			}
			else {
				(*ptr).location.row--;
			}
		}
		break;
	case NE:
		//taxi reached its row destination
		if (((*ptr).location.row == (*ptr).temp_stop.row) && ((*ptr).location.col == (*ptr).temp_stop.col)) {
			(*ptr).row_state_next_pass1 = TRUE;
			(*ptr).state = IDLE;
			ptr->journey_state_next_pass = JOURNEY_1;
		}
		else {
			//move cursor to previous row postion 
			move_cursor((*ptr).location.row, (*ptr).location.col);
			DISP(' '); //delete last taxi position

			//move cursor to next row postion after single clock cycle
			move_cursor((*ptr).location.row - 1, (*ptr).location.col);
			PRINT((*ptr).vin - 1000); //show taxi on the map

			//taxi reached its row destination
			if ((*ptr).location.row - 1 == (*ptr).temp_stop.row) {
				(*ptr).row_state_next_pass1 = TRUE;
				(*ptr).location.row = (*ptr).location.row - 1;
				if (((*ptr).location.row == (*ptr).temp_stop.row) && ((*ptr).location.col == (*ptr).temp_stop.col)) {
					ptr->journey_state_next_pass = JOURNEY_1;
				}
			}
			else {
				(*ptr).location.row--;
			}
		}
		break;
	case SW:
		//taxi reached its row destination
		if (((*ptr).location.row == (*ptr).temp_stop.row) && ((*ptr).location.col == (*ptr).temp_stop.col)) {
			(*ptr).row_state_next_pass1 = TRUE;
			(*ptr).state = IDLE;
			ptr->journey_state_next_pass = JOURNEY_1;
		}
		else {
			//move cursor to previous row postion 
			move_cursor((*ptr).location.row, (*ptr).location.col);
			DISP(' '); //delete last taxi position

			//move cursor to next row postion after single clock cycle
			move_cursor((*ptr).location.row - 1, (*ptr).location.col);
			PRINT((*ptr).vin - 1000); //show taxi on the map

			//taxi reached its row destination
			if ((*ptr).location.row - 1 == (*ptr).temp_stop.row) {
				(*ptr).row_state_next_pass1 = TRUE;
				(*ptr).location.row = (*ptr).location.row - 1;
				if (((*ptr).location.row == (*ptr).temp_stop.row) && ((*ptr).location.col == (*ptr).temp_stop.col)) {
					ptr->journey_state_next_pass = JOURNEY_1;
				}
			}
			else {
				(*ptr).location.row--;
			}
		}
		break;
	case SE:
		//taxi reached its row destination
		if (((*ptr).location.row == (*ptr).temp_stop.row) && ((*ptr).location.col == (*ptr).temp_stop.col)) {
			(*ptr).row_state_next_pass1 = TRUE;
			(*ptr).state = IDLE;
			ptr->journey_state_next_pass = JOURNEY_1;
		}
		else {
			//move cursor to previous row postion 
			move_cursor((*ptr).location.row, (*ptr).location.col);
			DISP(' '); //delete last taxi position

			//move cursor to next row postion after single clock cycle
			move_cursor((*ptr).location.row - 1, (*ptr).location.col);
			PRINT((*ptr).vin - 1000); //show taxi on the map

			//taxi reached its row destination
			if ((*ptr).location.row - 1 == (*ptr).temp_stop.row) {
				(*ptr).row_state_next_pass1 = TRUE;
				(*ptr).location.row = (*ptr).location.row - 1;
				if (((*ptr).location.row == (*ptr).temp_stop.row) && ((*ptr).location.col == (*ptr).temp_stop.col)) {
					ptr->journey_state_next_pass = JOURNEY_1;
				}
			}
			else {
				(*ptr).location.row--;
			}
		}
		break;
	}
	//if ((ptr->location.row == ptr->stop.row) && (ptr->journey_state == JOURNEY_1))
		//ptr->row_state = TRUE;

}
void move_right_tostart_j0() {
	if ((ptr->location.col == ptr->temp_stop.col) && (ptr->location.row == ptr->temp_stop.row)) {
		ptr->journey_state_next_pass = JOURNEY_1;
	}
	else {
		//(*ptr).state = MOVING;
		//switch ((*req_ptr).drop_off_corner) {
		//case NW:
			//move cursor to previuous col postion 
		move_cursor((*ptr).location.row, (*ptr).location.col);
		DISP(' '); //delete last position taxi

		//move cursor to next col postion after single clock cycle
		move_cursor((*ptr).location.row, (*ptr).location.col + 1);
		PRINT((*ptr).vin - 1000); //show taxi on the map

		//taxi reached its row destination
		if ((*ptr).location.col + 1 == (*ptr).temp_stop.col) {
			(*ptr).col_state_next_pass1 = TRUE;
			(*ptr).location.col = (*ptr).location.col + 1;

			if ((*ptr).location.row == (*ptr).temp_stop.row) {
				ptr->journey_state_next_pass = JOURNEY_1;
				ptr->col_state_next_pass = FALSE;
			}
		}
		else {
			(*ptr).location.col++;
		}
	}
	//if ((ptr->location.col == ptr->stop.col) && (ptr->journey_state == JOURNEY_1))
		//ptr->col_state = TRUE;
}
void move_left_tostart_j0() {
	if ((ptr->location.col == ptr->temp_stop.col) && (ptr->location.row == ptr->temp_stop.row)) {
		ptr->journey_state_next_pass = JOURNEY_1;
	}
	else {
		(*ptr).state = MOVING;

		//move cursor to previuous col postion 
		move_cursor((*ptr).location.row, (*ptr).location.col);
		DISP(' '); //delete last position taxi

		//move cursor to next col postion after single clock cycle
		move_cursor((*ptr).location.row, (*ptr).location.col - 1);
		PRINT((*ptr).vin - 1000); //show taxi on the map

		//taxi reached its row destination
		if ((*ptr).location.col - 1 == (*ptr).temp_stop.col) {
			(*ptr).col_state_next_pass1 = TRUE;
			(*ptr).location.col = (*ptr).location.col - 1;

			if ((*ptr).location.row == (*ptr).temp_stop.row)
				ptr->journey_state_next_pass = JOURNEY_1;
				ptr->col_state_next_pass = FALSE;
		}
		else {
			(*ptr).location.col--;
		}
	}
}

void move_down_j0() {
	switch ((*req_ptr).pick_up_corner) {
	case NW:
		//taxi reached its row destination
		if (((*ptr).location.row == (*ptr).stop1.row) && ((*ptr).location.col == (*ptr).stop1.col)) {
			(*ptr).row_state1 = TRUE;
			(*ptr).state = IDLE;
			ptr->journey_state = JOURNEY_1;
		}
		else {
			//if ((*ptr).location.row != boundary_col_check1) {
				//move cursor to previous row postion 
				move_cursor((*ptr).location.row, (*ptr).location.col);
				DISP(' '); //delete last taxi position
			//}

			//move cursor to next row postion after single clock cycle
			move_cursor((*ptr).location.row + 1, (*ptr).location.col);
			PRINT((*ptr).vin - 1000); //show taxi on the map

			//taxi reached its row destination
			if ((*ptr).location.row + 1 == (*ptr).stop1.row) {
				(*ptr).row_state1 = TRUE;
				(*ptr).location.row = (*ptr).location.row + 1;
				if (((*ptr).location.row == (*ptr).stop1.row) && ((*ptr).location.col == (*ptr).stop1.col)) {
					ptr->journey_state = JOURNEY_1;
				}
			}
			else {
				(*ptr).location.row++;
			}
		}
		break;
	case NE:
		//taxi reached its row destination
		if (((*ptr).location.row == (*ptr).stop1.row) && ((*ptr).location.col == (*ptr).stop1.col)) {
			(*ptr).row_state1 = TRUE;
			(*ptr).state = IDLE;
			ptr->journey_state = JOURNEY_1;
		}
		else {
			//move cursor to previous row postion 
			move_cursor((*ptr).location.row, (*ptr).location.col);
			DISP(' '); //delete last taxi position

			//move cursor to next row postion after single clock cycle
			move_cursor((*ptr).location.row + 1, (*ptr).location.col);
			PRINT((*ptr).vin - 1000); //show taxi on the map

			//taxi reached its row destination
			if ((*ptr).location.row + 1 == (*ptr).stop1.row) {
				(*ptr).row_state1 = TRUE;
				(*ptr).location.row = (*ptr).location.row + 1;
				if (((*ptr).location.row == (*ptr).stop1.row) && ((*ptr).location.col == (*ptr).stop1.col)) {
					ptr->journey_state = JOURNEY_1;
				}
			}
			else {
				(*ptr).location.row++;
			}
		}
		break;
	case SW:
		//taxi reached its row destination
		if (((*ptr).location.row == (*ptr).stop1.row) && ((*ptr).location.col == (*ptr).stop1.col)) {
			(*ptr).row_state1 = TRUE;
			(*ptr).state = IDLE;
			ptr->journey_state = JOURNEY_1;
		}
		else {
			//move cursor to previous row postion 
			move_cursor((*ptr).location.row, (*ptr).location.col);
			DISP(' '); //delete last taxi position

			//move cursor to next row postion after single clock cycle
			move_cursor((*ptr).location.row + 1, (*ptr).location.col);
			PRINT((*ptr).vin - 1000); //show taxi on the map

			//taxi reached its row destination
			if ((*ptr).location.row + 1 == (*ptr).stop1.row) {
				(*ptr).row_state1 = TRUE;
				(*ptr).location.row = (*ptr).location.row + 1;
				if (((*ptr).location.row == (*ptr).stop1.row) && ((*ptr).location.col == (*ptr).stop1.col)) {
					ptr->journey_state = JOURNEY_1;
				}
			}
			else {
				(*ptr).location.row++;
			}
		}
		break;
	case SE:
		//taxi reached its row destination
		if (((*ptr).location.row == (*ptr).stop1.row) && ((*ptr).location.col == (*ptr).stop1.col)) {
			(*ptr).row_state1 = TRUE;
			(*ptr).state = IDLE;
			ptr->journey_state = JOURNEY_1;
		}
		else {
			//move cursor to previous row postion 
			move_cursor((*ptr).location.row, (*ptr).location.col);
			DISP(' '); //delete last taxi position

			//move cursor to next row postion after single clock cycle
			move_cursor((*ptr).location.row + 1, (*ptr).location.col);
			PRINT((*ptr).vin - 1000); //show taxi on the map

			//taxi reached its row destination
			if ((*ptr).location.row + 1 == (*ptr).stop1.row) {
				(*ptr).row_state1 = TRUE;
				(*ptr).location.row = (*ptr).location.row + 1;
				if (((*ptr).location.row == (*ptr).stop1.row) && ((*ptr).location.col == (*ptr).stop1.col)) {
					ptr->journey_state = JOURNEY_1;
				}
			}
			else {
				(*ptr).location.row++;
			}
		}
		break;
	}
	//if ((ptr->location.row == ptr->stop.row) && (ptr->journey_state == JOURNEY_1))
		//ptr->row_state = TRUE;


}
void move_up_j0() {

	switch ((*req_ptr).pick_up_corner) {
	case NW:
		//taxi reached its row destination
		if (((*ptr).location.row == (*ptr).stop1.row) && ((*ptr).location.col == (*ptr).stop1.col)) {
			(*ptr).row_state1 = TRUE;
			(*ptr).state = IDLE;
			ptr->journey_state = JOURNEY_1;
		}
		else {
			//move cursor to previous row postion 
			move_cursor((*ptr).location.row, (*ptr).location.col);
			DISP(' '); //delete last taxi position

			//move cursor to next row postion after single clock cycle
			move_cursor((*ptr).location.row - 1, (*ptr).location.col);
			PRINT((*ptr).vin - 1000); //show taxi on the map

			//taxi reached its row destination
			if ((*ptr).location.row - 1 == (*ptr).stop1.row) {
				(*ptr).row_state1 = TRUE;
				(*ptr).location.row = (*ptr).location.row - 1;
				if (((*ptr).location.row == (*ptr).stop1.row) && ((*ptr).location.col == (*ptr).stop1.col)) {
					ptr->journey_state = JOURNEY_1;
				}
			}
			else {
				(*ptr).location.row--;
			}
		}
		break;
	case NE:
		//taxi reached its row destination
		if (((*ptr).location.row == (*ptr).stop1.row) && ((*ptr).location.col == (*ptr).stop1.col)) {
			(*ptr).row_state1 = TRUE;
			(*ptr).state = IDLE;
			ptr->journey_state = JOURNEY_1;
		}
		else {
			//move cursor to previous row postion 
			move_cursor((*ptr).location.row, (*ptr).location.col);
			DISP(' '); //delete last taxi position

			//move cursor to next row postion after single clock cycle
			move_cursor((*ptr).location.row - 1, (*ptr).location.col);
			PRINT((*ptr).vin - 1000); //show taxi on the map

			//taxi reached its row destination
			if ((*ptr).location.row - 1 == (*ptr).stop1.row) {
				(*ptr).row_state1 = TRUE;
				(*ptr).location.row = (*ptr).location.row - 1;
				if (((*ptr).location.row == (*ptr).stop1.row) && ((*ptr).location.col == (*ptr).stop1.col)) {
					ptr->journey_state = JOURNEY_1;
				}
			}
			else {
				(*ptr).location.row--;
			}
		}
		break;
	case SW:
		//taxi reached its row destination
		if (((*ptr).location.row == (*ptr).stop1.row) && ((*ptr).location.col == (*ptr).stop1.col)) {
			(*ptr).row_state1 = TRUE;
			(*ptr).state = IDLE;
			ptr->journey_state = JOURNEY_1;
		}
		else {
			//move cursor to previous row postion 
			move_cursor((*ptr).location.row, (*ptr).location.col);
			DISP(' '); //delete last taxi position

			//move cursor to next row postion after single clock cycle
			move_cursor((*ptr).location.row - 1, (*ptr).location.col);
			PRINT((*ptr).vin - 1000); //show taxi on the map

			//taxi reached its row destination
			if ((*ptr).location.row - 1 == (*ptr).stop1.row) {
				(*ptr).row_state1 = TRUE;
				(*ptr).location.row = (*ptr).location.row - 1;
				if (((*ptr).location.row == (*ptr).stop1.row) && ((*ptr).location.col == (*ptr).stop1.col)) {
					ptr->journey_state = JOURNEY_1;
				}
			}
			else {
				(*ptr).location.row--;
			}
		}
		break;
	case SE:
		//taxi reached its row destination
		if (((*ptr).location.row == (*ptr).stop1.row) && ((*ptr).location.col == (*ptr).stop1.col)) {
			(*ptr).row_state1 = TRUE;
			(*ptr).state = IDLE;
			ptr->journey_state = JOURNEY_1;
		}
		else {
			//move cursor to previous row postion 
			move_cursor((*ptr).location.row, (*ptr).location.col);
			DISP(' '); //delete last taxi position

			//move cursor to next row postion after single clock cycle
			move_cursor((*ptr).location.row - 1, (*ptr).location.col);
			PRINT((*ptr).vin - 1000); //show taxi on the map

			//taxi reached its row destination
			if ((*ptr).location.row - 1 == (*ptr).stop1.row) {
				(*ptr).row_state1 = TRUE;
				(*ptr).location.row = (*ptr).location.row - 1;
				if (((*ptr).location.row == (*ptr).stop1.row) && ((*ptr).location.col == (*ptr).stop1.col)) {
					ptr->journey_state = JOURNEY_1;
				}
			}
			else {
				(*ptr).location.row--;
			}
		}
		break;
	}
	//if ((ptr->location.row == ptr->stop.row) && (ptr->journey_state == JOURNEY_1))
		//ptr->row_state = TRUE;

}
void move_right_j0() {
	if ((ptr->location.col == ptr->stop1.col) && (ptr->location.row == ptr->stop1.row)) {
		ptr->journey_state = JOURNEY_1;
	}
	else {
		//(*ptr).state = MOVING;
		//switch ((*req_ptr).drop_off_corner) {
		//case NW:
			//move cursor to previuous col postion 
		move_cursor((*ptr).location.row, (*ptr).location.col);
		DISP(' '); //delete last position taxi

		//move cursor to next col postion after single clock cycle
		move_cursor((*ptr).location.row, (*ptr).location.col + 1);
		PRINT((*ptr).vin - 1000); //show taxi on the map

		//taxi reached its row destination
		if ((*ptr).location.col + 1 == (*ptr).stop1.col) {
			(*ptr).col_state1 = TRUE;
			(*ptr).location.col = (*ptr).location.col + 1;

			if((*ptr).location.row == (*ptr).stop1.row)
				ptr->journey_state = JOURNEY_1;
				ptr->col_state = FALSE;
		}
		else {
			(*ptr).location.col++;
		}
	}
	//if ((ptr->location.col == ptr->stop.col) && (ptr->journey_state == JOURNEY_1))
		//ptr->col_state = TRUE;
}
void move_left_j0() {
	if ((ptr->location.col == ptr->stop1.col) && (ptr->location.row == ptr->stop1.row)) {
		ptr->journey_state = JOURNEY_1;
	}
	else {
		(*ptr).state = MOVING;
		
			//move cursor to previuous col postion 
			move_cursor((*ptr).location.row, (*ptr).location.col);
			DISP(' '); //delete last position taxi

			//move cursor to next col postion after single clock cycle
			move_cursor((*ptr).location.row, (*ptr).location.col - 1);
			PRINT((*ptr).vin - 1000); //show taxi on the map

			//taxi reached its row destination
			if ((*ptr).location.col - 1 == (*ptr).stop1.col) {
				(*ptr).col_state1 = TRUE;
				(*ptr).location.col = (*ptr).location.col - 1;

				if ((*ptr).location.row == (*ptr).stop1.row)
					ptr->journey_state = JOURNEY_1;
					ptr->col_state = FALSE;
			}
			else {
				(*ptr).location.col--;
			}
	}
}