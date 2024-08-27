#pragma once
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>
#include<io.h>
#include <Windows.h>	/* For Windows-specific graphic data type and functions */

//#include "Relative Files.h"
#define LENGTH 256
#define START 1000

#define NUL	0x00
#define ESC	0x1b

#define MXN 100



/*
 - Box character codes (decimal)
 - See https://www.lookuptables.com/text/extended-ascii-table
*/
#define UL		218
#define LL		192
#define UR		191
#define LR		217
#define HBAR	196
#define VBAR	179

#define NL	'\n'
#define NUL	'\0'
#define NAMELEN	16
#define TRUE	1
#define FALSE	0
#define DEL_END -1l

#define MAX_mcode 51
#define FALSE 0
#define TRUE 1

/* DISPput character */
#define	DISP(x)	putc((x),stdout)
#define PRINT(val) printf("%d", val) 


#define TRUNCATE(name)	name[strlen(name)-1] = '\0'

//int boundary_row_check1 = 0;
//int boundary_row_check2 = 0;
//int boundary_col_check1 = 0;
//int boundary_col_check2 = 0;



HANDLE Console;		/* Identify action and I/O stream */

enum REC_STATUS { DELETED, ACTIVE };

enum Taxi_state { IDLE, MOVING, PARKED };

enum Taxi_state_with_passenger { NEXT_PASS, CURR_PASS, FIRST_PASS, NO_PASS };

enum Pass_state { PICKED, WAITING, DROPPED };

enum journey { JOURNEY_0, JOURNEY_1 };

enum building_corner {
	NW = 1,
	NE = 2,
	SE = 3,
	SW = 4,
}corner[MXN];

struct coordinate {
	int row;
	int col;
	int street;
	int avenue;
};

struct building_corner_position {
	struct coordinate NW; //Internal map coordinate of North West of building
	struct coordinate NE; //Internal map coordinate of North East of building
	struct coordinate SW; //Internal map coordinate of South West of building
	struct coordinate SE; //Internal map coordinate of South East of building
};

struct taxi {
	long battery_soc;
	long battery_capacity;
	long charge_rate;
	long taxi_state;
	long building_parked;
	enum building_corner corner_parked;
	long distance;
	enum REC_STATUS status;

	/*vin = taxi id (similar to passenger id) */
	long vin;

	struct coordinate temp_start; //Origin of request containing the corners
	struct coordinate temp_stop;
	struct coordinate start; //Origin of request containing the corners
	struct coordinate start1;
	struct coordinate right_side_dest; //TEMP DESTINATION TO GET TAXI ON RIGHT SIDE OF ROAD
	struct coordinate location;
	struct coordinate stop; //Destination of request containing the corners
	struct coordinate stop1;
	int passenger_id;
	enum Taxi_state state;


	enum Taxi_state_with_passenger taxi_pass_state;
	enum journey journey_state;
	enum journey journey_state_next_pass;

	int row_state; //has the taxi reached its destination row (Yes/No)
	int col_state; //has the taxi reached its destination column (Yes/No)
	int row_state1;
	int col_state1;

	int row_state_next_pass;
	int col_state_next_pass;
	int row_move_next_pass;
	int col_move_next_pass;

	int row_state_next_pass1;
	int col_state_next_pass1;
	int row_move_next_pass1;
	int col_move_next_pass1;
	struct coordinate source;
	struct coordinate destination;
	int row_move; //determines direction up or down
	int col_move; //determines direction right or left
	int row_move1;
	int col_move1;
	struct taxi* next;
	struct taxi* prev;
};
typedef struct taxi TAXI;
struct taxi* taxis;
struct taxi* first_taxi;
struct taxi* last_taxi;
struct taxi* ptr;
struct taxi* mov_list_ptr;
struct taxi* l_mov_list_ptr; //LAST TAXI ON MOVING LIST
struct taxi* park_list_ptr;
struct taxi* l_park_list_ptr; //LAST TAXI ON PARKING LIST

struct t_header {

	long first_vin;
};
typedef struct t_header TAXI_HEADER;

typedef struct service {

	long vin;
	long day;
	long month;
	long year;
	char* comment;

}SERVICE;

struct service_header {
	long first_vin;
};
typedef struct service_header SERVICE_HEADER;

struct building {
	int building_num; //Starting from 1
	struct coordinate location; //Indicated by Street and Avenue
	struct coordinate NW; //Internal map coordinate of North West of building
	struct coordinate NE; //Internal map coordinate of North East of building
	struct coordinate SW; //Internal map coordinate of South West of building
	struct coordinate SE; //Internal map coordinate of South East of building
	int no_charging;
	int no_parking;
};
struct building buildings[MXN];
int num_of_buildings;

struct time {
	int hours;
	int minutes;
};

struct passenger_request {
	long time_req;
	struct coordinate origin;
	struct coordinate destination;
	enum building_corner pick_up_corner; //Either NW-North West, NE-North East, SW-South West, or SE-South East
	enum building_corner drop_off_corner; //Either NW-North West, NE-North East, SW-South West, or SE-South East
	long pass_state;

	/*pid = passenger id */
	long pid;  //passenger_num 
	

	long building_pickup;
	long num_of_requests;
	enum REC_STATUS status;
	enum Pass_state p_state;

	struct passenger_request* next;
	struct passenger_request* prev;
};
typedef struct passenger_request PASSENGER;
struct passenger_request* req_ptr;
struct passenger_request* first_req;
struct passenger_request* last_req;
struct passenger_request* waiting_req;
struct passenger_request* l_waiting_req; //LAST TAXI REQUEST ON THE WAITING LIST
struct passenger_request* accepted_req;
struct passenger_request* l_accepted_req; //LAST REQUEST ON THE ACCEPTED LIST
struct passenger_request* completed_req;

struct p_header {

	long first_id;
};
typedef struct p_header HEADER;

#define TRUNCATE(name)		name[strlen(name)-1] = '\0'

extern FILE* sfd;

extern void move_down_j0();
extern void move_up_j0();
extern void move_right_j0();
extern void move_left_j0();

extern void taxi_menu();

extern int init_taxi();
extern int str_2_num(char* string);
extern int view_taxi_record();
extern int delete_taxi();
extern int add_new_taxi();

extern int init_passenger();
extern int view_pass_record();
extern int disp_all_pass_record();
extern int add_new_passenger();
extern int str_2_num(char* string);
extern int update_pass_record();

extern void display_taxis();


#pragma once
