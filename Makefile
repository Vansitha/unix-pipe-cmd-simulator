CC = gcc
CFLGAS =  -Wall -Werror -g
OBJ = bin/pipesim.o bin/util.o bin/fileIO.o bin/linkedList.o bin/process.o
EXEC = pipesim

$(EXEC): $(OBJ)
	$(CC) $(OBJ) $(CFLGAS) -o $(EXEC)

bin/pipesim.o: src/pipesim.c src/linkedList.h src/process.h src/util.h src/fileIO.h
	@mkdir -p bin
	$(CC) $(CFLAGS) -c $< -o $@

bin/util.o: src/util.c src/util.h
	@mkdir -p bin
	$(CC) $(CFLGAS) -c $< -o $@

bin/fileIO.o: src/fileIO.c src/fileIO.h  src/linkedList.h src/util.h
	@mkdir -p bin
	$(CC) $(CFLGAS) -c $< -o $@

bin/linkedList.o: src/linkedList.c src/linkedList.h
	@mkdir -p bin
	$(CC) $(CFLGAS) -c $< -o $@

bin/process.o: src/process.c src/process.h src/linkedList.h src/fileIO.h src/util.h
	@mkdir -p bin
	$(CC) $(CFLGAS) -c $< -o $@

# rule to clean all object, executable and output files
clean:
	rm -rf bin pipesim output*.txt

# rule to clean only the output files
rmout:
	rm output*.txt
