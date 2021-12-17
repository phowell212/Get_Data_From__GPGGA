#include <iostream>
#include <unistd.h>
//#include <fstream>
#define CSIZE 52
using namespace std;

void getcords(const char* GPGGA, int size, char* cords){

    // loop
    for(int i = 0; i < size; i++){
        // Checking for GPGGA
        if(GPGGA[i] == '$' && GPGGA[i + 1] == 'G' && GPGGA[i + 2] == 'P' && GPGGA[i + 3] == 'G'){
            i+=7; // to jump
            // dump GPGGA into cords
            for(int j = 0; j < CSIZE; j++){
                cords[j]=GPGGA[i];
                i++;
            }
        }
    }
}

// detection if the enter key is being pressed
int kbhit(){
    struct timeval tv{};
    fd_set fds;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds); //STDIN_FILENO is 0
    select(STDIN_FILENO+1, &fds, nullptr, nullptr, &tv);
    return FD_ISSET(STDIN_FILENO, &fds);
}


int main() {

    // while the enter key has not been pressed yet
    // you might have to hold the key in order for it to be registered as pressed
    while(!kbhit()){

        // use "dmesg | grep tty" to get serial info and look for USB ACM device
        // data is held in /dev/ttyASSIGNEDDEVICECODE in my case the name is ttyAMC0
        char in[CSIZE*12];

        // gets the last line of ttyAMC0 and stores it in in
        ///instream.open("/dev/ttyAMC0");
        ///char in = FUNC TO GET THE LAST LINE OF /dev/ttyAMC0
        ///instream.close("/dev/ttyAMC0");

        // making a new char array just for the cords
        char cords[CSIZE];
        getcords(in, CSIZE*12, cords);

        // print cords
        for(char cord : cords){
            cout<<cord;
        }
        cout<<endl;
    }
}
