#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <strings.h>
#include <sys/wait.h>

int MyRecv(int iSock, char * pchBuf, size_t tCount){
    size_t tBytesRead=0;
    int iThisRead;
    while(tBytesRead < tCount){
        do{
            iThisRead=read(iSock,pchBuf,tCount-tBytesRead);
        }while( (iThisRead<0) && (errno=EINTR));
        if(iThisRead<0){
            return (iThisRead);
        }else if(iThisRead==0)
            return (tBytesRead);
        tBytesRead+=iThisRead;
        pchBuf+=iThisRead;
    }
}

#define DEFAULT_PORT 6666

int main(int argc, char ** argv){
    int sockfd,acceptfd;
    struct sockaddr_in my_addr;
    struct sockaddr_in their_addr;
    unsigned int sin_size,my_port=6666,lisnum=10;

    if( (sockfd=socket(AF_INET,SOCK_STREAM,0))==-1 ){
        perror("socket");
		return -1;
	}
    printf("socket ok \n");

	memset(&my_addr,0,sizeof(my_addr));
	my_addr.sin_family=AF_INET;
	my_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	my_addr.sin_port=htons(DEFAULT_PORT);

    bzero(&(my_addr.sin_zero),0);
    if( bind(sockfd, (struct sockaddr*)&my_addr, sizeof(struct sockaddr))==-1 ){
        perror("bind");
		return -2;
	}
    printf("bind ok \n");
	if( listen(sockfd, 10)==-1){
        perror("listen");
		return -3;
	}
    printf("listen ok \n");

    char recvMsg[10]={0};
    sin_size=sizeof(my_addr);
    acceptfd=accept(sockfd,(struct sockaddr *) &my_addr,&sin_size);
    if(acceptfd<0){
        close(sockfd);
        printf("accept failed \n");
        return -4;
    }
    ssize_t readLen=MyRecv(acceptfd, recvMsg, sizeof(int));
    if(readLen < 0){
        printf("read failed\n");
        return -1;
    }
    int len=(int) ntohl(*(int *)recvMsg);
    printf("len:%d\n",len);
    readLen=MyRecv(acceptfd,recvMsg,len);
    if(readLen<0){
        printf("read failed\n");
        return -1;
    }
    recvMsg[len]='\0';
    printf("recvMsg:%s\n",recvMsg);
    close(acceptfd);
	return 0;
}
