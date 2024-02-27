#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main (){
    //spincoater ip and port 
    const char* spinCoaterIp = "192.168.121.200";
    const int spinCoaterPort = 47999;

    //crete a UDP socket 
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0){
        std::cerr << "Error creating socket" << std::endl;
        return -1;
    }

    //configure spin coater adress 
    struct sockaddr_in spinCoaterAddr;
    spinCoaterAddr.sin_family = AF_INET;
    spinCoaterAddr.sin_port = htons(spinCoaterPort);
    inet_pton(AF_INET, spinCoaterIp, &spinCoaterAddr.sin_addr);

    //VERSIONreq command structure 
    unsigned char versionReqCommand[] = {
        0x98, 0xFE, //ProtocolID
        0x01, // Protocol version
        0x00, // Sequence num, first seq
        0x03, // cmd_code for VERSIONreq
        0x01, // par_typ for PTYP_NONE, no additional parameter 
        0x00, // par_len, no additional parameter 
    };

    //send the VERSIONreq command 
    ssize_t sentBytes = sendto(sockfd, versionReqCommand, sizeof(versionReqCommand),0, (struct sockaddr*)&spinCoaterAddr, sizeof(spinCoaterAddr));
    
    if (sentBytes < 0){
    std::cerr << "ERROR SENDING VERSIONREQ COMMAND" << std::endl;
    close(sockfd);
    return -1;
    }

    //Listen to VERSIONreq response
    unsigned char responce [1024];
    socklen_t addrLen = sizeof(spinCoaterAddr);
    ssize_t recievedBytes = recvfrom(sockfd,responce, sizeof(responce),0,(struct sockaddr*)&spinCoaterAddr, &addrLen);
    
    if(recievedBytes < 0) {
        std::cerr << " ERRPR RECIEVING VERSIONREQ COMMAND" << std::endl;
        close(sockfd);
        return -1;
    }

    //process the responce 
    for (int i = 0; i <recievedBytes; i++) {
        std::cout << std::hex << (int)responce[i] << "";
    }
    std::cout<<std::endl;

    //close the socket
    close (sockfd);

    return 0;
}