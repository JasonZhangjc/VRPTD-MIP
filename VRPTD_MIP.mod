/*********************************************
 * OPL 12.8.0.0 Model
 * Author: Jason
 * Creation Date: Nov 7, 2018 at 7:51:36 AM
 *********************************************/
 
// Parameters: constants
int   c = ...;       // number of customers = number of stops
int   d = 1;         // depot is always lndexed by 1
int   m = 10;        // max number of routes
int   M = 1000;      // big number
int   v = ...;       // velocity of every vehicle (= 35 km/h usually)
float ut = ...;      // every vehicle should be back before 10:00 + ut:00
float sv = ...;      // for each customer there is a service time = (sv)/(60)

// Sets:
range C = 2..c;         // range of customers' indices
range D = 1..c;         // range of indices of customers and depot
range R = 1..m;         // range of routes

// Parameters: vectors and matrices
int   cp[R] = ...;      // vector of capacity of vehicles
float ds[D][D] = ...;  	// distance matrix between customers or between customers and depot
float co[D] = ...;      // vector of cut-off time (time deadline) at each stop
float dm[D] = ...;      // vector of demand for each customer

// Decision variables:
dvar boolean x[R][D][D]; 
// x[r][i][j] == 1 iff customer i is visited before customer j in route r
dvar boolean y[R][D];   // y[r][i] == 1 iff customer i is visited in route r
dvar boolean z[R];      // z[r] == 1 iff route r is used
dvar float+  s[R][D];   // s[r][i] == the time customer i is visited in route r           

// Set the limit of run time to 60 mins
execute timeTermination {
   	cplex.tilim = 60*60;   // set time model stop (second)
    }
    
// Objective function: minimize number of used routes
minimize sum(r in R) z[r];

subject to{

/*#1 All routes should start from depot */
	sum(r in R) s[r][d] == 0; 

/*#2 & #3 bigM constraints of precedence of visiting customers */
/* 2 - y[r][i] - y[r][j] deals with situations 
   when i and j are not visited in the same route */
	forall(i in D, j in D, r in R : i<j)
	{
	  	s[r][j] >= s[r][i] + sv + ds[i][j] / v 
	  	                   - M * (2 - y[r][i] - y[r][j] + x[r][j][i]);
	  	s[r][i] >= s[r][j] + sv + ds[i][j] / v 
	  	                   - M * (3 - y[r][i] - y[r][j] - x[r][j][i]);
 	}	 

/*#4 all visiting time should be >= 0*/
	forall(i in D, r in R)
	  s[r][i] >= 0;

/*#5 All completion time should be <= maximum working time for each vehicle */
	forall(i in C, r in R)
	  s[r][i] + sv + ds[d][i] / v <= ut;

/*#6 One customer is served in only one route*/
	forall(i in C, r in R)
	  s[r][i]/M <= y[r][i];

/*#7 One customer is served in only one route*/
	forall(i in C)
	  sum(r in R) y[r][i] == 1;

/*#8 The depot should be in all routes*/
	forall(r in R)
	  y[r][d] == 1;

/*#9 The deadline of visiting each customer should be met*/
	forall(i in C)
	  sum(r in R) s[r][i] <= co[i];
	  
/*#10 No customer can be served in inactive routes */
	forall(r in R, i in C)
	  y[r][i] <= z[r];

/*#11 Capacity constraints */
	forall(r in R)
	  sum(i in C) y[r][i] * dm[i] <= cp[r];
	  
}
 
