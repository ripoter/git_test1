#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
using namespace std;

int main()
	{
		unsigned int a = 192;
		unsigned int b = 168;
		unsigned int c = 0;
		unsigned int d = 100;
		unsigned short port = 65001;
		
		unsigned int destination_address = ( a << 24 ) | ( b << 16 ) | ( c << 8 ) | d;
		unsigned short destination_port = port;

		sockaddr_in address;
		address.sin_family = AF_INET;
		address.sin_addr.s_addr = htonl( destination_address );
		address.sin_port = htons( destination_port );
		
		int packet_data[2];
        sockaddr_in from;
        socklen_t fromLength = sizeof( from );
        
        int maximum_packet_size = sizeof( packet_data );
        char t = '0';
        
        int nonBlocking = 1;
		
		while(1)
		{
		
        
        

		int handle = socket( AF_INET, SOCK_DGRAM, IPPROTO_UDP );

		if ( handle <= 0 )
		{
			printf( "failed to create socket\n" );
			return false;
		}
		
		

		if ( bind( handle, (const sockaddr*) &address, sizeof(sockaddr_in) ) < 0 )
		{
			printf( "failed to bind socket\n" );
			return false;
		}	
		
		
        if ( fcntl( handle, F_SETFL, O_NONBLOCK, nonBlocking ) == -1 )
        {
            printf( "failed to set non-blocking socket\n" );
            return false;
        }
        
        
        
        
		
        if(recvfrom( handle, packet_data, maximum_packet_size,
                                   0, (sockaddr*)&from, &fromLength ) > 0)
        {
			cin >> t;
			if(t == '1')
			{
				cout << packet_data[0] << "  " << packet_data[1] << endl;
				t = '0';
			}
			
			//printf("%d",packet_data);
			
		}
		close(handle);
		}
        
       
	}
