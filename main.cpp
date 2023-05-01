#include "queue.h"
#include "queue.cpp"
#include <iostream>
#include <fstream>
#include <time.h>
#include <iomanip>

struct Cashier{
    bool is_free = true;
    int remaining_time = 0, total_working_time = 0;
};

void GetData (int &number_of_cashiers, int &service_time, int &time, float &propability_of_arrival);
void PrintData (int number_of_cashiers, Cashier cashiers[], int service_time, int time, float propability_of_arrival, int clients, int total_waiting_amount, int amount_of_unserviced_clients, int max_time_waited, int max_line_size);

int main()
{
    srand(time(NULL));
    int number_of_cashiers, service_time, time, total_waiting_amount = 0, clients = 0, amount_of_unserviced_clients = 0, max_time_waited = 0, max_line_size = 0;
    float propability_of_arrival, propability;
    GetData(number_of_cashiers, service_time, time, propability_of_arrival);
    Cashier cashiers[number_of_cashiers];
    Queue* line = createQueue();
    for(int i = 0; i < time; ++i)
    {
        for(int j = 0; j < number_of_cashiers; ++j)
        {
            if(cashiers[j].remaining_time > 0)
            {
                --cashiers[j].remaining_time;
                ++cashiers[j].total_working_time;
                if(!cashiers[j].remaining_time)
                {
                    cashiers[j].is_free = true;
                }
            }
        }

        if(!IsItEmpty(line))
        {
            for(int j = 0; j < number_of_cashiers; ++j)
            {
                if(cashiers[j].is_free)
                {
                    cashiers[j].remaining_time += service_time;
                    cashiers[j].is_free = false;
                    total_waiting_amount += i - line->front->key;
                    if(max_time_waited < i - line->front->key)
                    {
                        max_time_waited = i - line->front->key;
                    }
                    deQueue(line);
                    break;
                }
            }
        }

        propability = (float)(rand() % 10 + 1) / 10;
        if(propability <= propability_of_arrival)
        {
            ++clients;
            for(int j = 0; j < number_of_cashiers; ++j)
            {
                if(cashiers[j].is_free)
                {
                    cashiers[j].remaining_time += service_time;
                    cashiers[j].is_free = false;
                    break;
                }
                if(j == number_of_cashiers - 1)
                {
                    enQueue(line, i);
                    if(count(line) > max_line_size)
                    {
                        max_line_size = count(line);
                    }
                }
            }
        }
    }
    amount_of_unserviced_clients = count(line);
    PrintData(number_of_cashiers, cashiers, service_time, time, propability_of_arrival, clients, total_waiting_amount, amount_of_unserviced_clients, max_time_waited, max_line_size);
}
void GetData (int &number_of_cashiers, int &service_time, int &time, float &propability_of_arrival)
{
    std::ifstream in ("data.txt");
    char buffer[30];
    in.getline(buffer, 30);
    in >> number_of_cashiers;
    in.ignore();

    in.getline(buffer, 30);
    in >> service_time;
    in.ignore();

    in.getline(buffer, 30);
    in >> propability_of_arrival;
    in.ignore();

    in.getline(buffer, 30);
    in >> time;
    in.close();
}
void PrintData (int number_of_cashiers, Cashier cashiers[], int service_time, int time, float propability_of_arrival, int clients, int total_waiting_amount, int amount_of_unserviced_clients, int max_time_waited, int max_line_size)
{
    std::cout << "Number of cashiers at the bank: " << number_of_cashiers << std::endl;
    std::cout << "Service time: " << service_time << std::endl;
    std::cout << "Arrival propability of a client during one minute: " << propability_of_arrival << std::endl;
    std::cout << "Bank works for " << time << " minutes." << std::endl;
    std::cout << "Bank was visited by " << clients << " clients." << std::endl;
    std::cout << clients - amount_of_unserviced_clients << " clients were serviced." << std::endl;
    std::cout << amount_of_unserviced_clients << " clients were unserviced." << std::endl;
    std::cout << "Average waiting time: " << std::fixed << std::setprecision(2) << (float)total_waiting_amount / clients << " minutes." << std::endl;
    std::cout << "Longest waiting time: " << max_time_waited << " minutes." << std::endl;
    std::cout << "Longest line: " << max_line_size << std::endl;
    std::cout << "Time cashiers spent working in percents:" << std::endl;
    for(int i = 1; i <= number_of_cashiers; ++i)
    {
        std::cout << std::fixed << std::setprecision(2) << i << " . " << (float)cashiers[i - 1].total_working_time / time * 100 << std::endl;
    }
    std::ofstream out ("res.txt");
    out << "Number of cashiers at the bank: " << number_of_cashiers << std::endl;
    out << "Service time: " << service_time << std::endl;
    out << "Arrival propability of a client during one minute: " << propability_of_arrival << std::endl;
    out << "Bank works for " << time << " minutes." << std::endl;
    out << "Bank was visited by " << clients << " clients." << std::endl;
    out << clients - amount_of_unserviced_clients << " clients were serviced." << std::endl;
    out << amount_of_unserviced_clients << " clients were unserviced." << std::endl;
    out << "Average waiting time: " << std::fixed << std::setprecision(2) << (float)total_waiting_amount / clients << " minutes." << std::endl;
    out << "Longest waiting time: " << max_time_waited << " minutes." << std::endl;
    out << "Longest line: " << max_line_size << std::endl;
    out << "Time cashiers spent working in percents:" << std::endl;
    for(int i = 1; i <= number_of_cashiers; ++i)
    {
        out << std::fixed << std::setprecision(2) << i << " . " << (float)cashiers[i - 1].total_working_time / time * 100 << std::endl;
    }
    out.close();
}