#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <fstream>
#include "refinedsjf.h"


using namespace std;

int main() {

    ifstream fptr;

    system("ls *_.txt | wc -w > YUT.txt");

    fptr.open("YUT.txt");

    int numberofProcesses;

    fptr>>numberofProcesses;
    fptr.close();

    refinedsjf refinedsjf[numberofProcesses];

    for (int i = 0; i < numberofProcesses; ++i) {
        char string[100] = "";
        sprintf(string, "stat -c%%Y %d_.txt > YUT.txt", i+1);
        system(string);
        fptr.open("YUT.txt");
        fptr>>refinedsjf[i].at;
        fptr.close();


        fptr.open("YUT.txt");
        sprintf(string, "wc -w %d_.txt > YUT.txt | cut -f1 -d' ' > YUT.txt", i+1);
        system(string);
        fptr >> refinedsjf[i].bt;
        fptr.close();
    }

    refinedsjf->calculateEverything(refinedsjf, numberofProcesses);

    cout << "PID\tAT\t\tBT\t\tCT\tTAT\tWT"<<endl;

    refinedsjf->display(refinedsjf, numberofProcesses);

}

