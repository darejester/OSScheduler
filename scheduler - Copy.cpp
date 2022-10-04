#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include "queue.h"
#include <iostream>
#include <string>


using namespace std;

//compile with g++
queue list; // initialize queue object

struct process
{
	double arrivalTime;
	double executionTime;
};

class scheduler
{
	process *inputProcesses; //points to a process object
	double *startTime = NULL; 
	double *stopTime = NULL;
	 
	public:
		void FCFS()//member of class: scheduler
		{
			//write code here to print the schedule for given processes
			//x is old job, y is new job. If runTime of x is finished, run y
			//if arrival time of new job is  < arrival time of current job, run new job
			
			
		}
		
		void preemptiveSJF()//member of class: scheduler
		{
			//write code here to print the schedule for given processes
			//x is old job, y is new job. if run time of y < run time of x, do Y else do x
		}
};

void fcfs()
{
	node *temp = list.head;
	int time = 0;
	//cout << "inside fcfs function" << endl; tester
	while(temp != NULL)
	{
		if(temp == list.head)//initializes time for start
		{
			time = temp->aTime;
		}
		
		while(temp->aTime > time)//while next process hasnt arrived yet
		{
			time++;
		}

		cout << "====================" << endl;
		cout << temp->name << endl;
		cout << "START: " << time << endl;
		//temp->rTime++;
		while(temp->rTime < temp->eTime) //run current process
		{
			temp->rTime++;
			time++;
		}
		cout << "STOP: " << time << endl;
		//time = time + temp->eTime;
		temp = temp->next;
	}
	
	cout << "\n TOTAL RUN TIME: " << time << endl;
}

void sjf(int size) //enqueue-ing to tail doesnt organize processes in a sjf manner (create a queue of arrived processes that's sorted in sfj manner?)//what if process finished but next process hasnt arrived yet
{
	node *temp = list.head;
	node *temp2 = list.head;
	node *min = list.head;
	int time = list.head->aTime;
	
	//find tail
	while(temp->next != NULL)
	{
		temp = temp->next;
	}
	list.tail = temp; // set last node as tail	
	temp = list.head;// set temp equal to first node
	
	while(/*list.head != NULL && list.tail !=NULL*/ /*list.head != list.tail*/size > 0)
	{
		temp = list.head;
		temp2 = temp;
		min = temp;
		
		
		
		while(temp2->aTime <= time && temp2->next != NULL) // search for the shortest arrived process
		{
			//cout << "in while" << endl; //tester
			//cout << time << endl;
			//cout << min->eTime << endl;
			//cout << temp2->eTime << endl;
			if (temp2->eTime < min->eTime)
			{
				//cout << "inside min if" << endl;
				min = temp2;
			}
			//cout << temp2->next->eTime << endl;
			temp2 = temp2->next;
			
		}
		if(temp2->aTime <= time && temp2->eTime < min->eTime)//if min is last node
		{
			min = temp2;
		}
		while(temp != min &&temp->next != min)//increment until temp is pointing to the node before min
		{
			temp = temp->next;
		}
		
		//cout << "outside while" << endl;
		
		if(temp->aTime <= time && min->rTime == 0) //if process hasnt been ran before
		{
			//cout << "inside if" << endl;
			min->sTime = time;	
			min->rTime++;//increment process' rTime
			time++;
		}
		else if (temp->aTime <= time && min->rTime != 0)//if process has been ran before
		{
			//cout << "inside else if" << endl;
			min->rTime++;//increment process' rTime
			time++;
		}
		else
		{
			time++;
		}
		
		if(min->rTime == min->eTime) //if process is finished 
		{
			cout << "====================" << endl;
			cout << min->name << endl;
			cout << "START: " << min->sTime << endl;
			cout << "STOP: " << time << endl;
			
			//list.head = temp->next;
			//temp->next = NULL;
			//temp = list.head;
			//temp2 = temp;
			if(min->next == NULL)//end
			{
				list.tail = temp;
				temp->next = NULL;
				//cout << list.head << endl;
				//cout << list.tail << endl;
				//cout << "removed from end" << endl;
				size = size - 1;
				//cout << size << endl;
			}
			else if(min == list.head)//start
			{
				list.head = temp->next;
				temp->next = NULL;
				temp = list.head;
				temp2 = temp;
				
				//cout << list.head << endl;
				//cout << list.tail << endl;
				//cout << "removed from start" << endl;
				size = size - 1;
				//cout << size << endl;
			}
			else//mid
			{
				temp->next = min->next;
				min->next = NULL;
				//cout << list.head << endl;
				//cout << list.tail << endl;
				//cout << "removed from mid" << endl;
				size = size - 1;
				//cout << size << endl;
			}

		}
		/*
		if(temp2->aTime <= time && temp2->next != NULL)//check arrived processes for a shorter job
		{
			if(temp2->next->eTime < temp->eTime) //if new process is shorter than current process
			{
				//temp2 = temp; //set temp2 = to the node that temp is pointing to
				list.tail->next = temp; //sets last node's pointer to temp's node
				list.head = list.head->next; //set head equal to next node
				list.tail = temp;
				temp->next = NULL;
				temp = list.head;
			}
			else if (temp2->eTime >= temp->eTime)
			{
				temp2 = temp->next->next;
				list.tail->next = temp->next;
				temp->next = temp2;
				list.tail->next = NULL;
			}
		}
		*/
			//cout << "here" << endl;
	}
	
	cout << "\n TOTAL RUN TIME: " << time << endl;

}



