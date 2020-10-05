#include <iostream>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>
#include <vector>

bool IsPrime(int n){
int count =0;
for(int i=1; i<=n;++i) {
        if(n%i==0) {
        ++count;
        }
    }
   return count == 2;
}


void cal_and_write(int n1, int n2, int fd) {
  int count = 0;
  for(int i=n1; i<n2; ++i) {
        if (IsPrime(i))
                ++count;
  }
  std::cout<<"From "<<n1<<" To "<<n2<<':'<<count<<std::endl;
  const int size = 10;
  char buffer[size];
  sprintf(buffer, "%d", count);
  write(fd,buffer,size);
}


int read_result(int fd){
        lseek(fd,0, SEEK_SET);
        const int size =10;
        char buffer[size];
        read(fd,buffer,size);
	return atoi(buffer);
}


int main() {
	int n1{}, n2{}, k{};
	std::cin>>n1>>n2>>k;
	int row{};
	std::vector <int> begin;
	std::vector <int> end;
	for ( int i=n1; i<n2; i+=k) {
	int n{};
        if ((i+k)>=n2) {
                n=n2;
         }
        else {
       		n = i+k;
       	 }
	begin.push_back(i);
	end.push_back(n);
	++row;
	}
	int arr[row][2] = {};
	for( int i =0; i<row; ++i) {
	if(pipe(arr[i]) == -1) {
		std::cout<<strerror(errno)<<std::endl;
		for(int j=0; j<i; ++j) {
		close(arr[j][0]);
		close(arr[j][1]);
	   }	
	 }
	}
	int p[row]={};
	for (int i = 0; i<row; ++i) { 
	p[i] = fork();
	if (p[i]==0) { 
	close(arr[i][0]);
	cal_and_write(begin[i],end[i],arr[i][1]);
	return 0;
		}
	else { 
	    close(arr[i][1]);	
		}
	}	
	int count = 0;
	for (int i=0; i <row;++i) {
	count += read_result(arr[i][0]);
	close(arr[i][0]);
	close(arr[i][1]);
	}
	wait(nullptr);
	std::cout<<count<<std::endl;
	return 0;
}
