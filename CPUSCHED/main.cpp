#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <math.h>
#include <vector>
#include <algorithm>
using namespace std;

void FIFO()
{
    ///The following code below is implemented using FIFO Scheduling

    ///declare variables
    double total_elapsed_time = 10;
    double throughput = 0;
    double cpu_utilization = 0;
    double average_waiting_time = 0;
    double average_turnaround_time = 0;
    double average_response_time = 0;
    double total_burst_time = 0;
    double current_waiting_time = 0;
    double total_waiting_time = 0;
    double total_turnaround_time = 0;
    double total_response_time = 0;

    vector<double> arrival_time(500);
    vector<double> cpu_burst_length(500);
    vector<double> priority(500);

    ///read the input text for all 500 processes and calculate the total burst time
    fstream input;
    input.open("Datafile1-txt.txt");
    string firstLine;
    getline(input,firstLine);

    for(int i = 0; i < 500; i++)
    {
        input >> arrival_time[i];
        input >> cpu_burst_length[i];
        input >> priority[i];
        total_burst_time += cpu_burst_length[i];
    }

    ///execute 500 times for each process
    int i = 0;
    while(i < 500)
    {
        ///if the arrival time of the process is less than or equal to the total elapsed time, calculate
        ///the run time statistics, and increment to the next process

        if(arrival_time[i] <= total_elapsed_time)
        {
            total_response_time += total_elapsed_time - arrival_time[i];
            total_elapsed_time = total_elapsed_time + cpu_burst_length[i];
            current_waiting_time = total_elapsed_time - arrival_time[i] - cpu_burst_length[i];
            total_waiting_time += current_waiting_time;
            total_turnaround_time += current_waiting_time + cpu_burst_length[i];
            i++;
        }
        ///otherwise, make the total elapsed time equal to the current arrival time
        else
        {
           total_elapsed_time = arrival_time[i];
           i = i;
        }
    }

    ///calculate run time statistics
    average_waiting_time = total_waiting_time/500;
    throughput = total_burst_time/500;
    cpu_utilization = total_burst_time/total_elapsed_time;
    average_turnaround_time = total_turnaround_time/500;
    average_response_time = total_response_time/500;
    input.close();

    ///Print the results to the screen
    cout << "Statistics for Run" << endl << endl;
    cout << "Number of Processes: 500" << endl << endl;
    cout << "Total elapsed time (for the scheduler): " << total_elapsed_time << endl << endl;
    cout << "Throughput (Number of processes executed in one unit of CPU burst time): " << throughput << endl;
    cout << endl;
    cout << "CPU Utilization: " << cpu_utilization << endl << endl;
    cout << "Average waiting time (in CPU burst times): " <<  average_waiting_time << endl << endl;
    cout << "Average turnaround time (in CPU burst times): " << average_turnaround_time << endl;
    cout << endl;
    cout << "Average response time (in CPU burst times): " << average_response_time << endl;

    ///Print the results to a file called FIFO.txt
    ofstream output;
    output.open("FIFO.txt");
    output << "Statistics for Run" << endl << endl;
    output << "Number of Processes: 500" << endl << endl;
    output << "Total elapsed time (for the scheduler): " << total_elapsed_time << endl << endl;
    output << "Throughput (Number of processes executed in one unit of CPU burst time): " << throughput << endl;
    output << endl;
    output << "CPU Utilization: " << cpu_utilization << endl << endl;
    output << "Average waiting time (in CPU burst times): " << average_waiting_time << endl << endl;
    output << "Average turnaround time (in CPU burst times): " << average_turnaround_time << endl;
    output << endl;
    output << "Average response time (in CPU burst times): " << average_response_time << endl;
    output.close();
}

