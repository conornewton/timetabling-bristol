CC=g++ -std=c++17

timetabling: main.o activities.o rooms.o students.o teachers.o csv.o
	$(CC) bin/main.o bin/Activities.o bin/Rooms.o bin/Students.o bin/Teachers.o bin/CSV.o -o bin/timetabling

main.o: src/main.cpp
	$(CC) -c src/main.cpp -o bin/main.o

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