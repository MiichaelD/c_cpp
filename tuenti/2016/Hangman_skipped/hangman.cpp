#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
// #include <thread>
// #include <chrono>
#include <unordered_map>
#include <list>
#include <fstream>
using namespace std;


#define BUFFER_SIZE 1024
bool PLAYING = true;


class Hangman{
    unordered_map<int, list<string> > m_words;
    int m_chances = 0;
    void buildDictionary(){
        ifstream inFile;
        inFile.open("words.txt");
        string word;
        int size;
        while(!inFile.eof()){
            inFile >> word;
            size = static_cast<int>(word.length());
            m_words[size].emplace_back(std::move(word));
        }
        inFile.close();

    }

    // strin
public:

    Hangman(){
        buildDictionary();
    }

    bool processResponse(char *buffer){
        ++m_chances;
        if (m_chances == 9) //(strstr(buffer,"GAME OVER"))
            return false;

        return true;

    }
};

struct Socket{
    char buffer[BUFFER_SIZE];
    int sockfd, portno;
    struct sockaddr_in serv_addr;
    struct hostent *server;
};

void error(const char *msg){
    perror(msg);
    exit(0);
}

void setupSocket(int argc, char *argv[], Socket &socket1){
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port. Using defaults instead: 52.49.91.111:9988\n", argv[0]);
       socket1.server = gethostbyname("52.49.91.111");
       socket1.portno = 9988;
    } else {
        socket1.server = gethostbyname(argv[1]);
        socket1.portno = atoi(argv[2]);

    }
    socket1.sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket1.sockfd < 0) 
        error("ERROR opening socket");

    if (socket1.server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &socket1.serv_addr, sizeof(socket1.serv_addr));
    socket1.serv_addr.sin_family = AF_INET;
    bcopy((char *)socket1.server->h_addr, 
         (char *)&socket1.serv_addr.sin_addr.s_addr,
         socket1.server->h_length);
    socket1.serv_addr.sin_port = htons(socket1.portno);
    if (connect(socket1.sockfd,(struct sockaddr *) &socket1.serv_addr, sizeof(socket1.serv_addr)) < 0) 
        error("ERROR connecting");
}

void readInput(Socket &socket, Hangman &hangman){
    bzero(socket.buffer, BUFFER_SIZE);
    int n = read(socket.sockfd, socket.buffer, BUFFER_SIZE);
    if (n < 0) 
         error("ERROR reading from socket");
    printf("read: %s\n",socket.buffer);
    if (!hangman.processResponse(socket.buffer)){
        PLAYING = false;
    }
    // std::this_thread::sleep_for (std::chrono::milliseconds(100));
}

void sendOutput(Socket &socket, Hangman &hangman){
    bzero(socket.buffer, BUFFER_SIZE);
    fgets(socket.buffer, BUFFER_SIZE, stdin);
    int n = write(socket.sockfd, socket.buffer, strlen(socket.buffer));
    if (n < 0) 
         error("ERROR writing to socket");

    if (strstr(socket.buffer, "....")){
        PLAYING = false;
    }
}

int main(int argc, char *argv[]){
    Socket socket;
    Hangman hangman;
    setupSocket(argc, argv, socket);
    while(PLAYING){
        readInput(socket, hangman);
        sendOutput(socket, hangman);
    }
    close(socket.sockfd);
    return 0;
}