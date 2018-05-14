CXX = g++ # This is the main compiler
CXXFLAGS = -std=c++11 -Wall
VPATH = test src include bin build


# build:	000-CatchMain.o Utils.o HuffmanNode.o HuffmanTree.o driver.o
	# $(CXX) $(CXXFLAGS) -I ./include -o bin/huffencode build/Utils.o build/HuffmanNode.o build/HuffmanTree.o build/driver.o

# run: build
	# bin/huffencode $(ARGS)

# test-all: test-tree test-node
	# ./bin/test-node --success && ./bin/test-tree --success

# test-tree: 000-CatchMain.o Utils.o HuffmanNode.o HuffmanTree.o tests-huffmantree.o
	# $(CXX) $(CXXFLAGS) -I ./include -o bin/test-tree build/000-CatchMain.o build/Utils.o build/HuffmanNode.o build/HuffmanTree.o build/tests-huffmantree.o



test: 000-CatchMain.o Audio.o test.o
	$(CXX) $(CXXFLAGS) -I ./include -o bin/test build/000-CatchMain.o build/test.o
	./bin/test --success

	# $(CXX) $(CXXFLAGS) -I ./include -o bin/test build/000-CatchMain.o build/Audio.o build/test.o

driver.o: driver.cpp
	$(CXX) $(CXXFLAGS) -c src/driver.cpp -o build/driver.o
# tests-huffmannode.o: tests-huffmannode.cpp
	# $(CXX) $(CXXFLAGS) -c test/tests-huffmannode.cpp -o build/tests-huffmannode.o

Audio.o: Audio.cpp
	# $(CXX) $(CXXFLAGS) -I ./include -c src/Audio.cpp -o build/Audio.o

test.o: test.cpp Audio.h
	$(CXX) $(CXXFLAGS) -c test/test.cpp -o build/test.o


# HuffmanTree.o: Utils.o HuffmanNode.o HuffmanTree.cpp
	# $(CXX) $(CXXFLAGS) -c src/HuffmanTree.cpp -o build/HuffmanTree.o


000-CatchMain.o: 000-CatchMain.cpp
	$(CXX) $(CXXFLAGS) -I ./include -c test/000-CatchMain.cpp -o build/000-CatchMain.o


clean:
	echo "Cleaning..."
	find . -type f \( -name "*.o" ! -name "000-CatchMain.o" -or -name "test-node" \) -delete
	find . -type f \( -name "*.gch" -or -name "test" -or -name "samp" \) -delete
	# find . -type f -name "*.gch" -delete
	# find . -type f \( -name "*lorem.*" ! -name "lorem.txt" -or -name "lorem" \) -delete
	
	
	
	