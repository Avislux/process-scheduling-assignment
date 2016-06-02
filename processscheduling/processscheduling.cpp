// processscheduling.cpp : Defines the entry point for the console application.
// Assumes scheduling is preemptive

#include "stdafx.h"
#include <iostream>
using namespace std;
void RMS(int period[], int runTime[], int process[]);
void EDF(int period[], int runTime[], int process[]);
int _tmain(int argc, _TCHAR* argv[])
{
	int period[3] = { 30, 40, 50 }; // run every x ms
	int runTime[3] = { 10, 15, 5 };
	int process[3] = {1,2,3};
	cout << "Running RMS\n";
	RMS(period, runTime, process); //rate monotonic scheduling
	cout << "\n\nRunning EDF\n"; 
	EDF(period, runTime, process);
	char a;
	cin >>  a;
	return 0;
}
void EDF(int period[], int runTime[], int process[]){ //earliest first deadline
	int  deadline[3]; int TIME = 120; bool running[3] = { false, false, false }; int counter[3] = { 0, 0, 0 }; int queue[3] = { 0, 0, 0 };
	
	for (int time = 0; time < TIME; time = time + 5) {
		cout << "Time: " << time << " | ";
		for (int i = 0; i < 3; i++) {
			if (time % period[i] == 0) { //run process at fixed intervals
				counter[i] = runTime[i];
				queue[i] = runTime[i];
				deadline[i] = time + period[i];
			}
			if (counter[i] == 0) {
				running[i] = false;
			}
			else { running[i] = true; }
			/*
			if (running[i] == true) {
				cout << " Process" << i + 1 << ": RUNNING " ;
			}
			else { cout << " Process" << i + 1 << ": not " ; }
			*/
			if (counter[i] > 0) counter[i] -= 5; //subtract the run time
		}
		//cout << endl;
		//determine which process to run based on deadlines and whether it needs to be scheduled
		if (queue[0] != 0 && queue[1] != 0 && queue[2] != 0) {
			if (deadline[0] <= deadline[1] && deadline[0] <= deadline[2]) {
				cout << "Running Process A";
				queue[0] -= 5;
			}
			else if (deadline[1] <= deadline[2] && deadline[1] <= deadline[0]) {
				cout << "Running Process B";
				queue[1] -= 5;
			}

			else if (deadline[2] <= deadline[1] && deadline[2] <= deadline[0]) {
				cout << "Running Process C";
				queue[2] -= 5;
			}
		}
		else if (queue[0] != 0 && queue[1] != 0) {
			if (deadline[0] <= deadline[1]) {
				cout << "Running Process A";
				queue[0] -= 5;
			}
			else {
				cout << "Running Process B";
				queue[1] -= 5;
			}
		}
		else if (queue[1] != 0 && queue[2] != 0) {
			if (deadline[1] <= deadline[2] ) {
				cout << "Running Process B";
				queue[1] -= 5;
			}

			else{
				cout << "Running Process C";
				queue[2] -= 5;
			}
		}
		else if (queue[0] != 0 && queue[2] != 0) {
			if (deadline[0] <= deadline[2] ) {
				cout << "Running Process A";
				queue[0] -= 5;
			}
			
			else {
				cout << "Running Process C";
				queue[2] -= 5;
			}
		}
		else if (queue[0] != 0) {
			cout << "Running Process A";
			queue[0] -= 5;
		}
		else if (queue[1] != 0) {
			cout << "Running Process B";
			queue[1] -= 5;
		}
		else if (queue[2] != 0) {
			cout << "Running Process C";
			queue[2] -= 5;
		}
		cout << "\n";
	}
}
void RMS(int period[], int runTime[], int process[]){ //rate monotonic Process priority increases monotonically with the frequency with which it must execute

	int priority[3]; int TIME = 120; bool running[3] = { false, false, false }; int counter[3] = { 0, 0, 0 }; int queue[3] = { 0, 0, 0 };
	for (int i = 0; i < 3; i++){
		priority[i] = 1 / period[i];
	}
	for (int time = 0; time < TIME; time = time + 5){
		cout << "Time: " << time << " | ";
		for (int i = 0; i < 3; i++){
			if (time % period[i] == 0){ //run process at fixed intervals
				counter[i] = runTime[i];
				queue[i] = runTime[i];
			}
			if (counter[i] == 0){
				running[i] = false;
			}
			else { running[i] = true; }
			/*
			if (running[i] == true){
				cout << "Process" << i + 1 << ": RUNNING \t";
			}
			else { cout << "Process" << i + 1 << ": not \t"; }
			*/
			if (counter[i] > 0) counter[i] -= 5; //subtract the run time
		}
		//cout << endl;
		//determine based on priority
		if (priority[0] >= priority[1] && priority[0] >= priority[1] && queue[0] !=0){
			cout << "Running Process A"; 
			queue[0] -= 5;
		}
		else if (priority[1] >= priority[2] && priority[1] >= priority[0] && queue[1] != 0){
			cout << "Running Process B";
			queue[1] -= 5;
		} 
		else if (priority[2] >= priority[1] && priority[2] >= priority[0]&& queue[2] !=0){
			cout << "Running Process C";
			queue[2] -= 5;
		}
		cout << "\n";
		
	}
}
