.PHONY: start generate clean clean_object_file

all: start generate

object_file = Numerical_Differentiation_With_Ghost_points.out
code = Numerical_Differentiation_With_Ghost_points.cpp
input_file = Input.txt
original_function = Original_Function_File.txt
output_file = Output_File.txt
grid_file = Grid_Location.txt


start: 
	@echo "We are running the make file.... \n"

generate: ${code}
	@echo "Compiling the code.... \n"
	g++ ${code} -o ${object_file}

clean:
	@echo "Cleaning up the generated text files.... \n"
	rm ${original_function} ${output_file} ${grid_file}
	
clean_object_file:
	@echo "Removing the object file.... \n"
	rm ${object_file}
