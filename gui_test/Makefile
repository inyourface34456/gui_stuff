all: main

CXX = g++
CXXFLAGS = -g -Wall -Wpedantic -Werror
LIBS = -lglfw -lGLU -lGL -lXrandr -lXxf86vm -lXi -lXinerama -lX11 -lrt -ldl -lGLEW -lSOIL

SRCS = $(shell find -path **/*.cpp -type f -print | sed -e 's/ /\\ /g')
HEADERS = $(shell find -path **/*.h -type f -print)

main: $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o "$@" $(LIBS)
	
main-release: $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SRCS) -O3 -o "$@" $(LIBS)
	
main-debug: $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SRCS) -O0 -o "$@" $(LIBS)
	
clean:
	rm -rf main main-release main-debug
