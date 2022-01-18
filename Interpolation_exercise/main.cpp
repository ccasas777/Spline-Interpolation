// Interpolation_exercise.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <time.h>
#include "interpolation.h"
#include "sys_parameters.h"
#include "matplotlibcpp.h"
namespace plt = matplotlibcpp;
using namespace std;



#define DEBUG

int main()
{
    //===========================================================
   //                 Prepare Data
   //===========================================================
    ifstream infile("../data/T40M_250MSPS.csv", ios::in);
    string line;
    vector<struct Point> DATA_40M;
    getline(infile, line);
    while (getline(infile, line)) {
        stringstream ss(line);
        string str;
        Point adc_data;

        getline(ss, str, ',');
        adc_data.x = stod(str) * 4; //unit: ns
        getline(ss, str, ',');
        adc_data.y = stold(str); //unit V

        DATA_40M.push_back(adc_data);

    }
    
    vector<float> x_1, y_1, x_2, y_2;
    for (int i = 0; i < DATA_40M.size(); i++) {
        
        x_1.push_back(DATA_40M[i].x);
        y_1.push_back(DATA_40M[i].y);
    }
    //===========================================================
    //                  Start interpolation
    //===========================================================
    printf("spline_interpolation\r\n");
    std::vector<Point>  DATA_40M_interp;
    interpolation m_interpolation;
    m_interpolation.init();
    m_interpolation.input(&DATA_40M);    
    clock_t start, end;
    float duration;
    
    int time_range = 8192; //unit: ns
    int time_step = 1; //unit :ns
    int k = 5; // the number of search around points

    start = clock();
    DATA_40M_interp = m_interpolation.output(time_range, time_step, k);
    end = clock();
    duration = end - start;
    x_2.clear();
    y_2.clear();
    for (int i = 0; i < DATA_40M_interp.size(); i++) {
        //printf("ind: %d, {%f, %f}\r\n", i, DATA_40M_interp[i].x, DATA_40M_interp[i].y);
        x_2.push_back(DATA_40M_interp[i].x);
        y_2.push_back(DATA_40M_interp[i].y);
    }
    printf("size: %d, duration(ms): %f \r\n", DATA_40M_interp.size(), duration);




    //===========================================================
    //                 Show the result
    //===========================================================

    // Clear previous plot
    plt::clf();
    // Plot line from given x and y data. Color is selected automatically.
    plt::plot(x_2, y_2, { { "marker", "o" }, {"linestyle", " "}, {"label", "Interpolation"} });
    plt::plot(x_1, y_1, {{ "marker", "o" }, {"linestyle", " "},{"label", "Raw data"} });   

    // Plot the label
    plt::ylabel("unit: V");
    plt::xlabel("unit: ns");    
    // Set x-axis interval
    plt::xlim(150, 300);
    // Set y-axis interval
    plt::ylim(-2, 2);
    // Add graph title
    plt::title("adc figure");
    // Enable legend.
    plt::legend();
    // Display plot
    plt::show();
    // Display plot continuously
    //plt::pause(0.01);
    system("pause");

   
    
}