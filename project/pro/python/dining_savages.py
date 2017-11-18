#while creating object initialize the servings and NUM_SAVAGES

import thread
import threading
import time
import random

sem_emptypot = threading.Semaphore()
sem_fullpot = threading.Semaphore()

class Savages_cook:
	global NUM_SAVAGES
	global servings
	global meals

	def __init__(self,servings,NUM_SAVAGES):
		self.servings=servings
		self.NUM_SAVAGES=NUM_SAVAGES
		self.meals=0
		self.servings_thread=threading.Lock()
		self.print_thread=threading.Lock()


	def cook(self, cook_id):
		self.meals = 2
		while (self.meals != 0):
			sem_emptypot.acquire()

			self.putServingsInPot(15)
			self.meals=self.meals-1

			self.print_thread.acquire()
			print "Cook filled pot"
			self.print_thread.release()

			for i in range(0,self.NUM_SAVAGES):
				sem_fullpot.release()
		return 0

	def savage(self, savage_id):
		self.meals=11
		while ( self.meals != 0 ):

			self.servings_thread.acquire()

			myServing = self.getServingsFromPot()

			if (self.servings == 0):
				sem_fullpot.acquire()
				myServing = self.getServingsFromPot()

			self.servings_thread.release()

			self.meals=self.meals-1

			self.print_thread.acquire()
			print "Savage ", savage_id, "is eating "
			self.print_thread.release()

			time.sleep(2)

			self.print_thread.acquire()
			print "Savage ", savage_id, "is DONE eating"
			self.print_thread.release()

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
		sav_id[i]=i+1;
		#print sav_id[i]
		SAVAGES=threading.Thread(target = Sav_Co.savage, args = (sav_id[i],))
		SAVAGES.start()

	SAVAGES=threading.Thread(target = Sav_Co.cook, args = (sav_id[i],))
	SAVAGES.start()

	for i in range(0,NUM_SAVAGES):	
		SAVAGES.join()



if __name__ == '__main__':
	main()
