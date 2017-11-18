#while creating object initialize the servings and NUM_SAVAGES
from threading import Thread, Lock
import thread
import threading
import time
import random

sem_emptypot = threading.Semaphore(0)
sem_fullpot = threading.Semaphore(1)
sem_servings=threading.Semaphore(1) 
sem_print=threading.Semaphore(1)

class Savages_cook:
	global NUM_SAVAGES
	global servings
	global meals

	def __init__(self,servings,NUM_SAVAGES):
		self.servings=servings
		self.NUM_SAVAGES=NUM_SAVAGES
		self.meals=0
		#sem_servings=threading.Lock()
		#sem_print=threading.Lock()


	def cook(self, cook_id):
		self.meals = 2
		while (self.meals):
			sem_emptypot.acquire()

			self.putServingsInPot(15)
			self.meals=self.meals-1

			sem_print.acquire()
			print "Cook filled pot"
			sem_print.release()

			for i in range(0,self.NUM_SAVAGES):
				sem_fullpot.release()
		return 0

	def savage(self, savage_id):
		self.meals=11
		while ( self.meals ):

			sem_servings.acquire()

			myServing = self.getServingsFromPot()

			if (self.servings == 0):
				sem_fullpot.acquire()
				myServing = self.getServingsFromPot()

			sem_servings.release()

			self.meals=self.meals-1

			sem_print.acquire()
			print "Savage ", savage_id, "is eating "
			sem_print.release()

			time.sleep(2)

			sem_print.acquire()
			print "Savage ", savage_id, "is DONE eating"
			sem_print.release()

		return 0

	def getServingsFromPot(self):
		if (self.servings <= 0) :
			sem_emptypot.release()
			retVal=0
		else :
			self.servings=self.servings-1
			retVal=1
		return retVal

	def putServingsInPot(self,num):
		self.servings = self.servings - num;
		sem_fullpot.release()



def main():
	sav_id = [ ]
	SAVAGES = [ ]
	NUM_SAVAGES=3
	for i in range(NUM_SAVAGES+1):
		#print i
		sav_id.append(0)
	Sav_Co=Savages_cook(15,3)
	for i in range(0,NUM_SAVAGES):
		sav_id[i]=i;
		#print sav_id[i]
		SAVAGES=threading.Thread(target = Sav_Co.savage, args = (sav_id[i],))
		SAVAGES.start()
	#print "i---> ",i  =2
	SAVAGES=threading.Thread(target = Sav_Co.cook, args = (sav_id[i+1],))
	SAVAGES.start()

	for i in range(0,NUM_SAVAGES):	
		SAVAGES.join()



if __name__ == '__main__':
	main()
