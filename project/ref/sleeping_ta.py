import time
import random
import threading
import thread

mutex = threading.Semaphore(1) 
sem_stu = threading.Semaphore(0)
sem_ta = threading.Semaphore(1)

class Barber:
	global count
	global state
	global next_seat
	global chair
	global next_teach

	def __init__(self):
		self.count = 0
		self.state=0
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
		print '[stu] student {0} is programming'.format(id1)
		while True:
			time.sleep(3)
			mutex.acquire()
			if self.count < 3 and self.check(id1) == 0:
				self.chair[self.next_seat] = id1
				self.count = self.count + 1
				print 'count {0}'.format(self.count)
				print '[stu] student {0} is waiting'.format(id1)
				print 'waiting students : [1] {0} [2] {1} [3] {2}'.format(self.chair[0],self.chair[1],self.chair[2])
				self.next_seat = (self.next_seat +1) % 3
				if self.count == 1 and self.state == 1:
					print 'Wake up TA'
					self.state = 0
				mutex.release()
				sem_stu.release()
				sem_ta.acquire()
				ta = threading.Thread(target = self.ta_teaching,args=())
				ta.start()
			elif self.count == 3:
				print '-----------------> self.count :{0}\n'.format(self.count)
				print '[stu] no more chairs. student {0} is programming'.format(id1)
				mutex.release()	 	 	 	   	
                      
	def ta_teaching(self):
   		sem_stu.acquire()
   		mutex.acquire()
   		self.count = self.count - 1
   		print 'count {0}'.format(self.count)
   		print ' [ta] TA is teaching student {0}'.format(self.chair[self.next_teach])
   		self.chair[self.next_teach]=0
   		print 'waiting students :[1] {} [2] {} [3] {}'.format(self.chair[0],self.chair[1],self.chair[2])
   		self.next_teach = (self.next_teach + 1) % 3
   		#time.sleep(1)
   		print '		[ta] teaching finish'
   		if self.count == 0:
   			print 'sleep dude'
   			self.state=1
   		mutex.release()
   		sem_ta.release()
	
	def rand_sleep():
		time.sleep(5)
	
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
