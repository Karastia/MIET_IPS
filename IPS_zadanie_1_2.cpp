#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>
using namespace std;
using namespace std::chrono;

# define M_PI 3.14159265358979323846 
#pragma optimize( " ", on )

	double f(double x) {
		return (4 / ((x * x + 1) * (x * x + 1)));
	}

	void integral(double a, double b, int n, double& result) {
		double ref = 2 + M_PI;
		double s = (f(a));
		double h = (b - a) / n;

		high_resolution_clock::time_point t1 = high_resolution_clock::now();
		for (int i = 1; i <= n - 1; i++)
		{
			s += f(a + i * h);
		}
		high_resolution_clock::time_point t2 = high_resolution_clock::now();
		duration<double> duration = (t2 - t1);

		result = duration.count();
	}



int main()
{
	for (int n = 100; n <= 1000000; n = n * 10)
	{
		double area1 = 0;
		double area2 = 0;
		double area3 = 0;
		double area4 = 0;

		std::thread thr1(integral, -1, -0.5, n, std::ref(area1));
		std::thread thr2(integral, -0.5, 0, n, std::ref(area2));
		std::thread thr3(integral, 0, 0.5, n, std::ref(area3));
		std::thread thr4(integral, 0.5, 1, n, std::ref(area4));
		thr1.join();
		thr2.join();
		thr3.join();
		thr4.join();
		double area = area1 + area2 + area3 + area4;

		cout << "Result " << area << "   n = " << n << endl;
		cout << "----------------------------------" << endl;
	}
	return 0;
}