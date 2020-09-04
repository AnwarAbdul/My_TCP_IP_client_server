CC = g++
CFLAGS = -Wall -Werror -pipe -O2 -std=c++14
LFLAGS = -lm
INCLUDES = -I.
SERVER_SOURCES = server.cpp helper.cpp
SERVER_OUT = tcpip_server

.PHONY: build
build : $(SERVER_OUT)
$(SERVER_OUT): $(SERVER_SOURCES)
	$(CC) -o $@ $(CFLAGS) $^ $(LFLAGS) 
.PHONY: clean
clean:
	rm -f *.o *.out tcpip_server
