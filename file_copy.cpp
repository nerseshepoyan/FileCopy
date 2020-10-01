#include <iostream>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>


void copy(const char*str, const char* str1) { 

  int fd1 = open(str, O_RDONLY);
  int fd2 = open(str1, O_CREAT | O_WRONLY)
        const int size = 10;
        char buffer[size];
        int r =-1;
                while ((r=read(fd1,buffer,size))>0){
                        write(fd2, buffer, r);
                }
        close(fd1);
	close(fd2);

}

int main(int argc, char* argv[]){
	if(argc==3) {
	copy(argv[1], argv[2]);	
	}
	else{ 
		std::cout<<"Error"<<std::endl;
	}
	return 0;
} 
