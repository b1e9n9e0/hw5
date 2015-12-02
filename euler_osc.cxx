#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

void forward (double* const f, const double dt) {
	double x = f[1]*dt + f[0];
	double y = f[1] - f[0]*dt;

	f[0] = x;
	f[1] = y;
}


void backward (double* const f, const double dt) {
	double x = (f[0] + f[1]*dt)/(1+dt*dt);
	double y = (f[1] - f[0]*dt)/(1+dt*dt);

	f[0] = x;
	f[1] = y;
}






int main (int argcount, char** argvector) {

	// basic simulation variables, starting values, time limits and time steps
	const double pi = 3.14159265359;

	const double x_0 = 1;
	const double v_0 = 0;

	const double t_srt = 0;
	const double t_end = 20*pi;

	const double dt_1 = pi/10;
	const double dt_2 = pi/100;

	// arrays to hold the function values, initiate with starting values
	double f_for[2];
	double f_bak[2];

	f_for[0] = x_0;
	f_for[1] = v_0;

	f_bak[0] = x_0;
	f_bak[1] = v_0;

	// filenames 
	const char* fileone = "data_long_step.dat";
	const char* filetwo = "data_short_step.dat";

	// open the first file and print the first line
	ofstream out(fileone);
	out << t_srt << "\t" << f_for[0] << "\t" << f_for[1] << "\t" << f_bak[0] << "\t" << f_bak[1] << endl;

	// iterate over the entire timeframe, call functions and write to file
	for (double t=t_srt+dt_1; t<=t_end; t+=dt_1) {
		forward(f_for, dt_1);
		backward(f_bak, dt_1);

		out << t << "\t" << f_for[0] << "\t" << f_for[1] << "\t" << f_bak[0] << "\t" << f_bak[1] << endl;		
	}

	// close file
	out.close();


	// reinitiate arrays
	f_for[0] = x_0;
	f_for[1] = v_0;

	f_bak[0] = x_0;
	f_bak[1] = v_0;

	// open the second file and print the first line
	out.open(filetwo);
	out << t_srt << "\t" << f_for[0] << "\t" << f_for[1] << "\t" << f_bak[0] << "\t" << f_bak[1] << endl;

	// iterate over the entire timeframe, call functions and write to file
	for (double t=t_srt+dt_2; t<=t_end; t+=dt_2) {
		forward(f_for, dt_2);
		backward(f_bak, dt_2);

		out << t << "\t" << f_for[0] << "\t" << f_for[1] << "\t" << f_bak[0] << "\t" << f_bak[1] << endl;		
	}

	// close file
	out.close();
return 0;
}