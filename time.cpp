#include<iostream>
using namespace std;
class time
{
	int hours;
	int minutes;
	int seconds;
	public:
		void gettime(int h,int m,int s)
		{
			hours=h;
			minutes=m;
			seconds=s;
		}
		void puttime()
		{
			cout<<hours<<"hours ";
			cout<<minutes<<"minutes & ";
			cout<<seconds<<"seconds"<<endl;
		}
		void sum(time, time);
};
void time::sum(time t1,time t2)
{
	seconds=t1.seconds+t2.seconds;
	minutes=seconds/60;
	seconds=seconds%60;
	minutes=minutes+t1.minutes+t2.minutes;
	hours=minutes/60;
	minutes=minutes%60;
	hours=hours+t1.hours+t2.hours;
}
int main()
{
	time T1,T2,T3;
	T1.gettime(1,45,60);
	T2.gettime(2,30,30);
	T3.sum(T1,T2);
	cout<<"T1=";
	T1.puttime();
	cout<<"\nT2=";
	T2.puttime();
	cout<<"\nT3=";
	T3.puttime();
	return 0;
}
