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
#define DATASIZE 100 // PDU data size
#define PEERNAMESIZE 10 // Peer name size
#define CONTENTNAMESIZE 10 // Content name size
#define ADDRSIZE // Address size

#define PORT 3000;

/* PDU Structure */
struct PDU {
	char type;
	char data[DATASIZE];
};

/* Type R Structure */
struct R {
	char type;
	char peerName[PEERNAMESIZE];
	char contentName[CONTENTNAMESIZE];
	char address[ADDRSIZE];
};

/* Type S Structure */
struct S {
	char type;
	char peerName[PEERNAMESIZE];
	char contentName[CONTENTNAMESIZE];
	char address[ADDRSIZE];
};

/* Content Server Structure */
struct ContentServer {
	char contentName[CONTENTNAMESIZE];
	char data[DATASIZE];
	// struct R serverPDUs[10]; // TODO 10 is number of clients
};

/* Content Client Structure */
struct ContentClient {
	// int clientIndexPDU;
	char contentName[CONTENTNAMESIZE];
	char data[DATASIZE];
	// struct R clientPDUs[10]; // TODO
};

/* Index Server */
struct {
	struct ContentServer CS;
	struct ContentClient CC;
} ***IndexServer;

// Functions
void decodePDU(const char* pdu);
void contentRegistration(struct PDU *pdu, const struct ContentServer* CS);



/* Extract data from PDU from Peer here*/
void handleData(int clientSocket) {
	
	char buf[BUFLEN];
	size_t bytesReceived;

	printf("Handling Data from PDU...\n");
	bytesReceived = recv(clientSocket, buf, sizeof(buf), 0);
	if (bytesReceived < 0) {
		printf("...error receiving data\n");
		close(clientSocket);
		exit(1);
	}
	buf[bytesReceived] = '\0';

	// Decode PDU received from Peer
	decodePDU(buf);

	close(clientSocket);
	printf("...handling data complete!\n");
}

/* PDU Decoder to determine service needed i.e. R, T, S, O*/
void decodePDU(const char* pdu) {
	
	printf("Decoding PDU...\n");
	// Check PDU
	if (pdu == NULL || pdu[0] == '0') {
		printf("...invalid PDU\n");
		// send E type PDU
		return;
	}

	char pduType = pdu[0];
	printf("PDU Type: %c", pduType);	

	switch (pduType) {
		case 'R':
		case 'r':
			printf("...received PDU type R\n");
			// TODO
			break;
		case 'T':
		case 't':
			printf("...received PDU type T\n");
			// TODO
			break;
		case 'S':
		case 's':
			printf("...received PDU type S\n");
			// TODO
			break;
		case 'O':
		case 'o':
			printf("...received PDU type O\n");
			// TODO contentList(&IS);
			break;
		default:
			printf("...received PDU type NULL\n");
			break;
	}
	printf("...decoding PDU complete!\n");
}

/* Content Registration */
void contentRegistration(struct PDU *pdu, const struct ContentServer* CS) {

	// Initialize temp type R PDU
	struct R tempPDU;
	tempPDU.type = 'R';

	// Decode data of PDU to Type R PDU
	printf("...formatting\n");
/*
	memset(tempPDU->peerName, '\0', PEERNAMESIZE);
	strncpy(tempPDU->peerName, pdu->data + 1, PEERNAMESIZE);
	tempPDU->peerName[PEERNAMESIZE] = '\0';
	
	memset(tempPDU->peerName, '\0', CONTENTNAMESIZE);
	strncpy(tempPDU->contentName, pdu->data + PEERNAMSIZE + 1, CONTENTNAMESIZE);
	tempPDU->contentName[CONTENTNAMESIZE] = '\0';
	
	memset(tempPDU->peerName, '\0', ADDRSIZE);
	strncpy(tempPDU->address, pdu->data + PEERNAMESIZE + CONTENTNAMESIZE + 1, ADDRSIZE);
	tempPDU->address[ADDRSIZE] = '\0';
*/
	// Search for Existing Content Server based on content name

	// Create Content Server
	struct ContentServer* tempContentServer = (struct ContentServer*)malloc(sizeof(struct ContentServer));
	if (!tempContentServer) {
		printf("...error\n");
		// Send E-type PDU
		exit(1);
	}
	
	// Copy data to new node
/*
	strncpy(tempContentServer->peerName, PEERNAMESIZE - 1);
	tempContentServer->peerName[sizeof(newPeer->Peername) - 1] = '\0';

	strncpy(tempContentServer->contentName, CONTENTNAMESIZE - 1);
	tempContentServer->contentName[sizeof(newPeer->contentName) - 1] = '\0';

	// Add Content Server to Index Server array
	IS->serverBuffer = realloc(IS->serverBuffer, (IS->serverCount + 1) * sizeof(struct ContentServer));

	// Copy new server to buffer
	IS->serverBuffer[IS->serverCount] = *CS;
	IS->serverCount++;
*/	
	printf("...content registration complete!\n");
}

