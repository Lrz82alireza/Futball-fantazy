CC=g++
CFLAGS=-c -Wall --std=c++11 
LDFLAGS= 

BIN_DIR =./bin
EXECUTABLE = $(BIN_DIR)/main

SOURCES=$(wildcard *.cpp)
OBJS = $(patsubst %.cpp,$(BIN_DIR)/%.o,$(SOURCES))
RUN_CMD=./$(EXECUTABLE)


$(BIN_DIR)/%.o: %.cpp | $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(EXECUTABLE): $(OBJS) | $(BIN_DIR)
	$(CC) $^ -o $@ $(LDFLAGS)

$(BIN_DIR):
	mkdir $(BIN_DIR)

run: $(EXECUTABLE)
	$(RUN_CMD)

clean:
	rm -rf $(OBJS) $(EXECUTABLE) $(BIN_DIR)