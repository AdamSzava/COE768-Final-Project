#include <sys/types.h>

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>                                                                            
#include <netinet/in.h>
#include <arpa/inet.h>

#include <netdb.h>

#define BUFLEN		256	/* buffer length */
#define PORT 3000;
#define DATASIZE 100 // PDU data size
#define PEERNAMESIZE 10 // Peer name size
#define CONTENTNAMESIZE 10 // Content name size
#define ADDRSIZE // Address size

/* PDU Struct */
struct PDU {
	char type;
	char data[dataSIZE];
};

/* Method to Send PDU to Index Server */
void sendPDU(const struct PDU * pdu) {
	
	int sockfd;
	struct sockaddr_in serverAddr; 	// Internet endpoint address
	struct hostent *phe; 			// pointer to host information entry

	printf("Sending PDU to Index Server...\n");

	// Create UDP socket
	printf("...creating UDP socket\n");
	if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
		printf("...error\n");
		exit(1);
	}

	// Initialize server address struct
	printf("...initializing\n");
	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	
	/* Map host name to IP address, allowing for dotted decimal */
	printf("...mapping host name\n");
   	if ( phe = gethostbyname(host) ) {
		memcpy(&sin.sin_addr, phe->h_addr, phe->h_length);
    } else if ( (sin.sin_addr.s_addr = inet_addr(host)) == INADDR_NONE) {
		fprintf(stderr, "Can't get host entry \n");
	}

	// Sending PDU to Index Server
	printf("...sending PDU\n")
	if (sendto(sockfd, pdu, sizeof(struct PDU), 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
		printf("...error\n");
		close(sockfd);
		exit(1);
	}
	
	printf("...PDU sent!\n");
	close(sockfd);
}

/* Download */
void downloadContent(const struct PDU* pdu) {

}

/* MAIN */
int main(int argc, char **argv) {

	/* PDU */
	struct PDU REGISTER, DOWNLOAD, SEARCH, TREGISTRATION, DATA, ONLINE, AWKNOWLEDGEMENT, ERROR;

	// PDU Type
	REGISTER.type = 'R';
	DOWNLOAD.type = 'D';
	SEARCH.type = 'S';
	TREGISTRATION = 'T';
	DATA.type = 'D';
	ONLINE.type = 'O';
	AWKNOWLEDGEMENT = 'A';
	ERROR.type = 'E';

	// Function request variables
	char functionRequest[1];

	// Register variables
	char peerName[PEERNAMESIZE];
	char contentName[CONTENTNAMESIZE];
	char address[ADDRSIZE];
	

	switch (argc) {
	case 1:
		break;
	case 2:
		host = argv[1];
	case 3:
		host = argv[1];
		PORT = atoi(argv[2]);
		break;
	default:
		fprintf(stderr, "usage: UDPtime [host [port]]\n");
		exit(1);
	}

	memset(&sin, 0, sizeof(sin));
   	sin.sin_family = AF_INET;                                                                
    sin.sin_port = htons(PORT);

	/* Map host name to IP address, allowing for dotted decimal */
   	if ( phe = gethostbyname(host) ) {
		memcpy(&sin.sin_addr, phe->h_addr, phe->h_length);
    } else if ( (sin.sin_addr.s_addr = inet_addr(host)) == INADDR_NONE) {
		fprintf(stderr, "Can't get host entry \n");
	}
                                                                                
    /* Allocate a socket */
    s = socket(AF_INET, SOCK_DGRAM, 0);
    if (s < 0) {
		fprintf(stderr, "Can't create socket \n");
	}
                                                                                
    /* Connect the socket */
    if (connect(s, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
		fprintf(stderr, "Can't connect to %s %s \n", host, "Time");
	}

	/* Content Client or Content Server? */
	while(1) {

		// Prompt User Input for Function
		printf("Select Function: R - Register, S - Search/Download, T - De-Registration, O - List, Q - Quit\n");
		scanf(" %c", &functionRequest);
		printf("Chosen function: %c\n", functionRequest[0]);

		// Function decoder
		printf("Decoding request...");
		switch (function) {
			case 'R':
			case 'r':
				printf("Registering...\n");

				// Prompt User for Peer Name and Content Name
				printf("...enter Peer name: ");
				fgets(peerName, PEERNAMESIZE, stdin);
				peerName[strcspn(peerName, "\n")] = '\0'; // Remove newline

				printf("...enter Content name: ");
				fgets(contentName, CONTENTNAMESIZE, stdin);
				contentName[strcspn(contentName, "\n")] = '\0'; // Remove newline

				// Get Port Number
				struct sockaddr_in localAddr;
				socklen_t addrLen = sizeof(localAddr);
				getsockname(s, (struct sockaddr*)&localAddr, &addrLen);
				int localPort = ntohs(localAddr.sin_port);

				char tempData[DATASIZE];
				// Concatenate to tempData
				snprintf(tempData, DATASIZE, "%.30s %.30s %.30s", peerName, contentName, localPort);
				// Copy tempData to REGISTER.data
				strncpy(REGISTER.data, tempData, sizeof(REGISTER.data) - 1);
				sendPDU(&REGISTER);

				// Wait for index server response of A-type or E-type
				
				break;
			case 'S':
			case 's':
				printf("Searching...\n");

				// Prompt User for Peer Name
				printf("...enter Peer name:");
				fgets(peerName, PEERNAMESIZE, stdin);
				peerName[strcspn(peerName, "\n")] = '\0'; // Remove newline

				// Prompt User for Content Name
				printf("...enter Content name:");
				fgets(contentName, CONTENTNAMESIZE, stdin);
				peerName[strcspn(contentName, "\n")] = '\0'; // Remove newline

				// Appending data to S-type PDU
				char tempData[DATASIZE];
				
				snprintf(tempData, DATASIZE, "%.30s %.30s", peerName, contentName);
				// Copy tempData to REGISTER.data
				strncpy(SEARCH.data, tempData, sizeof(SEARCH.data) - 1);

				// Contact Index Server for Content Server Address; send S-type PDU; compute search
				sendPDU(&SEARCH);
				
				// Wait for index server response for S-type or E-type PDU

				// Extract address from PDU

				// Set TCP connection with content server

				// Determine if connection successful

				// Send D-type PDU with content name

				// Receive C-type PDUs from Content Server
				printf("...downloading\n");

				// Register the peer that downloaded from the content server

				// Receive A-type PDU from index server

				break;
			case 'T':
			case 't':
				printf("De-Registering...\n");

				// Send T-type PDU to index server

				// Receive A-type or E-type PDU
			
							
				break;
			case 'O':
			case 'o':
				printf("Listing Online Registered Content...\n");

				// Send O-type PDU to index server
				sendPDU(&ONLINE);

				// Receive O-type PDU containing list
				break;
			case 'Q':
			case 'q':
				print("Quitting program...\n");
	
				// De-register all registered content
				
				exit(0);
			break;
		}
	}
	
	close(s);

	return 0;
}
