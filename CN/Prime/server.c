#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>
int main()
{
       int serv,len,client;
	char buffer[1024];
	struct sockaddr_in servaddr,clientaddr;
	serv=socket(AF_INET,SOCK_STREAM,0);
	
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");	
	servaddr.sin_port=htons(1047);
	
	bind(serv,(struct sockaddr*)&servaddr,sizeof(servaddr));
	listen(serv,3);
	client=accept(serv,(struct sockaddr*)&clientaddr,&len);  
	while(1)
	{
	 int n= read(client,buffer,1024);
	 buffer[n]='\0';
	
	 printf("received data %s\n",buffer);
	 if(strcmp(buffer,"stop")==0)
		 break;
	 int x;
	 sscanf(buffer,"%d",&x);
	 int flag=0,m;
	 m=x/2;    
         for(int i=2;i<=m;i++)    
        {    
     		 if(x%i==0)    
			{     
			
			flag=1;    
			break;    
			}    
	}    
	if(flag==0)    
		send(client,"prime",strlen("prime"),0);
      else
      	send(client,"not prime",strlen("not prime"),0); 
	 
	 
	}
}
	 