int main(int argc, char *argv[]) //argc is holds the number of arguments when executing program //argv 
{
	//write code here to create schedule for the input processes
	//input is: processName arrivalTime executionTime, repeat. final argument is which scheduler to do
			//every index 1 is processName
			//every index 2 is arrivalTime
			//every index 3 is executionTime
		node *newNode = NULL;
		node *temp = list.head;
		node *temp2 = list.head;
		//cout << argc << endl;//test 
		string sched(argv[argc-1]); //set scheduler type from input
		int size = 0;
		//cout << sched << endl; //test input sched
		
		
		for (int ctr = 1; ctr < (argc-1); ctr = ctr+3) //loop to go through all the arguments of the input 
		{
			char *name = argv[ctr];
			double aTime = stod((string)argv[ctr+1]);
			double eTime = stod((string)argv[ctr+2]);
			cout << name << " " << aTime << " " << eTime << endl; //checker for which is getting recieved
			//cout << aTime + 100 << endl; //checker if aTime is double var
			
			newNode = list.enqueue(name, aTime, eTime);
			temp = list.head;
			temp2 = list.head;			
			
			
			if (temp != NULL) //if there is at least 1 existing node
			{
				//cout << "in temp" << endl;
				//cout << temp->aTime << " " << newNode->aTime << endl;
				while ((temp->aTime < newNode->aTime) && (temp->next != NULL))
				{
					temp = temp->next;
					while(temp2->next != temp)
					{
						temp2 = temp2->next;
					}
				}
				
				/*
				while ((temp->aTime < newNode->aTime) && (temp->next->aTime < newNode->aTime) && (temp->next != NULL)) //error with adding to the end. temp->next->aTime looks for aTime of NULL when adding to the end
				{
					cout << "in temp while loop" << endl;
					//cout << list.head->next << endl;
					//cout << temp->next << endl;
					cout << temp->aTime << endl;
					cout << temp->next->aTime << endl;
					temp = temp->next;
				}
				*/
				//cout << temp->aTime << endl;
				//cout << temp2->aTime << endl;
			}
			//cout << list.head << endl; //test head address
			//cout << newNode << endl; //test new node address
			
			if (list.head == NULL || (temp->aTime > newNode->aTime && temp == temp2)) //add to start or when empty
			{
				cout << "in start" << endl; // test if going inside condition
				newNode->next = list.head;
				list.head = newNode;
				size++;
			}
			else if ((temp->aTime > newNode->aTime) && (temp2->aTime < newNode->aTime))// add to middle
			{
				cout << "in middle" << endl; // test if going inside condition
				newNode->next = temp;
				temp2->next = newNode;
				size++;
			}
			else if( (temp->next == NULL))//add to last
			{
				cout << "in end" << endl; // test if going inside condition
				temp->next = newNode;
				size++;
			}
		}
		
		// print linked list
		temp = list.head;
		cout << "======TIMELINE======" << endl;
		while (temp != NULL)
		{
			cout << temp->name << " " << temp->aTime << " " << temp->eTime << endl;
			temp = temp->next;
		}
		
		//pick scheduler
		if (sched == "FCFS")
		{
			cout << "\nSCHEDULER: " << sched << endl; //test if going inside condition
			fcfs();
			
		}
		else if (sched == "SJF")
		{
			cout << "\nSCHEDULER: " << sched << endl; //test if going insdie condition
			sjf(size);
		}
		//cout << "in main" << endl;
		
		

	return 0;
}
