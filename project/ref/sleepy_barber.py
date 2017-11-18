from visual import *
import time
import random
import threading
import thread

mutex = threading.Semaphore(1)
sem_stu = threading.Semaphore(0)
sem_ta = threading.Semaphore(1)

#visual objects
side = 4.0
thk = 0.1
s2 = 2*side - thk
s3 = 5*side + thk

barber = arrow(pos=vector(-3.7,-2.5,0),axis=vector(0,3,0),color=color.black)
cust = []

class Barber:
	global count
	global state
	global next_seat
	global chair
	global next_teach

	def __init__(self):
		self.count = 0
		self.state=1
		self.next_seat = 0
		self.next_teach=0
		self.chair = [0,0,0]
		
	def check(self,id1):
		if self.chair[0] == id1 :
			return 1
		elif self.chair[1] == id1 :
			return 1
		elif self.chair[2] == id1 :
			return 1
		else:
			return 0	
						
	def stu_programming(self,id1):
		print 'customer {0} is entering'.format(id1)
		#time.sleep(10)	
		while True:
			time.sleep(10)
			mutex.acquire()
			#time.sleep(10)			
			if self.count < 3 and self.check(id1) == 0:
				self.chair[self.next_seat] = id1
				self.count = self.count + 1
				print 'count {0}'.format(self.count)
				print 'next_seat {0}'.format(self.next_seat)
				#i=10
				if self.next_seat == 0:
					
					r = (1.25,-side,0)

					while cust[id1-1].x > 1.25:
						rate(10)
						#cust[id1-1].pos=r
						cust[id1-1].x=cust[id1-1].x - 1.91

					cust[id1-1].y=-2.5	
					cust[id1-1].z=0										
				elif self.next_seat == 1:
					r = (4.25,-side,0)
					while cust[id1-1].x > 4.25:
						rate(10)
						#cust[id1-1].pos=r
						cust[id1-1].x=cust[id1-1].x - 2.15	
					cust[id1-1].y=-2.5
					cust[id1-1].z=0	
				elif self.next_seat == 2:
					r = (7.15,-side,0)
					while cust[id1-1].x > 7.15:
						rate(10)
						cust[id1-1].x=cust[id1-1].x - 0.71
					cust[id1-1].y=-2.5
					cust[id1-1].z=0
				print 'Customer {0} is waiting'.format(id1)
				print 'Waiting Customers : ({0}, {1}, {2})'.format(self.chair[0],self.chair[1],self.chair[2])
				self.next_seat = (self.next_seat +1) % 3
				if self.count == 1 and self.state == 1:
					print 'Wake up Barber'
					barber.pos = (-3,-side,0)				
					self.state = 0
				mutex.release()
				sem_stu.release()
				sem_ta.acquire()
				ta = threading.Thread(target = self.ta_teaching,args=())
				ta.start()
			elif self.count == 3:
				print '-----------------> self.count :{0}\n'.format(self.count)
				print 'No more chairs. Customer {0} left'.format(id1)
				while cust[id1-1].x > -9.3:
					rate(10)
					cust[id1-1].x=cust[id1-1].x - 5
				cust[id1-1].y=-side
				cust[id1-1].z=0
				mutex.release()
				time.sleep(3)
				cust[id1-1].pos=(10.7,-side,0)				 	 	 	   	
                      
	def ta_teaching(self):
   		sem_stu.acquire()
   		mutex.acquire()
   		self.count = self.count - 1
   		print 'count {0}'.format(self.count)
   		print ' Barber is cutting hair for Customer {0}'.format(self.chair[self.next_teach])
   		id1=self.chair[self.next_teach]
		while cust[id1-1].x > -3.7:
			rate(25)
			cust[id1-1].x=cust[id1-1].x - 0.1
		self.chair[self.next_teach]=0
   		print 'Waiting Customers :({0}, {1}, {2})'.format(self.chair[0],self.chair[1],self.chair[2])
   		self.next_teach = (self.next_teach + 1) % 3
   		print 'Barber finished cutting hair'
		while cust[id1-1].x > -9:
			rate(10)
			cust[id1-1].x=cust[id1-1].x - 1.06		
   		if self.count == 0:
   			print 'Barber is gonna sleep'
			'''while barber.x > -3.7:
				rate(10)
				barber.x=cust[id1-1].x + 2'''
			barber.pos=(-3.7,-2.5,0)
			#barber.y=-2.5
			time.sleep(3)
			#barber.pos=(10.7,0,0)   			
   			self.state=1
   		mutex.release()
   		sem_ta.release()
   		time.sleep(3)
		cust[id1-1].pos=(10.7,-side,0)   		
	
	def rand_sleep():
		time.sleep(5)
	
