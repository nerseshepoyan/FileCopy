#include <iostream>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>


void calculate_write(int n, int fd) { 
	int result = 1;
	for (int i =2;i<=n; ++i) {
		result  *= i;
	}
	const int size = 10; 
	char buffer[size];
	sprintf(buffer, "%d", result);
	std::cout<<"descriptor: "<<fd<<", WRITE: "<<buffer<<std::endl;
	write(fd, buffer,size); 
}


int r_result(int fd) { 
	lseek(fd,0,SEEK_SET);
	const int size = 10; 
	char buffer[size];
	read(fd, buffer, size);	
	std::cout<<"descriptor: "<<fd<<", READ: "<<buffer<<std::endl;
	return atoi(buffer);
}


int main() {
	int n{},k{};
	std::cin>>n;
	std::cin>>k;
	int nk=n-k;
	
	int fd1 = open("fd1", O_RDWR |  O_CREAT | O_TRUNC, S_IRWXU );
	if (fd1==-1){
		std::cout<<strerror(errno)<<std::endl;
	}
	
	int fd2 = open("fd2", O_RDWR |  O_CREAT | O_TRUNC, S_IRWXU );
        if (fd2==-1){
                std::cout<<strerror(errno)<<std::endl;
        }
	
	int fd3 = open("fd3", O_RDWR |  O_CREAT | O_TRUNC, S_IRWXU );
       	if (fd3==-1){
                std::cout<<strerror(errno)<<std::endl;
        }


	int id1 = fork();
	if (id1 == 0){ 
		calculate_write(n,fd1);
		return 0;
	}

	int id2 = fork();
	if (id2 == 0){
                calculate_write(k,fd2);
        	return 0;        	
	}

	int id3 = fork();
	if (id3 == 0){
                calculate_write(nk,fd3);
		return 0;       	        
	}
	
	while(wait(NULL)>0);
	
	int nres = r_result(fd1);
        int kres = r_result(fd2);
	int nkres = r_result(fd3);	
	
	std::cout<<"Result is: "<<nres/(kres*nkres)<<std::endl;

	close(fd1);
	close(fd2);
	close(fd3);
	
	return 0;

}