/* Searching for Content */
void contentSearch(const struct S* pdu) {

	printf("Searching Content...\n");
	
	// Initialize temp S type PDU
	printf("...initializing temp PDU\n");
	struct S tempPDU;
	tempPDU.type = 'S';

	// Copy Peer name to temp PDU
	strcpy(tempPDU.peerName, pdu->peerName);

	printf("...searching\n");
	// Search for content server using peer name and content name
	int i;
/*
	for (i = 0; i < (sizeof(IS->serverBuffer) / sizeof(IS->serverBuffer[0])); ++i) {
		// If condition

		if (strcmp(pdu->contentName, IS->serverBuffer[i].contentName) == 0) {
			// Copy Address to temp PDU
			printf("...match hit\n");
			strcpy(tempPDU.address, IS->serverBuffer[i].address); // TODO
			return tempPDU;
		}

	}
*/
	// If here, content not found
	printf("...match miss\n");
	// TODO return(1);

	// Send E Type PDU
	// TODO

	printf("...content search complete!\n");
}

/* Content De-Registration */
void contentDeRegistration(const struct PDU* pdu) {

	// Search for content name
	// TODO searchContent( , );

	// De-Register Content

	
	// Send A type PDU

	printf("...content de-registration complete!\n");
}

/* List of On-Line Registered Content */
void contentList() {
	
	printf("Printing Registered Peers...\n");

	// Iterate through IndexServer Array
	int i;	
/*
	for (i = 0; i < IS->serverCount; ++i) {
		// TODO printf("Content %s registered to Peer %s\n", IS->serverBuffer[i].contentName, IS->serverBuffer[i].peerName);
	}
*/
}

void updateContents(int contentFlag, struct ContentServer tempCS, struct ContentClient tempCC, // TODO) {
	
	if (contentFlag = 1) { 	// Update Content Server Array
		// TODO
		int i;
		for (i = 0; i < 10; i++) {
		}
	} else {				// Update Content Client Array
		// TODO
		int j;
		for (j = 0; j < 10; j++) {
		}
	}
}

int main(int argc, char *argv[]) {
	
	// Content Server and Content Client
	struct ContentServer CS[10];
	struct ContentClient CC[10];

	// Variables
	int serverSocket, clientSocket;
	struct sockaddr_in serverAddr, clientAddr;
	

	// Create Socket
	printf("Creating Socket...\n");
	if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		printf("...error creating socket\n");
		// TODO send type E pdu
		exit(1);
	}
	
	// Initialize Address of Server
	printf("...initializing address of server\n");
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(0);
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	// Bind Socket
	printf("Binding socket...\n");
	if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
		printf("...error binding socket\n");
		// TODO send type E pdu
		close(serverSocket);
		exit(1);
	}

	// Listen for Requests
	printf("Setting socket to listen...\n");

	if (listen(serverSocket, 1) == -1) {
		printf("...error listening for connections\n");
		// TODO send type E pdu
		close(serverSocket);
		exit(1);
	}
	printf("...listening for requests\n");
	int len;
	len = sizeof(serverAddr);

	struct PDU pdu;
	// MAIN LOOP
	while (1) {
		// Accept connecitons

		if ((clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, 0)) == -1) {
			printf("...error accepting connection");
			// TODO send type E PDU
			close(serverSocket);
			exit(1);
		}

		if (recvfrom(serverSocket, (struct PDU*)&pdu, sizeof(pdu), 0, (struct sockaddr*)&serverAddr, &len) < 0) {
			fprintf(stderr, "...recvfrom error.\n");		
		}
		
		printf("PDU Type: %c\n", &pdu.type);

		// Handle received data
		// TODO handleData(clientSocket, IS);
	}
	
	close(serverSocket);

	return 0;
}
