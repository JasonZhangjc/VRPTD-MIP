# VRPTD MIP Model Implementation in CPLEX
The data_processing.py is to generate the xxx.dat file for CPLEX.

The VRPTD_MIP.mod is to implement the MIP model for the Vehicle Routing Problem with Time Deadlines (VRPTD).

This is a demo for how to use them.

Required tools:
 1. IBM ILOG CPLEX Optimization Studio (https://www.ibm.com/products/ilog-cplex-optimization-studio)
 
To run the project:
 Data Processing:
 1. Put data_processing.cpp and all the data files (xxx.csv) you are using together.
 2. Modify the code piece "data_30_1.dat" on line 64 to a file name you like.
 3. Modify the code piece "deli_grouped_sample_30_1.csv" on line 77 to the name of a data file including parameters you need.
 4. Modify the code piece "distance_matrix_30_1.csv" on line 140 to the name of a data file including distance matrix you need.
 5. On your terminal, run   g++ -std=c++14 data_processing.cpp
 6. On your terminal, run   ./a.out
 7. Go find the file named in 2.
 
 Run Model:
 8. Open IBM ILOG CPLEX Optimization Studio
 9. In the file section, build a new OPL Project
 10. In the file section, select Copy the files to the project
 11. Insert the Code, VRPTD_MIP.mod with the data.dat in the "Data" file
 12. Create a new configuration, and drag the data file and the mod file into that configuration
 13. Run!!
 14. The result is on the result section, the limitation we set for the running time is 1 hour. If there is a result in the result section and point out as optimal, this is a optimal solution (porven by this solver). And the running time is on the corner (maybe left, maybe right).
