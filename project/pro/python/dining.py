import time
import random
import threading
import thread

mutex = threading.Semaphore(1)
sem_emptyPot = threading.Semaphore(0)
sem_fullPot = threading.Semaphore(0)


class getServingsFromPot:
	global retVal
		
		
		
		
		
		
		
		

def main():
	student_ids =[]
	students = []
	student_num = input("How many students?")
	print student_num
	for i in range(student_num):
		print i 
		student_ids.append(0)
	barber = Barber()
	for i in range(0,student_num-1):
		student_ids[i] = i+1
		print student_ids[i]
		students = threading.Thread(target = barber.stu_programming ,args=(student_ids[i],))
		students.start()
	
	for i in range(0,student_num-1):	
		students.join()
		
		
if __name__ == '__main__':
	main()
	



int main() {

    int i, id[NUM_SAVAGES+1];
    pthread_t tid[NUM_SAVAGES+1];

    // Initialize the mutex locks
    pthread_mutex_init(&servings_mutex, NULL);
    pthread_mutex_init(&print_mutex, NULL);

    // Initialize the semaphores
    sem_init(&emptyPot, 0, 0);
    sem_init(&fullPot,  0, 0);

    for (i=0; i<NUM_SAVAGES; i++) 
    {
        id[i] = i;
        printf("----------%d\n",id[i]);
        pthread_create (&tid[i], NULL, savage, (void *)&id[i]);
        }
        
    pthread_create (&tid[i], NULL, cook, (void *)&id[i]);			#pthread_create in python

    for (i=0; i<NUM_SAVAGES; i++)
        pthread_join(tid[i], NULL);
}
	

def main();
	global i
	id=[]
	pthread_t tid=[]
	
	for i in range(0,NUM_SAVAGES-1)
		id.append(i)
	print '---savage present is {}'.format(id)
	
	for i in range(0, NUM_SAVAGES-1);
		tid[i]=threading.Thread(target = )
	for i in range(0,NUM_SAVAGES-1)
	tid.join()	
	
