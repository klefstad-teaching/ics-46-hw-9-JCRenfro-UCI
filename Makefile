CXX = g++
CXXFlgs = -Wall -pedantic -fsanitize=address
testf = gtest/student_gtests.cpp
header = src/*.h

main_l: src/ladder_main.cpp ladder.o
	$(CXX) $(CXXFlgs) src/ladder_main.cpp -o ladder.out ladder.o

main_d: src/dijkstras_main.cpp dij.o
	$(CXX) $(CXXFlgs) src/dijkstras_main.cpp -o dij.out dij.o

test: ladder.o dij.o
	$(CXX) $(CXXFlgs) $(testf) -o test.out -lgtest -lgtest_main ladder.o dij.o
	make clean

dij.o: $(header) src/dijkstras.cpp
	$(CXX) $(CXXFlgs) -c src/dijkstras.cpp -o dij.o

ladder.o: $(header) src/ladder.cpp
	$(CXX) $(CXXFlgs) -c src/ladder.cpp -o ladder.o

clean:
	rm *.o