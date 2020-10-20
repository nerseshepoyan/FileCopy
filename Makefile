output: file_copy.o
	g++ file_copy.o -o output

file_copy.o: 
	g++ -c file_copy.cpp 
	
clean:
	rm *.o output

