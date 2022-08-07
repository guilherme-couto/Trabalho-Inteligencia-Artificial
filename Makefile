CXX				:= g++
INCLUDE_DIRS	:= -I./include
CXX_FLAGS		:= -g -O3 $(INCLUDE_DIRS)

BIN		:= bin
SRC		:= src
INCLUDE	:= include

EXECUTABLE	:= exec

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE)  $^ -o $@ 

init:
	mkdir -p $(BIN)
	mkdir -p $(SRC)
	mkdir -p $(INCLUDE)

exec: $(BIN)/$(EXECUTABLE)

run: exec
	@echo "\nExecutando aplicação...\n"
	$(BIN)/$(EXECUTABLE)
	@echo "\nEncerrando aplicação...\n"

clean:
	@echo "\nRemovendo executavel...\n"
	rm $(BIN)/$(EXECUTABLE)
	@echo "\nRemovido com sucesso...\n"
