
#include"interpolation.h"


interpolation::interpolation() {
   
}

interpolation::~interpolation() {

}

bool interpolation::init() {     
    N = 100;
    output_data.clear();
    return true;
}

void interpolation::input(std::vector<Point>* data) {    
    input_data = *data;
    N = input_data.size();   
   
}
std::vector<Point> interpolation::output(int time_range,int time_step,int k) {
    float tmp = 0;
    Point tt;

    for (int i = 0; i < time_range; i+= time_step) {
        tmp = spline_interpolation(i, k);
        tt.x = float(i);
        tt.y = tmp;
        output_data.push_back(tt);
    }
   
    return output_data;
}

// neville(x) within interval [L,R)
float interpolation::spline(float x, int L, int R)
{
    float y[100000];

    for (int i = L; i < R; ++i) y[i] = input_data[i].y;
    for (int j = 1; j < R - L + 1; ++j)
        for (int i = L; i < R - j; ++i)
            y[i] = ((x - input_data[i + j].x) * y[i] - (x - input_data[i].x) * y[i + 1]) / (input_data[i].x - input_data[i + j].x);

    return y[L];
}

float interpolation::spline_interpolation(float x, int k)
{
    int n = 0;
    while (n < N && x >= input_data[n].x) n++;
    if (x == input_data[n].x) return input_data[n].y;
    if (k > N) k = N;
    if (k < 2) k = 2;
    int L = n - k / 2;
    int R = L + k;
    if (L < 0) { L = 0; R = k; }
    if (R > N) { R = N; L = N - k; }
    if (L < 0) L = 0;
    if (R > N) R = N;
    return spline(x, L, R);
}
