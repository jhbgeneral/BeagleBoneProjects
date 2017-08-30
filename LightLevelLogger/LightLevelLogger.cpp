#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <ctime>


// Assume the screen is wide enough for this many more characters for the pointer
#define WIDTH 150

// The range of the ADC, 12 bits, 0 - 4095
#define RANGE 4096

// Sample the adc with this interval
#define SAMPLE_INTERVAL 10L // seconds

// Log to this file name
#define LOGNAME "/home/debian/lightLog"

using namespace std;



int main ()
{
	int val = 0;
	time_t t;		// Time now
	struct tm * now;	// In struct tm* format

	fstream adcIn;
	fstream logOut;

	cout << "Light Logger, starting" << endl;

	logOut.open (LOGNAME, fstream::out | fstream::app);

	while (1)
	{
		//
		// Get the date and time
		//
		t = time (0);		// Get the time now
		now = localtime (&t);	// Get the time in the struct tm* format

		cout	<< setfill ('0') << setw (4) << (now->tm_year + 1900) << '/' 
			<< setfill ('0') << setw (2) << (now->tm_mon + 1) << '/'
			<< setfill ('0') << setw (2) << now->tm_mday << " "
			<< setfill ('0') << setw (2) << now->tm_hour << ":" 
			<< setfill ('0') << setw (2) << now->tm_min << ":"
			<< setfill ('0') << setw (2) << now->tm_sec << "\t";

		logOut	<< setfill ('0') << setw (4) << (now->tm_year + 1900) << '/' 
			<< setfill ('0') << setw (2) << (now->tm_mon + 1) << '/'
			<< setfill ('0') << setw (2) << now->tm_mday << " "
			<< setfill ('0') << setw (2) << now->tm_hour << ":" 
			<< setfill ('0') << setw (2) << now->tm_min << ":"
			<< setfill ('0') << setw (2) << now->tm_sec << "\t";

		// Get the raw light value from the ADC
		adcIn.open ("/sys/bus/iio/devices/iio:device0/in_voltage0_raw", fstream::in);
		adcIn >> val;
		adcIn.close();

		// Send the raw value to the console and log file
		cout << setw (4) << right << val << "\t";
		logOut << setw (4) << right << val << "\t";

		// Output a line of dots highlighted with ^ proportional to val
		int loc = val * WIDTH / RANGE;	// loc will be 0 to WIDTH - 1
		for (int j = 0; j < WIDTH; j++)
		{
			cout << (j == loc ? "^" : "_");
			logOut << (j == loc ? "^" : "_");
		}

		cout << endl;
		logOut << endl;
		usleep (SAMPLE_INTERVAL * 1000000L);
	}
	cout << endl;
}
