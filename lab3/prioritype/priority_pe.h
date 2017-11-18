#include <iostream>

//#include "priority_pe.h"
using namespace std;

class priority_pe
{

private:
//int n;
int pid[10];
int turn_Around_Time;
int waiting_Time[10];
int arrival_Time[10];
int burst_Time[10];
int remain_Time[10];
int process_finish[10];
int priorityarray[10];
public:
void priority();

};