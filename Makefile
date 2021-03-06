CC=g++ -std=c++17 -O3

timetabling: main.o activities.o rooms.o students.o teachers.o csv.o backtrack.o hardconstraints.o sa.o obj.o data.o
	$(CC) bin/main.o bin/Activities.o bin/data.o bin/Rooms.o bin/Students.o bin/Teachers.o bin/CSV.o bin/Backtrack.o bin/HardConstraints.o bin/Sa.o bin/obj.o -o bin/timetabling

main.o: src/main.cpp
	$(CC) -c src/main.cpp -o bin/main.o

data.o: src/Data/Data.cpp src/Data/Data.hpp
	$(CC) -c src/Data/Data.cpp -o bin/data.o

backtrack.o: src/Backtracking/Backtrack.cpp src/Backtracking/Backtrack.hpp
	$(CC) -c src/Backtracking/Backtrack.cpp -o bin/Backtrack.o

hardconstraints.o: src/Backtracking/HardConstraints.cpp src/Backtracking/HardConstraints.hpp
	$(CC) -c src/Backtracking/HardConstraints.cpp -o bin/HardConstraints.o	

activities.o: src/Data/Activities.cpp src/Data/Activities.hpp src/Matrices/Matrix.hpp src/Matrices/SparseMatrix.hpp
	$(CC) -c src/Data/Activities.cpp -o bin/Activities.o

rooms.o: src/Data/Rooms.cpp src/Data/Rooms.hpp
	$(CC) -c src/Data/Rooms.cpp -o bin/Rooms.o

students.o: src/Data/Students.cpp src/Data/Students.hpp
	$(CC) -c src/Data/Students.cpp -o bin/Students.o

teachers.o: src/Data/Teachers.cpp src/Data/Teachers.hpp
	$(CC) -c src/Data/Teachers.cpp -o bin/Teachers.o

csv.o: src/CSV/CSV.cpp src/CSV/CSV.hpp
	$(CC) -c src/CSV/CSV.cpp -o bin/CSV.o

sa.o: src/Optimization/SimulatedAnnealing.cpp src/Optimization/SimulatedAnnealing.hpp
	$(CC) -c src/Optimization/SimulatedAnnealing.cpp -o bin/Sa.o

obj.o: src/Optimization/Objective.cpp src/Optimization/Objective.hpp
	$(CC) -c src/Optimization/Objective.cpp -o bin/obj.o