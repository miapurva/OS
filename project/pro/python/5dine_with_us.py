from visual import *

from threading import Thread, Lock
import thread
import threading
import time
import random

side = 4.0
thk = 0.3
'''
s2 = 2*side - thk
s3 = 2*side + thk
'''
s2=7.7
s3=8.3
NUM_SAVAGES=5
savagexx= [ ]

#cook
cookxxx= arrow(pos = vector(-3.7,-2,s3*4+6), axis=vector(0,1.8,0), color=color.blue)

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
		time.sleep(2)
		while (1):
			sem_servings.acquire()
			if (self.servings==0):
				sem_emptypot.release()
				print "\nSavage {0} signalled the cook".format(savage_id+1)
				time.sleep(2)
				sem_fullpot.acquire()
				self.servings=7

			self.servings=self.servings-1
			
			sem_print.acquire()
			while savagexx[savage_id].x > -1:
				rate(3)
				#r.x=r.x+1
				savagexx[savage_id].x=savagexx[savage_id].x - 0.625
			print "Savage {0} is eating".format(savage_id+1)
			sem_print.release()
			print "Servings--->",self.servings

			sem_servings.release()

			time.sleep(2)

			sem_print.acquire()
			savagexx[savage_id].pos=savagexx[savage_id].pos + vector(3,0,0)
			print "\nSavage {0} is DONE eating".format(savage_id+1)
			sem_print.release()
		#thread.exit()

		return 0

	def Cook(self,cook_id):
		while (1):
			sem_emptypot.acquire()
			cookxxx.x=cookxxx.x + 3.7
			cookxxx.z=cookxxx.z - 5
			time.sleep(2)
			print "\nCook filled the pot\n"
			cookxxx.pos=vector(-3.7,-2,s3*4+6)
			sem_fullpot.release()
		return 0

def main():

	wallRight = box (pos=vector( 2*side, 0, 0), size=vector(thk, s2, 4*s3),  color = color.gray(1.0))
	wallLeft = box (pos=vector(-2*side, 0, 0), size=vector(thk, s2, 4*s3),  color = color.gray(1.0))
	wallDown = box (pos=vector(0,-side, 0), size=vector(2*s3, thk, 8*s3),  color = color.orange, material=materials.wood)
	wallTop = box (pos=vector(0,side, 0), size=vector(2*s3, thk, 4*s3),  color = color.gray(0.7))
	wallBack = box(pos=vector(0, 0, -2*side), size=vector(2*s2, s2, thk), color = color.gray(1.0))
	table = cone(pos=(0,-1,15), axis=(0,-side,0),radius=1.5,color=color.orange)
	
	#final destination of the savages is 4*s3
	#savage1= arrow(pos = vector(-1,-2,4*s3-2), axis=vector(0,1.8,0), color=color.red)
	
	#source point of the savages
	#savage2= arrow(pos = vector(2,-2,s3*4+6), axis=vector(0,1.8,0), color=color.green)
	#savage2= arrow(pos = vector(2,-2,s3*4+6-i), axis=vector(0,1.8,0), color=color.green)
	'''
	r=vector(-1,-2,4*s3-2)
	while r.x < 5:
		rate(5)
		savagexx[i].pos=r
		r.x=r.x+1
	'''

	#first layer
	food1= sphere(pos=(-0.8,-0.75,15),radius=0.20,color=color.yellow)
	food2= sphere(pos=(-0.4,-0.75,15),radius=0.20,color=color.yellow)
	food3= sphere(pos=(0,-0.75,15),radius=0.20,color=color.yellow)
	food4= sphere(pos=(0.4,-0.75,15),radius=0.20,color=color.yellow)
	food5= sphere(pos=(0.8,-0.75,15),radius=0.20,color=color.yellow)
	#second layer
	food6= sphere(pos=(-0.65,-0.37,15),radius=0.20,color=color.yellow)
	food7= sphere(pos=(-0.2,-0.37,15),radius=0.20,color=color.yellow)
	food8= sphere(pos=(0.2,-0.37,15),radius=0.20,color=color.yellow)
	food9= sphere(pos=(0.65,-0.37,15),radius=0.20,color=color.yellow)
	#third layer
	food9= sphere(pos=(-0.425,-0.03,15),radius=0.20,color=color.yellow)
	food10= sphere(pos=(0	,-0.03,15),radius=0.20,color=color.yellow)
	food11= sphere(pos=(0.425,-0.03,15),radius=0.20,color=color.yellow)
	
	#fourth layer
	food12= sphere(pos=(-0.2125,0.35,15),radius=0.20,color=color.yellow)
	food13= sphere(pos=(0.2125,0.35,15),radius=0.20,color=color.yellow)
	#fifth layer
	food14= sphere(pos=(0,0.75,15),radius=0.20,color=color.yellow)
	
	

	sav_id = [ ]
	#savagexx = [ ]
	SAVAGES_thread = [ ]
	distance=0
	
	for i in range(NUM_SAVAGES+1):
		savage= arrow(pos = vector(-1*side,0,0), axis=vector(+0.2,+0.2,0), color=color.red)
	
		#print i
		sav_id.append(0)
		savagexx.append(0)
	Sav_Co=Savages_cook(7,4)

	for i in range(0,NUM_SAVAGES):
		#print i
		sav_id[i]=i
		print "Savage ",sav_id[i], " entered"
		
		savagexx[i]= arrow(pos = vector(2,-2,s3*4+6+distance), axis=vector(0,1.8,0), color=color.green)
		
		SAVAGES_thread=threading.Thread(target = Sav_Co.Savage, args = (sav_id[i],))
		SAVAGES_thread.start()
		
		distance=distance-2
	SAVAGES_thread=threading.Thread(target = Sav_Co.Cook,args = (sav_id[i+1],))
	SAVAGES_thread.start()

	for i in range(0,NUM_SAVAGES):	
		SAVAGES_thread.join()

if __name__ == '__main__':
	main()


			

		

