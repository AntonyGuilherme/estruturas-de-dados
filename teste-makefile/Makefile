# comentario

CXX := g++
OBJ := main.o teste.o
TARGET := programa.out

%.o: %.cpp
	g++ -c $<

comp:$(OBJ) 
	$(CXX) -o $(TARGET) $(OBJ)
	make clear
	mkdir compile
	mkdir ./compile/objects
	mv -i *.o ./compile/objects
	mv -i *.out ./compile

comp1:
	g++ -c *.cpp 
	g++ -o programa.out *.o
	make clear
	mkdir compile
	mkdir ./compile/objects
	mv -i *.o ./compile/objects
	mv -i *.out ./compile

execute:
	./compile/programa.out

clear:
	@rm -rf ./compile	