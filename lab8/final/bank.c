#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

#define MAX_ACCOUNTS 10 
#define TXN_LIMIT 5000 	
#define number_of_counters 3 	

double Bank_Asset = 0;
float Balance[MAX_ACCOUNTS] = {0};
int Customer_MAXLIMIT;

sem_t counter[number_of_counters], mutex[MAX_ACCOUNTS];

struct txn
{
	int Customer_No, Account_No, Counter_Ass;
	unsigned long Txn_ID;
	float Txn_Amt;
};

void Debit(struct txn T)
{
	sem_wait(&counter[T.Counter_Ass]);
	printf("\nCustomer %d, Txn_id = %lu, ctr %d, requesting for Withdrawal of Rs. %0.2f on ACC : %d \n", T.Customer_No, T.Txn_ID, T.Counter_Ass, T.Txn_Amt, T.Account_No + 1);
	
	sem_wait(&mutex[T.Account_No]);
	printf("\nCustomer %d, Txn_id = %lu, ctr %d, GOT HOLD of ACC : %d \n", T.Customer_No, T.Txn_ID, T.Counter_Ass, T.Account_No + 1);
	
	if(Balance[T.Account_No] >= T.Txn_Amt)
	{
		Balance[T.Account_No] -= T.Txn_Amt;
		Bank_Asset -= T.Txn_Amt;
		printf("\n\n\t\tCustomer %d, Txn_id = %lu, ctr %d, WITHDREW Rs. %0.2f ----> (Current Balance[%d] = Rs. %0.2f) \tTotal Bank Asset = %lf \n", T.Customer_No, T.Txn_ID, T.Counter_Ass, T.Txn_Amt, T.Account_No + 1, Balance[T.Account_No], Bank_Asset);
	}
	else
		printf("\n\n\t\tCustomer %d, Txn_id = %lu, ctr %d, COULDN'T WITHDRAW because ----> (Current Balance[%d] = Rs. %0.2f) < (Withdrawal Amt = Rs. %0.2f) \n", T.Customer_No, T.Txn_ID, T.Counter_Ass, T.Account_No + 1, Balance[T.Account_No], T.Txn_Amt);
	
	sem_post(&mutex[T.Account_No]);
	sem_post(&counter[T.Counter_Ass]);
	printf("\nCustomer %d, Txn_id = %lu LEFT the ctr %d ...\n", T.Customer_No, T.Txn_ID, T.Counter_Ass);
}

void Credit(struct txn T)
{
	sem_wait(&counter[T.Counter_Ass]);
	printf("\nCustomer %d, Txn_id = %lu, ctr %d, requesting Deposit of Rs. %0.2f on ACC : %d \n", T.Customer_No, T.Txn_ID, T.Counter_Ass, T.Txn_Amt, T.Account_No + 1);
	
	sem_wait(&mutex[T.Account_No]);
	printf("\nCustomer %d, Txn_id = %lu, ctr %d, got hold of ACC : %d \n", T.Customer_No, T.Txn_ID, T.Counter_Ass, T.Account_No + 1);
	
		Balance[T.Account_No] += T.Txn_Amt;
		Bank_Asset += T.Txn_Amt;
		printf("\nCustomer %d, Txn_id = %lu, ctr %d, Deposited Rs. %0.2f ----> (Current Balance[%d] = Rs. %0.2f) \t\nTotal Bank Asset = %lf \n", T.Customer_No, T.Txn_ID, T.Counter_Ass, T.Txn_Amt, T.Account_No + 1, Balance[T.Account_No], Bank_Asset);
	
	sem_post(&mutex[T.Account_No]);
	sem_post(&counter[T.Counter_Ass]);
	printf("\nCustomer %d, Txn_id = %lu LEFT the ctr %d \n", T.Customer_No, T.Txn_ID, T.Counter_Ass);
}

void *Transaction(void *arg)
{
	struct txn T;
	T.Customer_No = *(int *)(arg);
	T.Txn_ID = (unsigned long) pthread_self();
	T.Counter_Ass = rand() % number_of_counters;
	T.Account_No = rand() % MAX_ACCOUNTS;
	T.Txn_Amt = (float)(rand() % (TXN_LIMIT * 100)) / 100;
	switch(rand() % 2)
	{
		case 0:	Debit(T);
				break;
		case 1:	Credit(T);
				break;
	}
	pthread_exit(0);
}

int main()
{
	int i;
	
	for (i = 0; i < number_of_counters; i++)
		sem_init(&counter[i], 0, 1);
	for (i = 0; i < MAX_ACCOUNTS; i++)
		sem_init(&mutex[i], 0, 1);
	srand(time(NULL));
	for(i = 0; i < MAX_ACCOUNTS; i++)
	{
		Balance[i] = (float)(rand() % (TXN_LIMIT * 1000)) / 100;
		Bank_Asset += Balance[i];

	printf("\n");
	printf("\n\t\t\tTotal Asset in the Bank: Rs. %0.2lf \n", Bank_Asset);
	printf("Enter the MAX Limit of Customers : ");
	scanf("%d", &Customer_MAXLIMIT);

	int Customers[Customer_MAXLIMIT];
	pthread_t trans[Customer_MAXLIMIT];
	for (i = 0; i < Customer_MAXLIMIT; i++)
	{
		Customers[i] = i+1;
		printf( "Customer %d CAME to the Bank \n", i+1);
		pthread_create(&trans[i], NULL, Transaction, &Customers[i]);
	}

	for(i = 0; i < Customer_MAXLIMIT; i++)
		pthread_join(trans[i], NULL);

	return 0;
	}
}