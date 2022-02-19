#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>
using namespace std;
using namespace std::chrono;

# define M_PI 3.14159265358979323846 
#pragma optimize( " ", on )
class i_am_integral {

	double f(double x) {
		return (4 / ((x * x + 1) * (x * x + 1)));
	}
public:
	void integral(double a, double b, int n) {
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

		double I = h * s;
		double dist = abs(ref - I);
		//cout.setf(ios::scientific);
		cout << "n = " << n << endl;
		//cout << setprecision(5) << "error = " << dist << "  ";
		cout << "Duration is: " << duration.count() << " seconds" << endl;
	}


	void integral_no_vector(double a, double b, int n) {
		double ref = 2 + M_PI;
		double s = (f(a));
		double h = (b - a) / n;


		high_resolution_clock::time_point t1 = high_resolution_clock::now();
		#pragma loop(no_vector)
		for (int i = 1; i <= n - 1; i++)
		{
			s += f(a + i * h);
		}
		high_resolution_clock::time_point t2 = high_resolution_clock::now();
		duration<double> duration = (t2 - t1);

		double I = h * s;
		double dist = abs(ref - I);
		//cout.setf(ios::scientific);
		cout << "n = " << n << endl;
		//cout << setprecision(5) << "error = " << dist << "  ";
		cout << "Duration is: " << duration.count() << " seconds" << endl;
	}

	void integral_parallel(double a, double b, int n) {
		double ref = 2 + M_PI;
		double s = (f(a));
		double h = (b - a) / n;


		high_resolution_clock::time_point t1 = high_resolution_clock::now();
		#pragma loop(hint_parallel(0))
		for (int i = 1; i <= n - 1; i++)
		{
			s += f(a + i * h);
		}
		high_resolution_clock::time_point t2 = high_resolution_clock::now();
		duration<double> duration = (t2 - t1);


		double I = h * s;
		double dist = abs(ref - I);
		//cout.setf(ios::scientific);
		cout << "n = " << n << endl;
		//cout << setprecision(5) << "error = " << dist << "  ";
		cout << "Duration is: " << duration.count() << " seconds" << endl;
	}
};



int main()
{	
	
	i_am_integral integral_1;
	integral_1.integral(-1, 1, 100);
	integral_1.integral(-1, 1, 1000);
	integral_1.integral(-1, 1, 10000);
	integral_1.integral(-1, 1, 100000);
	integral_1.integral(-1, 1, 1000000);
	
	cout << "-------------------------------------------------------------------- "  << endl;

	integral_1.integral_no_vector(-1, 1, 100);
	integral_1.integral_no_vector(-1, 1, 1000);
	integral_1.integral_no_vector(-1, 1, 10000);
	integral_1.integral_no_vector(-1, 1, 100000);
	integral_1.integral_no_vector(-1, 1, 1000000);

	cout << "-------------------------------------------------------------------- "  << endl;

	integral_1.integral_parallel(-1, 1, 100);
	integral_1.integral_parallel(-1, 1, 1000);
	integral_1.integral_parallel(-1, 1, 10000);
	integral_1.integral_parallel(-1, 1, 100000);
	integral_1.integral_parallel(-1, 1, 1000000);
	
	return 0;
}