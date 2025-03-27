# CS 471/571, Problem 1: CPU Scheduling

## Author:

**Yomna Elmousalami**

## Project Description:

This project is a CPU scheduling simulator. It will simulate FIFO and Priority with Preemption scheduling. Each run will handle scheduling of 500 (simulated) processes, by reading from "Datafile1-txt.txt." 
The "Datafile1-txt.txt" file contains the following: "Process ID, Arrival time, Priority, CPU burst units," each of which are an integer parameter. After scheduling the 500 simulated process, it will 
calculate the following run time statistics and display the output as follows (Note: the output will be displayed to the screen and in seperate text files for each scheduling algorithm):

**Forumulas used to calculate the output statistics:**

- Total elapsed time: The amount of time from initiation to termination of the application.

- Throughput (Number of processes executed in one unit of CPU burst time) so you can calculate it using the formula: Total burst time( It is the sum of all given burst length) / Total number of processes

- CPU Utilization: The CPU Utilization measures the percentage of the time that the CPU is performing work so you can calculate it using the formula: Total Burst Time/ Total elapsed time

- Average waiting time: total waiting time / Number of processes

- Turnaround time = Burst time + Waiting time or
- Turnaround time = Exit time - Arrival time

- Average turnaround time: Total turnaround time / No of processes

- Response time = Time at which the process gets the CPU for the first time - Arrival time Average response time: Total response time / No of processes

**Output:**

- Statistics for the Run
- Number of processes: 500
- Total elapsed time (for the scheduler):
- Throughput (Number of processes executed in one unit of CPU burst time):
- CPU utilization:
- Average waiting time (in CPU burst times):
- Average turnaround time (in CPU burst times): Average response time (in
CPU burst times):

## Prior to compiling and running the code

cd ~/CS471PROJECT/CPUSCHED

## How to compile the code

g++ -c main.cpp

g++ -o main main.o 

## How to run the code 

./main

**Input text file:**

- Datafile1-txt.txt

## Output Files produced

- FIFO.txt
- Priority.txt

## Explanation of output displayed

Although both have the same elapsed time, throughput, and CPU Utlization, the Priority with preemption
scheduling is more efficient than FIFO since it has a shorter waiting time, turnaround time, and response time. 