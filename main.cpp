#include <iostream>
#include <chrono>
#include <thread>
#include <unistd.h>
#include <fstream>
#define CSIZE 26
using namespace std;
using namespace std::chrono_literals;

int getcords(const char* GPGGA, int size, char* cords, int g ){
    // loop
    // g serves as a continuous i
    while(g < size){
        // Checking for GPGGA
        if(GPGGA[g] == '$' && GPGGA[g + 1] == 'G' && GPGGA[g + 2] == 'P' && GPGGA[g + 3] == 'G' && GPGGA[g + 4] == 'G'){
            g+=17; // to jump
            // dump GPGGA into cords
            for(int j = 0; j < CSIZE; j++){
                cords[j]=GPGGA[g];
                g++;
            }
            return g;
        }g++;
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

    // no need to put a return in main because the return is here
    return FD_ISSET(STDIN_FILENO, &fds);
}

int main() {
    // while the enter key has not been pressed yet
    // you might have to hold the key for 1 second order for it to be registered as pressed because of the sleep
    int g = 0;
    while(!kbhit()){
        // use "dmesg | grep tty" to get serial info and look for USB ACM device
        // data is held in /dev/ttyASSIGNEDDEVICECODE in my case the name is ttyACM0

        // putting the data file into a string
        string inFileName = "/mnt/c/Users/Phineas/CLionProjects/Get_Data_From_$GPGGA/datatest.txt";
        ifstream inFile;
        inFile.open(inFileName.c_str());

        int y = 52*8;
        char in[y];
        if (inFile.is_open())
        {
            for (int i = 0; i < y; i++)
            {
                inFile >> in[i];
            }

            inFile.close(); // close input file
        }
        else { // error message
            cerr << "Can't find input file " << inFileName << endl;
        }
        // making a new char array just for the cords
        char cords[CSIZE];
        g = getcords(in, y, cords, g);

        // convert cords to a string to print it because printing the car array was buggy
        string out;
        for(char cord : cords){
            if(cord == ',') {
                out += cord;
                out += " ";
            }else{
                out +=cord;
            }
        }
        cout<<out<<endl;

        // GPS only gets new cords every 1 second, so we will delay for 1 second minus runtime
        // eventually it will go out of sync as the time spent executing code adds up
        // setting up a timer and sleeping for that time didn't work, the function only takes pure ints
        std::this_thread::sleep_for(1s);
    }
}
