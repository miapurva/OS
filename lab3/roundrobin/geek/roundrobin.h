class roundrob
{
private:
	//int n;
	int pid[50];
	int arrival_Time[50];
	int burst_Time[50];
	int remaining_Time[50];
	int completion_Time[50];
	int turn_Around_Time[50];
	int waiting_Time[50];
	//int check[50];
	//int RQ[50];
public:
	void robinround();
	//void display();
	//void turn_Around();
};