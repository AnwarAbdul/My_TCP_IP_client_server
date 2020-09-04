CC = g++
CFLAGS = -Wall -Werror -pipe -O2 -std=c++14
LFLAGS = -lm
INCLUDES = -I.
SERVER_SOURCES = server.cpp
SERVER_OUT = tcpip_server

SERVER_OBJS = $(SERVER_SOURCES:.cpp=.o)
%.o: %.cpp
	$(CC) -o $@ $(CFLAGS) $< $(LFLAGS)
		
.PHONY: build
build : $(SERVER_OUT)
$(SERVER_OUT): $(SERVER_OBJS)
	cp server.o $@
.PHONY: clean
clean:
	rm -f *.o *.out tcpip_server
