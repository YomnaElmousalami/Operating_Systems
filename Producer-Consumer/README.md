# CS 471/571, Problem 2: Producer-Consumer Problem

## Author:

**Yomna Elmousalami**

## Project Description:

This project will develop the producer-consumer problem using Pthreads in the C++ programming language.
The program will allow users to test several inputs and display the results to the screen: (how long to sleep before terminating the program, the number of producer threads, and the number of consumer threads). The total turnaround time of the threads will also be calculated. In addition, the program will read various input files with different test cases and display the same result format in output files.

## Prior to compiling and running the code

cd ~/CS471PROJECT/Producer-Consumer

## How to compile the code

g++ -c main.cpp

g++ -o main main.o 

## How to run the code 

number_1 = how long to sleep before terminating the program

number_2 = the number of producer threads

number_3 = the number of consumer threads

./main number_1 number_2 number_3

## Input files that will be read

- sleep_2.txt
- sleep_4.txt
- sleep_6.txt

## Output Files produced

- output_sleep_2.txt
- output_sleep_4.txt
- output_sleep_6.txt

## How the sample output will look like

(Depending on the number of threads and the sleep time)

Sleep Time Num Producers Num Consumers

Finished: Sleep time = num1, Producers = num2, Consumers = num3 Overall Turnaround Time = num4 miliseconds


## Summary and Explanation of Results

As the sleep time increases, the overall turnaround time increases. Additionally, as the number of both producers and consumer threads increase, the overall turnaround time increases. Furthermore, if the number of producer threads dominate the number of consumer threads, and vice versa, the turnaround time will be greater than if the number of producer and consumer threads are equivalent to each other. 