void priority()
{
    ///The following code uses priority with preemptive scheduling

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

///creating a struct for the processes
struct process {
    double arrival_time;
    double cpu_burst_length;
    double priority;
    double elapse_tracker;
    bool isStartset = false;
    double start;
    double ending;

    ///constructor to initialize the data members
    process(double arrival, double burst_length, double p)
    {
        arrival_time = arrival;
        cpu_burst_length = burst_length;
        priority = p;
        elapse_tracker = 0;
        start = 0;
        ending = 0;
    }
};

///comparator to to compare which process is the highest priority (lower number)
auto higher_priority = [] (process a, process b)
{
    return a.priority < b.priority;
};

///declare variables
double curr_T = 0;
double arrival_time, cpu_burst_length, priority;
double total_burst_time = 0;
double total_elapsed_time = 0;
double cpu_utilization = 0;
double throughput = 0;
double current_waiting_time = 0;
double total_waiting_time = 0;
double average_waiting_time = 0;
double average_turnaround_time = 0;
double total_turnaround_time = 0;
double total_response_time = 0;
double average_response_time = 0;

vector<process> all_processes; ///this vector keeps track of all of the processes being read from the file
vector<process> tracker; ///this vector keeps track of the processes that are currently going to be executed

///read the input file and calculate the total burst time
    fstream input;
    input.open("Datafile1-txt.txt");

    string firstLine;
    getline(input, firstLine);

    for (int i = 0; i < 500; i++)
    {
        input >> arrival_time >> cpu_burst_length >> priority;
        all_processes.emplace_back(arrival_time, cpu_burst_length, priority);
        total_burst_time += cpu_burst_length;
    }

    input.close();

    while (!all_processes.empty() || !tracker.empty())
    {
        ///when processes start arriving, keep them in the ready queue
        if (!all_processes.empty() && all_processes.front().arrival_time <= curr_T)
        {
            tracker.push_back(all_processes.front());
            all_processes.erase(all_processes.begin());
        }

        ///this code segment helps with priority preemption
        ///if there are processes ready to be executed, sort them based on priority and calculate calculate runtime statistics
        if (!tracker.empty())
        {
            sort(tracker.begin(), tracker.end(), higher_priority);
            if (tracker.front().elapse_tracker < tracker.front().cpu_burst_length)
            {
                if (!tracker.front().isStartset)
                {
                    tracker.front().start = curr_T;
                    tracker.front().isStartset = true;
                }
                tracker.front().ending = curr_T;
                tracker.front().elapse_tracker++;
                curr_T++;
            }
            else if (tracker.front().elapse_tracker == tracker.front().cpu_burst_length)
            {
                tracker.front().ending = curr_T;
                current_waiting_time = tracker.front().ending - tracker.front().arrival_time - tracker.front().cpu_burst_length;
                total_waiting_time += current_waiting_time;
                total_turnaround_time += tracker.front().cpu_burst_length + current_waiting_time;
                total_response_time += tracker.front().start - tracker.front().arrival_time;
                curr_T = curr_T;
                tracker.front().elapse_tracker ++;
            }
            else if(tracker.front().elapse_tracker > tracker.front().cpu_burst_length)
            {
                curr_T = curr_T;
                tracker.erase(tracker.begin());
            }
        }

        ///otherwise, increment the current elapsed time
        else
        {
            curr_T++;
        }

    }

    ///calculate run time statistics
    total_elapsed_time = curr_T;
    cpu_utilization = total_burst_time/total_elapsed_time;
    throughput  = total_burst_time/500;
    average_waiting_time = total_waiting_time/500;
    average_turnaround_time = total_turnaround_time/500;
    average_response_time = total_response_time/500;

    /// Print the results to the screen
    cout << "Statistics for Run" << endl << endl;
    cout << "Number of Processes: 500" << endl << endl;
    cout << "Total elapsed time (for the scheduler): " << total_elapsed_time << endl << endl;
    cout << "Throughput (Processes per unit time): " << throughput << endl;
    cout << endl;
    cout << "CPU Utilization: " << cpu_utilization << endl << endl;
    cout << "Average waiting time (in CPU burst times): " << average_waiting_time << endl << endl;
    cout << "Average turnaround time (in CPU burst times): " << average_turnaround_time << endl;
    cout << endl;
    cout << "Average response time (in CPU burst times): " << average_response_time << endl;

    ///print the results to the output file
    ofstream output;
    output.open("Priority.txt");
    output << "Statistics for Run" << endl << endl;
    output << "Number of Processes: 500" << endl << endl;
    output << "Total elapsed time (for the scheduler): " << total_elapsed_time << endl << endl;
    output << "Throughput (Processes per unit time): " << throughput << endl;
    output << endl;
    output << "CPU Utilization: " << cpu_utilization << endl << endl;
    output << "Average waiting time (in CPU burst times): " << average_waiting_time << endl << endl;
    output << "Average turnaround time (in CPU burst times): " << average_turnaround_time << endl;
    output << endl;
    output << "Average response time (in CPU burst times): " << average_response_time << endl;
    output.close();
}

int main()
{
    ///to choose desired scheduling to execute
    int input = 0;
    cout << "Select the scheduling algorithm you desire: (1) FIFO, (2) Priority with preemption: ";
    cin >> input;
    cout << endl;
    if(input == 1)
    {
        FIFO();
    }
    else if(input == 2)
    {
        priority();
    }
    else
    {
        cout << "Failure";
    }
    return 0;
}
