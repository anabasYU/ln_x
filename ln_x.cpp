#include <iostream>
#include <math.h>
#include <time.h>

using namespace std;

const double ln2 = 0.6931471805599452862;
double taylor(double value);
double calculous(double value);
double func(double value);

int main()
{
    double value;
    int precision;
    int temp;
    while(1)
    {
        cout << "Please enter the x of ln(x): ";
        cin >> value;
        if (value < 1 || value > 100)
        {
            cout << "The value must between 1 and 100." << endl;
            continue;
        }
        else
        {
            if (value < 10)
            {
                temp = (int)(value * 10000);
                if ((value*10000 - temp) > 0)
                {
                    cout << "The significance digit have to under 5." << endl;
                    continue;
                }
                else
                {
                    break;
                }
            }
            else if (value >= 10)
            {
                temp = (int)(value * 1000);
                if ((value*1000 - temp) > 0)
                {
                    cout << "The significance digit have to under 5." << endl;
                    continue;
                }
                else
                {
                    break;
                }
            }
        }
    }
    cout << "Please enter the precision you want to set(default is 20): ";
    cin >> precision;

    clock_t taylor_start, taylor_finish;
    clock_t calculous_start, calculous_finish;

    taylor_start = clock();
    double taylor_result = taylor(value);
    taylor_finish = clock();
    calculous_start = clock();
    double calculous_result = calculous(value);
    calculous_finish = clock();

    cout.precision(precision);
    cout << "The standard c math ln() function calculate result is : " << log(value) << endl;
    cout << "The value of ln(" << value << ") calculated by taylor is : " << taylor_result << endl;
    cout << "The time of taylor is : " << double(taylor_finish - taylor_start) << "ms"<< endl;
    cout << "The error of taylor compared with c math ln() function is : " << log(value) - taylor_result << endl;
    cout << "The value of ln(" << value << ") calculated by calculous is : " << calculous_result << endl;
    cout << "The time of calculous is : " << double(calculous_finish - calculous_start) << "ms" << endl;
    cout << "The error of calculous compared with c math ln() function is : " << log(value) - calculous_result << endl;

    return 0;
}

double func(double value)
{
    return 1 / value;
}

double calculous(double value)
{
    int n = 1000;
    double h = (value - 1) / n;

    double x;
    double  currentArea = 0.0;
    double totalArea = 0.0;
    for (int i = 1; i <= n; ++i) {
        x = 1 + (i-1)*h;
        currentArea = h * func(x+h);
        totalArea = totalArea + currentArea;
    }

    return totalArea;
}

double taylor(double value)
{
    double scaleValue = value;
    int k = 0;
    while(scaleValue > 2.0)
    {
        scaleValue = scaleValue / 2.0;
        k++;
    }

    double temp = scaleValue - 1;
    double sign = -1;
    double count = 0;
    int n = 1000;

    for (int i = 1; i <= n; ++i) {
        count = count + pow(temp, i) * pow(sign, i-1) / i;
    }
    count = count + k * ln2;

    return count;
}