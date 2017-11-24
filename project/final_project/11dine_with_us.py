'''
PROJECT: SYNCHRONIZATION PROBELM- DINING SAVAGES
Usage : python 11dine_with_us.py
Programmers: CED15I017,COE15B036,COE15B010
'''


from visual import *

from threading import Thread, Lock
import thread
import threading
import time
import random

side = 4.0
thickness = 0.3
s2=7.7
s3=8.3
#count_servings = 7
NUM_SAVAGES=5
savagexx= [ ]
food = [ ]
#cook
cookxxx= arrow(pos = vector(-3.7,-2,s3*4+6), axis=vector(0,1.8,0), color=color.blue)

sem_emptypot=threading.Semaphore(0)
sem_fullpot=threading.Semaphore(0)
sem_print=threading.Semaphore(1)
sem_servings=threading.Semaphore(1)

class Savages_cook:
	global NUM_SAVAGES
	global servings
	global count_servings

	def __init__(self,servings,NUM_SAVAGES):
		self.servings=servings
		self.NUM_SAVAGES=NUM_SAVAGES
		self.count_servings=14

	def Savage(self, savage_id):
		time.sleep(2)
		while (1):
			sem_servings.acquire()
			if (self.servings==0):
				print "\nSavage {0} signalled the cook".format(savage_id+1)
				#color change
				savagexx[savage_id].color=color.green
				#position change
				while savagexx[savage_id].x > 0:
					rate(5)
					savagexx[savage_id].x=savagexx[savage_id].x - 0.5
				#back to original position
				time.sleep(2)
				savagexx[savage_id].pos=savagexx[savage_id].pos + vector(2,0,0)
				sem_emptypot.release()
				
				time.sleep(4)
				#back to original color
				savagexx[savage_id].color=(0.8,0.1,0.3)
				sem_fullpot.acquire()
				self.servings=15

			#servings getting finished
			
			sem_print.acquire()
			print "Savage {0} is eating".format(savage_id+1)
			while savagexx[savage_id].x > -1:
				rate(3)
				#r.x=r.x+1
				savagexx[savage_id].x=savagexx[savage_id].x - 0.625
			sem_print.release()
			self.servings=self.servings-1
			food[self.count_servings].visible=False
			self.count_servings=self.count_servings-1
			print "Servings--->",self.servings

			sem_servings.release()

			time.sleep(2)

			sem_print.acquire()
			print "\nSavage {0} is DONE eating".format(savage_id+1)
			savagexx[savage_id].pos=savagexx[savage_id].pos + vector(3,0,0)
			sem_print.release()

		return 0

	def Cook(self,cook_id):
		while (1):
			sem_emptypot.acquire()
			cookxxx.x=cookxxx.x + 3.7
			time.sleep(1)
			cookxxx.z=cookxxx.z - 5
			time.sleep(2)
			print "\nCook filled the pot\n"
			for i in range(0,15):
				food[i].visible=True
			self.count_servings=14
			#back to original position
			cookxxx.pos=vector(-3.7,-2,s3*4+6)
			sem_fullpot.release()
		return 0

def main():

	wallRight = box (pos=vector( 2*side, 0, 0), size=vector(thickness, s2, 6*s3),  color = color.white, material=materials.wood)
	wallLeft = box (pos=vector(-2*side, 0, 0), size=vector(thickness, s2, 6*s3),  color = color.white, material=materials.wood)
	wallDown = box (pos=vector(0,-side, 0), size=vector(2*s3, thickness, 8*s3),  color = color.white, material=materials.wood)
	wallTop = box (pos=vector(0,side, 0), size=vector(2*s3, thickness, 6*s3),  color = color.white, material=materials.wood)
	wallBack = box(pos=vector(0, 0, -2*side), size=vector(2*s2, s2, thickness), color = color.white, material=materials.wood )
	table = cone(pos=(0,-1,15), axis=(0,-side,0),radius=1.5,color=color.white, material=materials.wood)

	for i in range(0,15):
		print i
		food.append(0)
	#first layer
	food[0]= sphere(pos=(-0.8,-0.75,15),radius=0.20,color=color.yellow)
	food[1]= sphere(pos=(-0.4,-0.75,15),radius=0.20,color=color.yellow)
	food[2]= sphere(pos=(0,-0.75,15),radius=0.20,color=color.yellow)
	food[3]= sphere(pos=(0.4,-0.75,15),radius=0.20,color=color.yellow)
	food[4]= sphere(pos=(0.8,-0.75,15),radius=0.20,color=color.yellow)
	#second layer
	food[5]= sphere(pos=(-0.65,-0.37,15),radius=0.20,color=color.yellow)
	food[6]= sphere(pos=(-0.2,-0.37,15),radius=0.20,color=color.yellow)
	
	food[7]= sphere(pos=(0.2,-0.37,15),radius=0.20,color=color.yellow)
	food[8]= sphere(pos=(0.65,-0.37,15),radius=0.20,color=color.yellow)
	#third layer
	food[9]= sphere(pos=(-0.425,-0.03,15),radius=0.20,color=color.yellow)
	food[10]= sphere(pos=(0	,-0.03,15),radius=0.20,color=color.yellow)
	food[11]= sphere(pos=(0.425,-0.03,15),radius=0.20,color=color.yellow)
	
	#fourth layer
	food[12]= sphere(pos=(-0.2125,0.35,15),radius=0.20,color=color.yellow)
	food[13]= sphere(pos=(0.2125,0.35,15),radius=0.20,color=color.yellow)
	#fifth layer
	food[14]= sphere(pos=(0,0.75,15),radius=0.20,color=color.yellow)
	
	

	sav_id = [ ]
	#savagexx = [ ]
	SAVAGES_thread = [ ]
	distance=0
	
	for i in range(NUM_SAVAGES+1):
		#savage= arrow(pos = vector(-1*side,0,0), axis=vector(+0.2,+0.2,0), color=color.red)
	
		#print i
		sav_id.append(0)
		savagexx.append(0)
	Sav_Co=Savages_cook(15,4)

	for i in range(0,NUM_SAVAGES):
		#print i
		sav_id[i]=i
		print "Savage ",sav_id[i], " entered"
		
		savagexx[i]= arrow(pos = vector(2,-2,s3*4+6+distance), axis=vector(0,1.8,0), color=(0.8,0.1,0.3))
		
		SAVAGES_thread=threading.Thread(target = Sav_Co.Savage, args = (sav_id[i],))
		SAVAGES_thread.start()
		
		distance=distance-2
	SAVAGES_thread=threading.Thread(target = Sav_Co.Cook,args = (sav_id[i+1],))
	SAVAGES_thread.start()

	for i in range(0,NUM_SAVAGES):	
		SAVAGES_thread.join()

if __name__ == '__main__':
	main()