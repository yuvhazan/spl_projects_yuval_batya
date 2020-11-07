# All Targets
all: cTrace

cTrace: bin/Main.o bin/Session.o bin/Agent.o bin/Graph.o bin/Tree.o
	@echo 'Building target: cTrace'
	g++ -o bin/cTrace bin/Main.o bin/Session.o bin/Agent.o bin/Graph.o bin/Tree.o 
	@echo 'Finished building target: cTrace'

# Depends on the source and header files
bin/Main.o: src/main.cpp
	g++ -g -Wall -std=c++11 -c -Iinclude -o bin/Main.o src/main.cpp

# Depends on the source and header files 
bin/Session.o: src/Session.cpp
	g++ -g -Wall -std=c++11 -c -Iinclude -o bin/Session.o src/Session.cpp

# Depends on the source and header files 
bin/Agent.o: src/Agent.cpp
	g++ -g -Wall -std=c++11 -c -Iinclude -o bin/Agent.o src/Agent.cpp

# Depends on the source and header files 
bin/Graph.o: src/Graph.cpp
	g++ -g -Wall -std=c++11 -c -Iinclude -o bin/Graph.o src/Graph.cpp

# Depends on the source and header files 
bin/Tree.o: src/Tree.cpp
	g++ -g -Wall -std=c++11 -c -Iinclude -o bin/Tree.o src/Tree.cpp


#Clean the build directory
clean: 
	rm -f bin/*
