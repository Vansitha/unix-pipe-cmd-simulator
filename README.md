# Unix Pipe Simulator

## Program overview

- Program demonstrates the functionality of the unix pipe command. 
- It reads an input file containing the commands to be executed.
- Each command is executed and the output is sent into the following command's input.
- This is accomplished through the use of output files, which help achieve the 
replication of the the UNIX pipe's functionality.
- Finally prints out the output.

## Running the program

Step 1: `cd pipe_simulator`

Step 2: run `make`

 - Creates a 'bin' directory containing the compiled object files
- Creates an executable in the current working directory called "pipesim"

Step 3: run `./pipesim <input-file-name.txt>`

Step 4 (Before running the program again): run `make rmout`
- This will remove all output files created by the program previously.  
- This step is a required since the program does not replace any output files generated when executed again.

Step 5 (Optional): run `make clean`
- Removes executable, bin directory and any file named as "output<num>.txt"

## Assumptions

- Assumed that the commands provided in the initial input file are valid.
