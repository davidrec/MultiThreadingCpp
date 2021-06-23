#include <iostream>
#include <thread>
#include <windows.h>
#include <synchapi.h>
using namespace std;


void print(string str)
{
    cout << str.c_str();
}
// A dummy function
void SaveToDB(string study_insance_uid)
{
	//Simulating function that taks time async. 
    print("SaveToDB() -- connecting to DB\n");
    Sleep(5000);
    print("SaveToDB() --  connected, inserting " + study_insance_uid + " and commit\n");
    Sleep(2000);
    print("SaveToDB() -- stored to DB\n");
}


// A callable object
class fir_thread_obj {
public:
    void operator()(string study_insance_uid)
    {
		//Simulating function that taks time async. 
        print("fir_thread_obj() --  save to FIR " + study_insance_uid + "\n");
        Sleep(5000);
        print("fir_thread_obj() -- " + study_insance_uid + " saved to FIR\n");
    }
};



int main()
{
    string study_inctance_uid = "1.1.1.1";
    print("Main() --  Threads 1 and 2 and 3 operating independently\n");

    // This thread is launched by using 
    // function pointer as callable
    thread th1(SaveToDB, study_inctance_uid);

    // This thread is launched by using
    // function object as callable
    thread th2(fir_thread_obj(), study_inctance_uid);

    // Define a Lambda Expression
    auto lamdaPatientMatching = [](string study_inctance_uid) {
        print("lamdaPatientMatching() -- seraching for patient matching\n");
        Sleep(1000);
        print("lamdaPatientMatching() -- " + study_inctance_uid + " match to patient 123\n");
    };

    // This thread is launched by using 
    // lamda expression as callable
    thread th3(lamdaPatientMatching, study_inctance_uid);

    // Wait for the threads to finish

    // Wait for thread t1 to finish
    th1.join();

    // Wait for thread t2 to finish
    th2.join();

    // Wait for thread t3 to finish
    th3.join();
    print("Main() -- Finish");
    return 0;
}


