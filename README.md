[//]: # (Image References)
[image1]: ./snapshot/result.png

# Spline-Interpolation-Project


### Goals
When we obtain some data that is discrete data, eg: from the the Analog-to-digital converter card, we need to restore it's original features to analysis it and use it.
In this project, I use the spline-interpolation method to a origin sine-wave data(40 MHz) captured by 250M sampling rate. Trying to restore the original patterns.
This is a very easy read code to understand the spline mechanism.

## Overview  
Here is the video that the spline-interpolation performance dynamic demo(1-40 MHz): https://youtu.be/zNlazi6ewa0
The dynamic video code is more complicated than this project want to perform. 

1. main.cpp : organize all the functions together: Build-DATA, interpolation, DATA-Visualization.

2. interpolation.cpp : It's a simple interpolation core including the spline-method and searching method.

3. matplotlibcpp.h : It's a open source of matplotlibcpp for Cpp.(reference: https://matplotlib-cpp.readthedocs.io/en/latest/) 

4. sys_parameters.h : restore the constants like the speed limit or acceleration limit...

##Environmental setup

1. install VS2019 for Cpp coding.

2. install python38 with numpy and matplotlibcpp

3. add environmental parameters as following
 
->PYTHONHOME: C:\Python38 (your dir. of python) 

->PYTHONPATH: C:\Python38\DLLs;C:\Python38\Lib;C:\Python38\Lib\site-packages;

4. open the CPP project property, adding the include and lib address:
 
->Additional include Directories:  C:\Python38\include

->Additional Library Directories: C:\Python38\libs


## Descriptions

To begining with, we first generate the data from .csv

```cpp
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

```

Then call the spline Interpolation functions.... and calculate it's speed.
In this step, you could try different parameters to understand the change of spline's speed: 

The time range you want to interpolate(Max: original data size)

int time_range = 8192;

The time step you want to interpolate(min: 1)

int time_step = 1; 

the number of search around points

int k = 5; 


```cpp
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
```

Finally, I use matplotlibcpp to visualize the data for comparison.

```cpp
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

```
## Result:　
![image1]




