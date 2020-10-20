#include <iostream>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>


void copy(const char*file1, const char*file2) { 
  int fd1 = open(file1, O_RDONLY);
  int fd2 = open(file2, O_CREAT | O_WRONLY, S_IRWXU);
  if (fd1 ==-1 || fd2 == -1 ) { 
	  std::cout<<strerror(errno)<<std::endl;
  }
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
	struct stat statbuf;
	if( stat(argv[1], &statbuf)==-1) { 
		std::cout<<strerror(errno)<<std::endl;
	}
	std::cout<<"Physical size of source file: "<<statbuf.st_size<<std::endl;
	std::cout<<"Logical size of source file: "<<statbuf.st_blksize<<std::endl;
	copy(argv[1], argv[2]);	
	if(stat(argv[2], &statbuf)==-1) {
		std::cout<<strerror(errno)<<std::endl;
	}
	std::cout<<"Physical size of copy file: "<<statbuf.st_size<<std::endl;
	std::cout<<"Logical size of source file: "<<statbuf.st_blksize<<std::endl;
	}
	else{ 
		std::cout<<"Error"<<std::endl;
	}
	return 0;
} 
