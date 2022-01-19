CC = g++
INCLUDE_FOLDER = ./include/
BIN_FOLDER = ./bin/
OBJ_FOLDER = ./obj/
SRC_FOLDER = ./src/

MAIN = main
TARGET = run.out
SRC = $(wildcard $(SRC_FOLDER)*.cpp)
OBJ = $(patsubst $(SRC_FOLDER)%.cpp, $(OBJ_FOLDER)%.o, $(SRC))

$(OBJ_FOLDER)%.o: $(SRC_FOLDER)%.cpp
	$(CC) $(CXXFLAGS) -c $< -o $@ -I$(INCLUDE_FOLDER)

all:$(OBJ)
		$(CC) $(CXXFLAGS) -o $(BIN_FOLDER)$(TARGET) $(OBJ)
		
clean:
	@rm -rf $(OBJ_FOLDER)* $(BIN_FOLDER)run.out

cleanfiles:
	@rm -rf rodada*

compile:
	$(BIN_FOLDER)$(TARGET)	teste.txt saida1.txt 8
	$(BIN_FOLDER)$(TARGET)	teste.txt saida2.txt 11
	$(BIN_FOLDER)$(TARGET)	teste.txt saida3.txt 4
	$(BIN_FOLDER)$(TARGET)	teste.txt saida4.txt 3
	$(BIN_FOLDER)$(TARGET)	teste.txt saida5.txt 2
	$(BIN_FOLDER)$(TARGET)	teste.txt saida6.txt 1