#pragma once
#include <vector>
#include "sys_parameters.h"

class interpolation {
    public:
        interpolation();
        ~interpolation();
        bool init();
        int N;
   
        std::vector<Point> input_data;
        std::vector<Point> output_data;
        void input(std::vector<Point>* data);
        std::vector<Point> output(int time_range, int time_step, int k);
        float spline(float x, int L, int R);
        float spline_interpolation(float x, int k);
};
