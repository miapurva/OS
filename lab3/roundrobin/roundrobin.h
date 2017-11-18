#include <iostream>

class roundround{
private:
	//int pid[50];
	int n;
	int arrival_Time[50];
	int burst_Time[50];
	int remaining_Time[50];
	int completion_Time[50];
	int waiting_Time[50];
	int check[50];
	int RQ[50];
public:
	int pid[50];
	void roundr();
	void enqueue(int RQ[],int add);
	void dequeue(int RQ[]);
	void display(int RQ[]);
};