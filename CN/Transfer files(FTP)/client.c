#include<stdio.h>
#include <unistd.h>
#include<string.h>
#include <netinet/in.h>
 #include <arpa/inet.h>
int main()
{   int client;
   struct sockaddr_in serveraddr;
  char buffer[1024];
  char s[1024];
   int port=1026;
    client=socket(AF_INET,SOCK_STREAM,0);
    serveraddr.sin_family=AF_INET;
    serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    serveraddr.sin_port = htons( port );
   if( connect(client,(struct sockaddr*)&serveraddr,sizeof(serveraddr))>0)
    printf("connected");
  send(client,"udplient.c",strlen("udpclient.c"),0);
while(1)
{  int n=read(client,buffer,1024);
  if(n==0)
	break;
   buffer[n]='\0';
   printf("%s",buffer);
}

close(client);
}
