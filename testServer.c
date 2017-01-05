#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define  BUFF_SIZE   1024

int main (void)
{
   int server_socket;
   int client_socket;
   int client_addr_size;

   struct sockaddr_in   server_addr;
   struct sockaddr_in   client_addr;

   char buff_rcv[BUFF_SIZE+5];
   char buff_snd[BUFF_SIZE+5];
   char Data_send[23] = {'P','/','1','0','0','/','2','0','0','/','D','/','1','2','9','/','5','4','7','/','w','/','1'};

   int User_Pos[2]; User_Pos[0] = 100; User_Pos[1] = 200;
   int User_Des[2]; User_Des[0] = 129; User_Des[1] =547;
   int weight = 1;

   server_socket = socket( PF_INET, SOCK_STREAM, 0);
   if( -1 == server_socket)
   {
      printf( "server socket 생성 실패\n");
      exit(1);
   }

   memset( &server_addr, 0, sizeof( server_addr));
   server_addr.sin_family = AF_INET;
   server_addr.sin_port = htons(4000);
   server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

   if( -1 == bind( server_socket, (struct sockaddr*)&server_addr, sizeof( server_addr) ) )
   {
      printf( "bind() 실행 에러\n");
      exit(1);
   }

   if( -1 == listen(server_socket, 5))
   {
      printf( "listen() 실행 실패\n");
      exit(1);
   }

   while(1)
   {
      client_addr_size = sizeof(client_addr);
      client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_addr_size);

      if ( -1 == client_socket)
      {
         printf( "클라이언트 연결 수락 실패\n");
         exit(1);
      }

      read ( client_socket, buff_rcv, BUFF_SIZE);
      printf( "receive: %s\n", buff_rcv);
      //send weight, User_info data to the client
      //receive distance value from the client
      //if server receives distance value and all the values are returning z value, weight++
      //if min value defined, send the activation data to the car which has the min value
      sprintf( buff_snd, "%d : %s", strlen( buff_rcv), buff_rcv);
      //String temp;
      //sprintf(temp, "%d", weight);
      //write( client_socket, buff_snd, strlen( buff_snd)+1);          // +1: NULL까지 포함해서 전송
      //write( client_socket, "alpha", strlen("alpha")+1);
      write( client_socket, Data_send, strlen(Data_send)+1);
      //write( client_socket, "D,129,547", strlen("D,129,547")+1);
      //write( client_socket, "w,1", strlen("w,1")+1);
      close( client_socket);
   }
}