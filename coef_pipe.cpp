#include <iostream>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>


void calculate_write(int n, int fd) {
        int result = 1;
        for (int i =2;i<=n; ++i) {
                result  *= i;
        }
        const int size = 10;
        char buffer[size];
        sprintf(buffer, "%d", result);
        write(fd, buffer,size);
}


int r_result(int fd) {
        lseek(fd,0,SEEK_SET);
        const int size = 10;
        char buffer[size];
        read(fd, buffer, size);
        return atoi(buffer);
}


int main() { 
	
	int n{}, k{};
	std::cin>>n>>k;
	int nk=n-k;
	int n_arr[2] = {};
	int k_arr[2] = {};
	int nk_arr[2] = {};
	
	if (pipe(n_arr)==-1){
		std::cout<<strerror(errno)<<std::endl;
		return 0;
	}	
	if (pipe(k_arr) == -1) {
		std::cout<<strerror(errno)<<std::endl;
		close(n_arr[0]);
		close(n_arr[1]);
		return 0;
	}
	if (pipe(nk_arr) == -1) {
		std::cout<<strerror(errno)<<std::endl;
		close(n_arr[0]);
                close(n_arr[1]);
		close(k_arr[0]);
		close(k_arr[1]);
		return 0;
	}
		
	int id = fork();
	if (id == 0) {
		close(n_arr[0]);
	    	calculate_write(n, n_arr[1]);
		return 0;
	}

	else { 
		close(n_arr[1]);
	}

	int id1 = fork();
	if (id1 == 0) {
		close(k_arr[0]);
                calculate_write(k, k_arr[1]);
                return 0;
        }
	 else {
                close(k_arr[1]);
        }

	int id3 = fork();
	if (id3 == 0) {
		close(nk_arr[0]);
		calculate_write(nk, nk_arr[1]);
                return 0;
        }
	 else {
                close(nk_arr[1]);
        }

	int nres = r_result(n_arr[0]);
	int kres = r_result(k_arr[0]);
	int nkres = r_result(nk_arr[0]);
	
	close(n_arr[0]);
	close(n_arr[0]);
	close(k_arr[0]);
	close(k_arr[0]);
	close(nk_arr[0]);
	close(nk_arr[0]);

	wait(nullptr);	

	std::cout<<"Result: "<<nres/(kres*nkres)<<std::endl;
	return 0;
}
