#include<stdio.h>
#include <unistd.h>
#include<string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include<stdlib.h>

int main()
{	char buffer[1024];
	char s[1024];
	int opt=1;
	int PORT=1026;
	int server,client;
	FILE *fp;
	struct sockaddr_in servaddr,clientaddr;
	int addrlen = sizeof(clientaddr);
	server=socket(AF_INET,SOCK_STREAM,0);
	if (server<0)
 	{	printf("socket doest not created\n");
		exit(0);
	}
	servaddr.sin_family = AF_INET;
  	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
   	servaddr.sin_port = htons( PORT );
	setsockopt(server, SOL_SOCKET,
                   SO_REUSEADDR | SO_REUSEPORT, &opt,
                   sizeof(opt));
  	int b=bind(server,(struct sockaddr*)&servaddr,sizeof(servaddr));
	if (b<0)
	{ 	printf("Error in binding\n");
		exit(0);
	}
	listen(server,3);
        printf("\n");
	client=accept(server,(struct sockaddr*)&clientaddr,&addrlen);
	if (client<0)
	{ exit(0);
	}
	printf("Connection accepted from %s\n",inet_ntoa(clientaddr.sin_addr));
        int n= read(client,buffer,1024);
	buffer[n]='\0';
	printf("file Name received is %s\n",buffer);
	fp=fopen(buffer,"r");
 	
	if (fp==NULL)
          send(client,"File Not Present",strlen("File Not Present"),0);
	else
	{
	while(fgets(buffer,1024,fp)!=NULL)
	{	send(client,buffer,strlen(buffer),0);
	}
	printf("file data sent");
	fclose(fp);
	
	}
	
	
	close(	client);
	
	close(server);
}
