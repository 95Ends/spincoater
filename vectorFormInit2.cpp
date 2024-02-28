#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/time.h>
#include <limits>
#include <vector>
#include <chrono>
#include <thread>

using namespace std;

bool hasTenSecondsPassed (const chrono::steady_clock::time_point& start){
    auto now = chrono::steady_clock::now();
    auto elapsed = chrono::duration_cast<chrono::seconds>(now-start).count();
    return elapsed >=10;

}

    // INITreq command structure
    vector<unsigned char> generateInitReqCommand(unsigned char& sequenceNumber){
        vector<unsigned char> command = {
    0xfe,
    0x98,       // Protocol ID: 0x98FE
    0x01,       // Protocol version: 0x01
    sequenceNumber,       // Sequence number
    0x01,       // INITreq command code (example, adjust as needed)
    0x00,       // Parameter type: No parameter for INITreq
    0x00,       // Length of the command parameter(s): 0 for INITreq
    0x00        // Reserved, set to 0
    // No additional parameters for INITreq
        };
    sequenceNumber = (sequenceNumber + 1) % 255;

    return command;
    }


    // VERSIONreq command structure
    vector <unsigned char> generateVersReqCommand(unsigned char& sequenceNumber) {
        vector<unsigned char> command = {
    0xfe,
    0x98,       // Protocol ID: 0x98FE
    0x01,       // Protocol version: 0x01
    sequenceNumber,       // Sequence number: 
    0x03,       // VERSIONreq command code
    0x01,       // Parameter type: No parameter for VERSIONreq
    0x00,       // Length of the command parameter(s): 0 for VERSIONreq
    0x00        // Reserved, set to 0
        };
    
    sequenceNumber = (sequenceNumber + 1) % 255;

    return command;
    }
   
   //STATreq command structure
    vector <unsigned char> generateStatReqCommand(unsigned char& sequenceNumber) {
        vector <unsigned char> command = {
    0xfe,
    0x98,       // Protocol ID: 0x98FE
    0x01,       // Protocol version: 0x01
    sequenceNumber,       // Sequence number
    0x0e,       // STATreq command code 
    0x01,       // Parameter type
    0x00,       // Length of the command parameter(s)
    0x00,       // Reserved, set to 0
        };

    sequenceNumber = (sequenceNumber +1 ) % 255;

    return command;
    }

    //WDENAreq command structure
    vector <unsigned char> generateWdenaReqCommand (unsigned char& sequenceNumber) {
        vector <unsigned char> command = {
    0xfe,
    0x98,       // Protocol ID: 0x98FE
    0x01,       // Protocol version: 0x01
    sequenceNumber,       // Sequence number: 2
    0x11,       // WDENAreq command code 
    0x05,       // Parameter type
    0x02,       // Length of the command parameter(s)
    0x00,       // Reserved, set to 0
    0x01,
    0x00 
    };

    sequenceNumber = (sequenceNumber +1 ) % 255;

    return command;
    }

    //PACTreq command structure
    vector <unsigned char> generatePactReqCommand (unsigned char& sequenceNumber) {
        vector <unsigned char> command = {
    0xfe,
    0x98, // Protocol ID: 0x98FE
    0x01,       // Protocol version: 0x01
    sequenceNumber,       // Sequence number
    0x15,       // PACTreq command code 
    0x05,       // Parameter type
    0x02,       // Length of the command parameter(s)
    0x00,        // Reserved, set to 0
    0x00,       //  additional parameters 
    0x00
    };

    sequenceNumber = (sequenceNumber +1 ) % 255;
    return command;
    }


    //VELreq command structure (start with 1500RPM)
    vector <unsigned char> generateVelocityReqCommand (unsigned char& sequenceNumber, unsigned char& velPar1, unsigned char& velPar2) {
        vector <unsigned char> command = {
    0xfe,
    0x98, // Protocol ID: 0x98FE
    0x01,       // Protocol version: 0x01
    sequenceNumber,       // Sequence number
    0x0b,       // VELreq command code 
    0x08,       // Parameter type
    0x04,       // Length of the command parameter(s)
    0x00,        // Reserved, set to 0
    velPar1,       // addititinal parameters
    velPar2,
    0x00,
    0x00
    };

    sequenceNumber = (sequenceNumber +1 ) % 255;

    return command;
    }


    //STOPreq command structure
    vector <unsigned char> generateStopReqCommand (unsigned char& sequenceNumber) {
        vector <unsigned char> command = {
    0xfe,
    0x98, // Protocol ID: 0x98FE
    0x01,       // Protocol version: 0x01
    sequenceNumber,       // Sequence number
    0x0c,       // STOPreq command code 
    0x00,       // Parameter type
    0x00,       // Length of the command parameter(s)
    0x00        // Reserved, set to 0
    
    };
    sequenceNumber = (sequenceNumber +1 ) % 255;

    return command;
    }

    //command to login as admin
    vector <unsigned char> generateLoginReqCommand (unsigned char& sequenceNumber) {
        vector <unsigned char> command = {
    0xfe,
    0x98, // Protocol ID: 0x98FE
    0x01,       // Protocol version: 0x01
    sequenceNumber,       // Sequence number
    0x10,       // VELreq command code 
    0x07,       // Parameter type
    0x04,       // Length of the command parameter(s)
    0x00,        // Reserved, set to 0
    0x52,       // addititinal parameters
    0x04,
    0x00,
    0x00
    };

    sequenceNumber = (sequenceNumber +1 ) % 255;

    return command;
    }

    //PRDVAlreq command structure to read error
    vector <unsigned char> generatePrdvalReqCommandError (unsigned char& sequenceNumber) {
        vector <unsigned char> command = {
    0xfe,
    0x98,       // Protocol ID: 0x98FE
    0x01,       // Protocol version: 0x01
    sequenceNumber,       // Sequence number
    0x05,       // Command code 
    0x0b,       // Parameter type
    0x08,       // Length of the command parameter(s)
    0x00,        // Reserved, set to 0
    0xc7,       // addititinal parameters
    0x09,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00
    };

    sequenceNumber = (sequenceNumber +1 ) % 255;

    return command;
    }

    //PRDVAlreq command structure to read current encoder angle value
    vector <unsigned char> generatePrdvalReqCommandAngle (unsigned char& sequenceNumber) {
        vector <unsigned char> command = {
    0xfe,
    0x98,       // Protocol ID: 0x98FE
    0x01,       // Protocol version: 0x01
    sequenceNumber,       // Sequence number
    0x05,       // Command code 
    0x0b,       // Parameter type
    0x08,       // Length of the command parameter(s)
    0x00,        // Reserved, set to 0
    0x63,       // addititinal parameters
    0x09,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00
    };

    sequenceNumber = (sequenceNumber +1 ) % 255;

    return command;
    }

    //PWRVALreq command structure command to deactivate inertia mangemant
    vector <unsigned char> generatePwrvalReqCommandInertiaZero (unsigned char& sequenceNumber) {
        vector <unsigned char> command = {
    0xfe,
    0x98, // Protocol ID: 0x98FE
    0x01,       // Protocol version: 0x01
    sequenceNumber,       // Sequence number
    0x06,       // PRDVALreq command code 
    0x0e,       // Parameter type
    0x18,       // Length of the command parameter(s)
    0x00,        // Reserved, set to 0
    0xf4,       //Additional parameters
    0x03,
    0x04,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x05,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00
        };

    sequenceNumber = (sequenceNumber +1 ) % 255;

    return command;
    }

    //PWRVALreq command structure command to set VlimUsr 
    vector <unsigned char> generatePwrvalReqCommandVlimUsr (unsigned char& sequenceNumber) {
        vector <unsigned char> command = {
    0xfe,
    0x98, // Protocol ID: 0x98FE
    0x01,       // Protocol version: 0x01
    sequenceNumber,       // Sequence number
    0x06,       // PRDVALreq command code 
    0x0e,       // Parameter type
    0x18,       // Length of the command parameter(s)
    0x00,        // Reserved, set to 0
    0xea,       //Additional parameters
    0x03,
    0x04,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0xA0,
    0x86,
    0x01,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00
        };

    sequenceNumber = (sequenceNumber +1 ) % 255;

    return command;
    }


     //PWRVALreq command structure command to set Amax 
    vector <unsigned char> generatePwrvalReqCommandAmax (unsigned char& sequenceNumber) {
        vector <unsigned char> command = {
    0xfe,
    0x98, // Protocol ID: 0x98FE
    0x01,       // Protocol version: 0x01
    sequenceNumber,       // Sequence number
    0x06,       // PRDVALreq command code 
    0x0e,       // Parameter type
    0x18,       // Length of the command parameter(s)
    0x00,        // Reserved, set to 0
    0xeb,       //Additional parameters
    0x03,
    0x04,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x10,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00
        };

    sequenceNumber = (sequenceNumber +1 ) % 255;

    return command;
    }

    //PWRVALreq command structure command to set Dmax 
    vector <unsigned char> generatePwrvalReqCommandDmax (unsigned char& sequenceNumber) {
        vector <unsigned char> command = {
    0xfe,
    0x98, // Protocol ID: 0x98FE
    0x01,       // Protocol version: 0x01
    sequenceNumber,       // Sequence number
    0x06,       // PRDVALreq command code 
    0x0e,       // Parameter type
    0x18,       // Length of the command parameter(s)
    0x00,        // Reserved, set to 0
    0xec,       //Additional parameters
    0x03,
    0x04,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x10,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00
        };

    sequenceNumber = (sequenceNumber +1 ) % 255;

    return command;
    }

    //PWRVALreq command structure command to set Pmax 
    vector <unsigned char> generatePwrvalReqCommandPmax (unsigned char& sequenceNumber) {
        vector <unsigned char> command = {
    0xfe,
    0x98, // Protocol ID: 0x98FE
    0x01,       // Protocol version: 0x01
    sequenceNumber,       // Sequence number
    0x06,       // PRDVALreq command code 
    0x0e,       // Parameter type
    0x18,       // Length of the command parameter(s)
    0x00,        // Reserved, set to 0
    0xed,       //Additional parameters
    0x03,
    0x04,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x01,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00
        };

    sequenceNumber = (sequenceNumber +1 ) % 255;

    return command;
    }

    int main() {

    unsigned char responce [1024];
    int motorAngle = 0;
    bool shouldStop = false; //bool to stop after 20seconds of searching for zero angle 
    unsigned char sequenceNumber =0x00;//command sequence counter
    struct timeval tv;//Timeval struct for timeout definition
    tv.tv_sec = 15; //15sec timout
    tv.tv_usec = 0;

    // Spin coater IP and port
    const char* spinCoaterIp = "192.168.121.200";
    const int spinCoaterPort = 47999;
    //PLC IP and port
    const char* plcIp = "192.168.121.1";
    const int plcPort = 2000;
    const int plcPortListen = 2001;

    // Create a UDP socket
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        std::cerr << "Error creating socket" << std::endl;
        return -1;
    }

    // Configure spin coater address
    struct sockaddr_in spinCoaterAddr;
    memset(&spinCoaterAddr, 0, sizeof(spinCoaterAddr)); // Clear structure
    spinCoaterAddr.sin_family = AF_INET;
    spinCoaterAddr.sin_port = htons(spinCoaterPort);
    inet_pton(AF_INET, spinCoaterIp, &spinCoaterAddr.sin_addr);


    //..............................
    // Send the INITreq command

    auto initReqCommand = generateInitReqCommand(sequenceNumber);
    ssize_t sentBytes = sendto(sockfd, initReqCommand.data(), initReqCommand.size(), 0,
                               (struct sockaddr*)&spinCoaterAddr, sizeof(spinCoaterAddr));
    if (sentBytes < 0) {
        std::cerr << "Error sending INITreq command" << std::endl;
        close(sockfd);
        return -1;
    }
    else {
     std::cerr << "INITreq command sent" << std::endl;
     std::cout << std::hex << (int)sequenceNumber << " ";
    }
    
     // Listen for the response
    unsigned char response[1024]; // Adjust size based on expected response
    socklen_t addrLen = sizeof(spinCoaterAddr);
    ssize_t receivedBytes = recvfrom(sockfd, response, sizeof(response), 0,
                                     (struct sockaddr*)&spinCoaterAddr, &addrLen);

    if (receivedBytes < 0) {
        std::cerr << "Error receiving VERSIONcon response" << std::endl;
        close(sockfd);
        return -1;
    }
    // Process and print the response
    std::cout << "Received response to INITreq: ";
    for (int i = 0; i < receivedBytes; ++i) {
        std::cout << std::hex << (int)response[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Waiting for 10 seconds..." << std::endl;
    //...............................................



    // Wait for 10 seconds
    sleep(10);

    //.....................................
    // Send the VERSIONreq command

    auto versionReqCommand = generateVersReqCommand(sequenceNumber);

    sentBytes = sendto(sockfd, versionReqCommand.data(), versionReqCommand.size(), 0,
                               (struct sockaddr*)&spinCoaterAddr, sizeof(spinCoaterAddr));
    if (sentBytes < 0) {
        std::cerr << "Error sending VERSIONreq command" << std::endl;
        close(sockfd);
        return -1;
    }
    else {
        std::cout << "VERSIONreq command sent..." << std::endl;
         std::cout << std::hex << (int)sequenceNumber << " ";
    }
   

    receivedBytes = recvfrom(sockfd, response, sizeof(response), 0,
                                     (struct sockaddr*)&spinCoaterAddr, &addrLen);

    if (receivedBytes < 0) {
        std::cerr << "Error receiving VERSIONreq response" << std::endl;
        close(sockfd);
        return -1;
    }

    // Process and print the response
    std::cout << "Received response from VERSIONreq: ";
    for (int i = 0; i < receivedBytes; ++i) {
        std::cout << std::hex << (int)response[i] << " ";
    }
    std::cout << std::endl;

    //............................................

    //.........................................
    // Send the STATreq command
    
    auto statReqCommand = generateStatReqCommand(sequenceNumber);

    
    sentBytes = sendto(sockfd, statReqCommand.data(), statReqCommand.size(), 0,
                               (struct sockaddr*)&spinCoaterAddr, sizeof(spinCoaterAddr));
    if (sentBytes < 0) {
        std::cerr << "Error sending STATreq command" << std::endl;
        close(sockfd);
        return -1;
    }
    else {
        std::cout << "STATreq command sent..." << std::endl;
         std::cout << std::hex << (int)sequenceNumber << " ";
        
    }
    

    receivedBytes = recvfrom(sockfd, response, sizeof(response), 0,
                                     (struct sockaddr*)&spinCoaterAddr, &addrLen);

    if (receivedBytes < 0) {
        std::cerr << "Error receiving WDSTATreqENAreq response" << std::endl;
        close(sockfd);
        return -1;
    }

    // Process and print the response
    std::cout << "Received response from STATreq: ";
    for (int i = 0; i < receivedBytes; ++i) {
        std::cout << std::hex << (int)response[i] << " ";
    }
    std::cout << std::endl;

    //............................................

    //.........................................
    // Send the LOGINreq command
    
    auto loginReqCommand = generateLoginReqCommand(sequenceNumber);

    
    sentBytes = sendto(sockfd, loginReqCommand.data(), loginReqCommand.size(), 0,
                               (struct sockaddr*)&spinCoaterAddr, sizeof(spinCoaterAddr));
    if (sentBytes < 0) {
        std::cerr << "Error sending LOGINreq command" << std::endl;
        close(sockfd);
        return -1;
    }
    else {
        std::cout << "LOGINreq command sent..." << std::endl;
         std::cout << std::hex << (int)sequenceNumber << " ";
        
    }
    

    receivedBytes = recvfrom(sockfd, response, sizeof(response), 0,
                                     (struct sockaddr*)&spinCoaterAddr, &addrLen);

    if (receivedBytes < 0) {
        std::cerr << "Error receiving LOGINreq response" << std::endl;
        close(sockfd);
        return -1;
    }

    // Process and print the response
    std::cout << "Received response from LOGINreq: ";
    for (int i = 0; i < receivedBytes; ++i) {
        std::cout << std::hex << (int)response[i] << " ";
    }
    std::cout << std::endl;

    //............................................

    //.........................................
    // Send the PWRVALreq command
    
    auto pwrvalReqCommandInertiaZero = generatePwrvalReqCommandInertiaZero(sequenceNumber);

    sentBytes = sendto(sockfd, pwrvalReqCommandInertiaZero.data(), pwrvalReqCommandInertiaZero.size(), 0,
                               (struct sockaddr*)&spinCoaterAddr, sizeof(spinCoaterAddr));
    if (sentBytes < 0) {
        std::cerr << "Error sending pwriteValReq command" << std::endl;
        close(sockfd);
        return -1;
    }
    else {
        std::cout << "pwriteValReq command sent..." << std::endl;
         std::cout << std::hex << (int)sequenceNumber << " ";
        
    }
    

    receivedBytes = recvfrom(sockfd, response, sizeof(response), 0,
                                     (struct sockaddr*)&spinCoaterAddr, &addrLen);

    if (receivedBytes < 0) {
        std::cerr << "Error receiving pwriteValReq response" << std::endl;
        close(sockfd);
        return -1;
    }

    // Process and print the response
    std::cout << "Received response from pwriteValReq: ";
    for (int i = 0; i < receivedBytes; ++i) {
        std::cout << std::hex << (int)response[i] << " ";
    }
    std::cout << std::endl;

    //............................................


    //.........................................
    // Send the PWRVALreq command
    
    auto pwrvalReqCommandVlimUsr = generatePwrvalReqCommandVlimUsr(sequenceNumber);

    sentBytes = sendto(sockfd, pwrvalReqCommandVlimUsr.data(), pwrvalReqCommandVlimUsr.size(), 0,
                               (struct sockaddr*)&spinCoaterAddr, sizeof(spinCoaterAddr));
    if (sentBytes < 0) {
        std::cerr << "Error sending pwriteValReq VlimUsr command" << std::endl;
        close(sockfd);
        return -1;
    }
    else {
        std::cout << "pwriteValReq VlimUsr command sent..." << std::endl;
         std::cout << std::hex << (int)sequenceNumber << " ";
        
    }
    

    receivedBytes = recvfrom(sockfd, response, sizeof(response), 0,
                                     (struct sockaddr*)&spinCoaterAddr, &addrLen);

    if (receivedBytes < 0) {
        std::cerr << "Error receiving pwriteValReq VlimUsr response" << std::endl;
        close(sockfd);
        return -1;
    }

    // Process and print the response
    std::cout << "Received response from pwriteValReq VlimUsr: ";
    for (int i = 0; i < receivedBytes; ++i) {
        std::cout << std::hex << (int)response[i] << " ";
    }
    std::cout << std::endl;

    //............................................
    
    /*
    //.........................................
    // Send the PWRVALreq command
    auto pwrvalReqCommandAmax = generatePwrvalReqCommandAmax(sequenceNumber);

    sentBytes = sendto(sockfd, pwrvalReqCommandAmax.data(), pwrvalReqCommandAmax.size(), 0,
                               (struct sockaddr*)&spinCoaterAddr, sizeof(spinCoaterAddr));
    if (sentBytes < 0) {
        std::cerr << "Error sending pwriteValReq Amax command" << std::endl;
        close(sockfd);
        return -1;
    }
    else {
        std::cout << "pwriteValReq Amax command sent..." << std::endl;
         std::cout << std::hex << (int)sequenceNumber << " ";
        
    }
    

    receivedBytes = recvfrom(sockfd, response, sizeof(response), 0,
                                     (struct sockaddr*)&spinCoaterAddr, &addrLen);

    if (receivedBytes < 0) {
        std::cerr << "Error receiving pwriteValReq Amax response" << std::endl;
        close(sockfd);
        return -1;
    }

    // Process and print the response
    std::cout << "Received response from pwriteValReq Amax: ";
    for (int i = 0; i < receivedBytes; ++i) {
        std::cout << std::hex << (int)response[i] << " ";
    }
    std::cout << std::endl;

    //............................................

    //.........................................
    // Send the PWRVALreq command
    auto pwrvalReqCommandDmax = generatePwrvalReqCommandDmax(sequenceNumber);

    sentBytes = sendto(sockfd, pwrvalReqCommandDmax.data(), pwrvalReqCommandDmax.size(), 0,
                               (struct sockaddr*)&spinCoaterAddr, sizeof(spinCoaterAddr));
    if (sentBytes < 0) {
        std::cerr << "Error sending pwriteValReq Dmax command" << std::endl;
        close(sockfd);
        return -1;
    }
    else {
        std::cout << "pwriteValReq Dmax command sent..." << std::endl;
         std::cout << std::hex << (int)sequenceNumber << " ";
        
    }
    

    receivedBytes = recvfrom(sockfd, response, sizeof(response), 0,
                                     (struct sockaddr*)&spinCoaterAddr, &addrLen);

    if (receivedBytes < 0) {
        std::cerr << "Error receiving pwriteValReq Dmax response" << std::endl;
        close(sockfd);
        return -1;
    }

    // Process and print the response
    std::cout << "Received response from pwriteValReq Dmax: ";
    for (int i = 0; i < receivedBytes; ++i) {
        std::cout << std::hex << (int)response[i] << " ";
    }
    std::cout << std::endl;

    //............................................

    //.........................................
    // Send the PWRVALreq command
    auto pwrvalReqCommandPmax = generatePwrvalReqCommandPmax(sequenceNumber);

    sentBytes = sendto(sockfd, pwrvalReqCommandPmax.data(), pwrvalReqCommandPmax.size(), 0,
                               (struct sockaddr*)&spinCoaterAddr, sizeof(spinCoaterAddr));
    if (sentBytes < 0) {
        std::cerr << "Error sending pwriteValReq Pmax command" << std::endl;
        close(sockfd);
        return -1;
    }
    else {
        std::cout << "pwriteValReq Pmax command sent..." << std::endl;
         std::cout << std::hex << (int)sequenceNumber << " ";
        
    }
    

    receivedBytes = recvfrom(sockfd, response, sizeof(response), 0,
                                     (struct sockaddr*)&spinCoaterAddr, &addrLen);

    if (receivedBytes < 0) {
        std::cerr << "Error receiving pwriteValReq Pmax response" << std::endl;
        close(sockfd);
        return -1;
    }

    // Process and print the response
    std::cout << "Received response from pwriteValReq Pmax: ";
    for (int i = 0; i < receivedBytes; ++i) {
        std::cout << std::hex << (int)response[i] << " ";
    }
    std::cout << std::endl;

    //............................................

    //.........................................
    // Send the WDENAreq command
    
    auto wdenaReqCommand = generateWdenaReqCommand(sequenceNumber);

    
    sentBytes = sendto(sockfd, wdenaReqCommand.data(), wdenaReqCommand.size(), 0,
                               (struct sockaddr*)&spinCoaterAddr, sizeof(spinCoaterAddr));
    if (sentBytes < 0) {
        std::cerr << "Error sending WDENAreq command" << std::endl;
        close(sockfd);
        return -1;
    }
    else {
        std::cout << "WDENAreq command sent..." << std::endl;
         std::cout << std::hex << (int)sequenceNumber << " ";
        
    }
    

    receivedBytes = recvfrom(sockfd, response, sizeof(response), 0,
                                     (struct sockaddr*)&spinCoaterAddr, &addrLen);

    if (receivedBytes < 0) {
        std::cerr << "Error receiving WDENAreq response" << std::endl;
        close(sockfd);
        return -1;
    }

    // Process and print the response
    std::cout << "Received response from WDENAreq: ";
    for (int i = 0; i < receivedBytes; ++i) {
        std::cout << std::hex << (int)response[i] << " ";
    }
    std::cout << std::endl;

    //............................................
    */

    //.........................................
    // Send the VELreq command
    

    std::cout << "Press Enter to start the motor..." << std::endl;
    std::cin.get();
    
    
    unsigned char velPar1 = 0x35;
    unsigned char velPar2 = 0x85;

    auto velReqCommand = generateVelocityReqCommand(sequenceNumber,velPar1,velPar2);
    sentBytes = sendto(sockfd, velReqCommand.data(), velReqCommand.size(), 0,
                               (struct sockaddr*)&spinCoaterAddr, sizeof(spinCoaterAddr));
    if (sentBytes < 0) {
        std::cerr << "Error sending VElreq command" << std::endl;
        close(sockfd);
        return -1;
    }
    else {
        std::cout << "VELreq command sent..." << std::endl;
         std::cout << std::hex << (int)sequenceNumber << " ";
        
    }
    

    receivedBytes = recvfrom(sockfd, response, sizeof(response), 0,
                                     (struct sockaddr*)&spinCoaterAddr, &addrLen);

    if (receivedBytes < 0) {
        std::cerr << "Error receiving VElreq response" << std::endl;
        close(sockfd);
        return -1;
    }

    // Process and print the response
    std::cout << "Received response from VELreq: ";
    for (int i = 0; i < receivedBytes; ++i) {
        std::cout << std::hex << (int)response[i] << " ";
    }
    std::cout << std::endl;

    //............................................

    sleep(5);

    //.........................................
    // Send the STATreq command
    
    statReqCommand = generateStatReqCommand(sequenceNumber);

    
    sentBytes = sendto(sockfd, statReqCommand.data(), statReqCommand.size(), 0,
                               (struct sockaddr*)&spinCoaterAddr, sizeof(spinCoaterAddr));
    if (sentBytes < 0) {
        std::cerr << "Error sending STATreq command" << std::endl;
        close(sockfd);
        return -1;
    }
    else {
        std::cout << "STATreq command sent..." << std::endl;
         std::cout << std::hex << (int)sequenceNumber << " ";
        
    }
    

    receivedBytes = recvfrom(sockfd, response, sizeof(response), 0,
                                     (struct sockaddr*)&spinCoaterAddr, &addrLen);

    if (receivedBytes < 0) {
        std::cerr << "Error receiving WDSTATreqENAreq response" << std::endl;
        close(sockfd);
        return -1;
    }

    // Process and print the response
    std::cout << "Received response from STATreq: ";
    for (int i = 0; i < receivedBytes; ++i) {
        std::cout << std::hex << (int)response[i] << " ";
    }
    std::cout << std::endl;

    //............................................

    //.........................................
    // Send the VELreq command
    std::cout << "Press Enter to slow the motor..." << std::endl;
    std::cin.get();
    
    velPar1 = 0x00;
    velPar2 = 0x01;

    velReqCommand = generateVelocityReqCommand(sequenceNumber,velPar1,velPar2);
    sentBytes = sendto(sockfd, velReqCommand.data(), velReqCommand.size(), 0,
                               (struct sockaddr*)&spinCoaterAddr, sizeof(spinCoaterAddr));
    if (sentBytes < 0) {
        std::cerr << "Error sending VElreq command" << std::endl;
        close(sockfd);
        return -1;
    }
    else {
        std::cout << "VELreq command sent..." << std::endl;
         std::cout << std::hex << (int)sequenceNumber << " ";
        
    }
    

    receivedBytes = recvfrom(sockfd, response, sizeof(response), 0,
                                     (struct sockaddr*)&spinCoaterAddr, &addrLen);

    if (receivedBytes < 0) {
        std::cerr << "Error receiving VElreq response" << std::endl;
        close(sockfd);
        return -1;
    }

    // Process and print the response
    std::cout << "Received response from VELreq: ";
    for (int i = 0; i < receivedBytes; ++i) {
        std::cout << std::hex << (int)response[i] << " ";
    }
    std::cout << std::endl;

    //............................................

    //.........................................
    // Homing sequence
    // Send the PRDVALreq command
    auto start = chrono::steady_clock::now();
    while (!shouldStop){

    auto prdvalReqCommandAngle = generatePrdvalReqCommandAngle
    (sequenceNumber);

    
    sentBytes = sendto(sockfd, prdvalReqCommandAngle.data(), prdvalReqCommandAngle.size(), 0,
                               (struct sockaddr*)&spinCoaterAddr, sizeof(spinCoaterAddr));
    if (sentBytes < 0) {
        std::cerr << "Error sending PRDVALreq command" << std::endl;
        close(sockfd);
        return -1;
    }
    else {
        std::cout << "WDENAreq PRDVALreq sent..." << std::endl;
         std::cout << std::hex << (int)sequenceNumber << " ";
        
    }
    

    receivedBytes = recvfrom(sockfd, response, sizeof(response), 0,
                                     (struct sockaddr*)&spinCoaterAddr, &addrLen);

    

    if (receivedBytes < 0) {
        std::cerr << "Error receiving PRDVALreq response" << std::endl;
        close(sockfd);
        return -1;
    }

    // Process and print the response
    std::cout << "Received response from PRDVALreq: ";
    for (int i = 0; i < receivedBytes; ++i) {
        std::cout << std::hex << (int)response[i] << " ";
    }
    std::cout << std::endl;

    motorAngle = (int)responce[16];
     
    if (motorAngle > 1 && motorAngle < 5) {

    auto stopReqCommand = generateStopReqCommand(sequenceNumber);

    
    sentBytes = sendto(sockfd, stopReqCommand.data(), stopReqCommand.size(), 0,
                               (struct sockaddr*)&spinCoaterAddr, sizeof(spinCoaterAddr));
    if (sentBytes < 0) {
        std::cerr << "Error sending STOPreq command" << std::endl;
        close(sockfd);
        return -1;
    }
    else {
        std::cout << "Found Home! STOPreq command sent..." << std::endl;
         std::cout << std::hex << (int)sequenceNumber << " ";
        
    }
    

    receivedBytes = recvfrom(sockfd, response, sizeof(response), 0,
                                     (struct sockaddr*)&spinCoaterAddr, &addrLen);

    if (receivedBytes < 0) {
        std::cerr << "Error receiving STOPreq response" << std::endl;
        close(sockfd);
        return -1;
    }

    // Process and print the response
    std::cout << "Received response from STOPreq: ";
    for (int i = 0; i < receivedBytes; ++i) {
        std::cout << std::hex << (int)response[i] << " ";
    }
    std::cout << std::endl;
    
    shouldStop = true;
    break; 
        }

    auto now = chrono::steady_clock::now();
    if (chrono::duration_cast<chrono::seconds>(now-start).count() >=60) {

        auto stopReqCommand = generateStopReqCommand(sequenceNumber);

    
    sentBytes = sendto(sockfd, stopReqCommand.data(), stopReqCommand.size(), 0,
                               (struct sockaddr*)&spinCoaterAddr, sizeof(spinCoaterAddr));
    if (sentBytes < 0) {
        std::cerr << "Error sending STOPreq command" << std::endl;
        close(sockfd);
        return -1;
    }
    else {
        std::cout << "Didnt finde home. STOPreq command sent ..." << std::endl;
         std::cout << std::hex << (int)sequenceNumber << " ";
        
    }
    

    receivedBytes = recvfrom(sockfd, response, sizeof(response), 0,
                                     (struct sockaddr*)&spinCoaterAddr, &addrLen);

    if (receivedBytes < 0) {
        std::cerr << "Error receiving STOPreq response" << std::endl;
        close(sockfd);
        return -1;
    }

    // Process and print the response
    std::cout << "Received response from STOPreq: ";
    for (int i = 0; i < receivedBytes; ++i) {
        std::cout << std::hex << (int)response[i] << " ";
    }
    std::cout << std::endl;
    break;
    } 

    this_thread::sleep_for(chrono::milliseconds(100));

    }


    /*//.........................................
    // Send STOPreq command
    
    std::cout << "Press Enter to stop the motor..." << std::endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

    auto stopReqCommand = generateStopReqCommand(sequenceNumber);

    
    sentBytes = sendto(sockfd, stopReqCommand.data(), stopReqCommand.size(), 0,
                               (struct sockaddr*)&spinCoaterAddr, sizeof(spinCoaterAddr));
    if (sentBytes < 0) {
        std::cerr << "Error sending STOPreq command" << std::endl;
        close(sockfd);
        return -1;
    }
    else {
        std::cout << "STOPreq command sent..." << std::endl;
         std::cout << std::hex << (int)sequenceNumber << " ";
        
    }
    

    receivedBytes = recvfrom(sockfd, response, sizeof(response), 0,
                                     (struct sockaddr*)&spinCoaterAddr, &addrLen);

    if (receivedBytes < 0) {
        std::cerr << "Error receiving STOPreq response" << std::endl;
        close(sockfd);
        return -1;
    }

    // Process and print the response
    std::cout << "Received response from STOPreq: ";
    for (int i = 0; i < receivedBytes; ++i) {
        std::cout << std::hex << (int)response[i] << " ";
    }
    std::cout << std::endl;

    //............................................

    //.........................................
    // Send the PRDVALreq command
    
    auto prdvalReqCommandAngle = generatePrdvalReqCommandAngle
    (sequenceNumber);

    
    sentBytes = sendto(sockfd, prdvalReqCommandAngle.data(), prdvalReqCommandAngle.size(), 0,
                               (struct sockaddr*)&spinCoaterAddr, sizeof(spinCoaterAddr));
    if (sentBytes < 0) {
        std::cerr << "Error sending PRDVALreq command" << std::endl;
        close(sockfd);
        return -1;
    }
    else {
        std::cout << "WDENAreq PRDVALreq sent..." << std::endl;
         std::cout << std::hex << (int)sequenceNumber << " ";
        
    }
    

    receivedBytes = recvfrom(sockfd, response, sizeof(response), 0,
                                     (struct sockaddr*)&spinCoaterAddr, &addrLen);

    motorAngle = responce[15];

    if (receivedBytes < 0) {
        std::cerr << "Error receiving PRDVALreq response" << std::endl;
        close(sockfd);
        return -1;
    }

    // Process and print the response
    std::cout << "Received response from PRDVALreq: ";
    for (int i = 0; i < receivedBytes; ++i) {
        std::cout << std::hex << (int)response[i] << " ";
    }
    std::cout << std::endl;

    *///............................................
}

