
//
// Created by gowtham on 1/8/17.
//

#include <iostream>
#include "refinedsjf.h"

using namespace std;

int main(void) 
{

    cout << "Give the number of processes: ";

    int numberOfProcesses;
    cin >> numberOfProcesses;

    refinedsjf refinedsjf[numberOfProcesses];

    for (int i = 0; i < numberOfProcesses; ++i) {
        cout << "give arrival and burst times: ";

        cin >> refinedsjf[i].at >> refinedsjf[i].bt;
    }

    refinedsjf->calculateEverything(refinedsjf, numberOfProcesses);

    cout << "PID\tAT\tBT\tCT\tTAT\tWT\n";

    refinedsjf->display(refinedsjf, numberOfProcesses);
    return(0);

}

