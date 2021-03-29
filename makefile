ProcessGenerator: ProcessGenerator.o FilesDriver.o CommandDriver.o Command.o Stem.o SharedMemoryDriver.o Process.o Branch.o Leaf.o
	g++ -o ProcessGenerator ProcessGenerator.o FilesDriver.o CommandDriver.o Command.o Stem.o  SharedMemoryDriver.o Process.o Branch.o Leaf.o -lrt -lpthread

ProcessGenerator.o: ProcessGenerator.cpp FilesDriver.h CommandDriver.h
	g++ -c ProcessGenerator.cpp

FilesDriver.o: FilesDriver.h FilesDriver.cpp
	g++ -c FilesDriver.cpp

CommandDriver.o: CommandDriver.h CommandDriver.cpp Stem.h Command.h
	g++ -c CommandDriver.cpp

Stem.o: Stem.h Stem.cpp 
	g++ -c Stem.cpp

Branch.o: Branch.h Branch.cpp
	g++ -c Branch.cpp

Leaf.o: Leaf.h Leaf.cpp
	g++ -c Leaf.cpp

Command.o: Command.h Command.cpp CommandType.h
	g++ -c Command.cpp

SharedMemoryDriver.o: SharedMemoryDriver.h SharedMemoryDriver.cpp	
	g++ -c SharedMemoryDriver.cpp

Process.o: Process.h Process.cpp
	g++ -c Process.cpp

clean:
	rm -rf *.o