def main():
	#room and walls definition
	wallR = box (pos=( 2.5*side+0.7, 0, 0), size=(thk, s2, s3),  color = color.red)
	wallL = box (pos=(-2.5*side+0.7, 0, 0), size=(thk, s2, s3),  color = color.red)
	wallB = box (pos=(0.7, -side, 0), size=(s3, thk, s3),  color = color.red)
	floor = box (pos=(0, 0, 0),size=(thk, s2, s3),length =0.1, height=10, width=0.1, color=color.green)
	wallT = box (pos=(0.7,  side, 0), size=(s3, thk, s3),  color = color.red)
	wallBK = box(pos=(0.7, 0, -1.5*side), size=(s3, s2, thk), color = (0.7,0.7,0.7))	

	#chairs
	#barber chair
	floor0 = box(pos=(-4.3,-2.5,0),length =1.9, height=0.2, width=1.1, color=color.green)
	floor7 = box(pos=(-3.4,-1,0),length =0.1, height=2.8, width=1.1, color=color.green)

	#customer chairs
	floor1 = box(pos=(1.7,-2.5,0),length =1.9, height=0.2, width=1.1, color=color.green)
	floor2 = box(pos=(0.8,-1,0),length =0.1, height=2.8, width=1.1, color=color.green)

	floor3 = box(pos=(4.7,-2.5,0),length =1.9, height=0.2, width=1.1, color=color.green)
	floor4 = box(pos=(3.8,-1,0),length =0.1, height=2.8, width=1.1, color=color.green)

	floor5 = box(pos=(7.7,-2.5,0),length =1.9, height=0.2, width=1.1, color=color.green)
	floor6 = box(pos=(6.7,-1,0.5),length =0.1, height=2.8, width=1.1, color=color.green)
	
	Customer_ids =[]
	Customers = []
	Customer_num = 5
	#Customer_num = input("How many Customers?")
	#print Customer_num
	for i in range(Customer_num):
		#print i 
		Customer_ids.append(0)
		cust.append(0)
	barber = Barber()
	for i in range(0,Customer_num):
		Customer_ids[i] = i+1
		if i%5== 0:		
			cust[i]=arrow(pos=vector(10.7,-side,i),axis=vector(0,2,0),color=color.yellow)
		elif i%5== 1:
			cust[i]=arrow(pos=vector(10.7,-side,i),axis=vector(0,2,0),color=(0.4,0.2,0.7))			
		elif i%5 == 2:
			cust[i]=arrow(pos=vector(10.7,-side,i),axis=vector(0,2,0),color=(0.3,0.5,0.5))	
		elif i%5 == 3:
			cust[i]=arrow(pos=vector(10.7,-side,i),axis=vector(0,2,0),color=(0.5,0.6,0.1))	
		elif i%5 == 4:
			cust[i]=arrow(pos=vector(10.7,-side,i),axis=vector(0,2,0),color=(0.2,0.1,0.9))									
		Customers = threading.Thread(target = barber.stu_programming ,args=(Customer_ids[i],))
		Customers.start()
	
	for i in range(0,Customer_num):	
		Customers.join()
		
		
if __name__ == '__main__':
	main()