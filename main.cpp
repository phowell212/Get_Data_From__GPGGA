#include <iostream>
#include <fstream>
#include <string>
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

int main() {
    while(true){
        std::ifstream instream;

        // use "dmesg | grep tty" to get serial info and look for USB ACM device
        // data is held in /dev/ttyASSIGNEDDEVICECODE in my case the name is ttyAMC0
        char in[CSIZE*12];
        instream.open("/dev/ttyACM0");

        // gets the last line of /dev/AMC0
        while(!instream.eof())
        {
            instream.getline(in,256);
        }

        // making a new char array just for the cords
        char cords[CSIZE];
        getcords(in, CSIZE*12, cords);

        // print cords
        for(int i = 0; i < CSIZE; i++){
            cout<<cords[i];
        }

        bool out = true;
        if(out) break;
    }
}
