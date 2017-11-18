from threading import Thread, Lock
import thread
import threading
import time
import random

sem_emptypot=threading.Semaphore(0)
sem_fullpot=threading.Semaphore(0)
sem_print=threading.Semaphore(1)
sem_servings=threading.Semaphore(1)

class Savages_cook:
	global NUM_SAVAGES
	global servings

	def __init__(self,servings,NUM_SAVAGES):
		self.servings=servings
		self.NUM_SAVAGES=NUM_SAVAGES

	def Savage(self, savage_id):
		while (1):
			sem_servings.acquire()
			if (self.servings==0):
				sem_emptypot.release()
				print "\nSavage {0} signalled the cook".format(savage_id+1)
				sem_fullpot.acquire()
				self.servings=7
			self.servings=self.servings-1
			
			sem_print.acquire()
			print "Savage {0} is eating".format(savage_id+1)
			sem_print.release()
			print "Servings--->",self.servings

			sem_servings.release()

			time.sleep(2)

			sem_print.acquire()
			print "\nSavage {0} is DONE eating".format(savage_id+1)
			sem_print.release()
		#thread.exit()

		return 0

	def Cook(self,cook_id):
		while (1):
			sem_emptypot.acquire()
			print "\nCook filled the pot\n"
			sem_fullpot.release()
		return 0

def main():
	sav_id = [ ]
	SAVAGES_thread = [ ]
	NUM_SAVAGES=4
	for i in range(NUM_SAVAGES+1):
		#print i
		sav_id.append(0)
	Sav_Co=Savages_cook(7,4)
	for i in range(0,NUM_SAVAGES):
		#print i
		sav_id[i]=i
		SAVAGES_thread=threading.Thread(target = Sav_Co.Savage, args = (sav_id[i],))
		SAVAGES_thread.start()
	SAVAGES_thread=threading.Thread(target = Sav_Co.Cook,args = (sav_id[i+1],))
	SAVAGES_thread.start()

	for i in range(0,NUM_SAVAGES):	
		SAVAGES_thread.join()

if __name__ == '__main__':
	main()


			

		

from threading import Thread, Lock
import thread
import threading
import time
import random

sem_emptypot=threading.Semaphore(0)
sem_fullpot=threading.Semaphore(0)
sem_print=threading.Semaphore(1)
sem_servings=threading.Semaphore(1)

class Savages_cook:
	global NUM_SAVAGES
	global servings

	def __init__(self,servings,NUM_SAVAGES):
		self.servings=servings
		self.NUM_SAVAGES=NUM_SAVAGES

	def Savage(self, savage_id):
		while (1):
			sem_servings.acquire()
			if (self.servings==0):
				sem_emptypot.release()
				print "\nSavage {0} signalled the cook".format(savage_id+1)
				sem_fullpot.acquire()
				self.servings=7
			self.servings=self.servings-1
			
			sem_print.acquire()
			print "Savage {0} is eating".format(savage_id+1)
			sem_print.release()
			print "Servings--->",self.servings

			sem_servings.release()

			time.sleep(2)

			sem_print.acquire()
			print "\nSavage {0} is DONE eating".format(savage_id+1)
			sem_print.release()
		#thread.exit()

		return 0

	def Cook(self,cook_id):
		while (1):
			sem_emptypot.acquire()
			print "\nCook filled the pot\n"
			sem_fullpot.release()
		return 0

def main():
	sav_id = [ ]
	SAVAGES_thread = [ ]
	NUM_SAVAGES=4
	for i in range(NUM_SAVAGES+1):
		#print i
		sav_id.append(0)
	Sav_Co=Savages_cook(7,4)
	for i in range(0,NUM_SAVAGES):
		#print i
		sav_id[i]=i
		SAVAGES_thread=threading.Thread(target = Sav_Co.Savage, args = (sav_id[i],))
		SAVAGES_thread.start()
	SAVAGES_thread=threading.Thread(target = Sav_Co.Cook,args = (sav_id[i+1],))
	SAVAGES_thread.start()

	for i in range(0,NUM_SAVAGES):	
		SAVAGES_thread.join()

if __name__ == '__main__':
	main()
