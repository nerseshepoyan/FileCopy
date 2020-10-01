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
	int n1{},n2{};	
	std::cin>>n1>>n2;
	int k{};
	std::cin>>k;
	std::vector <int> arr;
	for (int i=n1; i<n2; i+=k){
	int n{};
	if ( (i+k)>n2) {
		n=n2;	
	}
	else{ 
	n = i+k;
	}	
	char name[50];
	sprintf(name,"fd%d",i);
	int fd = open(name, O_RDWR |  O_CREAT | O_TRUNC, S_IRWXU);
	arr.push_back(fd);
	int id = fork();
	if (id ==  0) {
	cal_and_write(i,n,fd);
        return 0;
	    }	
	}
	while(wait(nullptr)>0);
	int count{};
	
	for(int i=0; i<arr.size(); ++i) {
		count += read_result(arr[i]);
		close(arr[i]);
	} 
	std::cout<<"Result: "<<count<<std::endl;
	return 0;
}
