#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

struct base_ip{
	unsigned int f_oct, s_oct, t_oct, fo_oct;
};

struct ip_addr{
	base_ip addr;
	unsigned int cidr;
	base_ip mask;
};

struct subnet{
	 base_ip start;
	 base_ip end;
	 base_ip mask;
	 subnet *next;
};

int main(){
	ip_addr user_ip;
	cout<<"\nEnter the given ip and the cidr : "<<endl;
	cout<<"\nEnter the first octet : ";
	cin>>user_ip.addr.f_oct;
	cout<<"\nEnter the second octet : ";
	cin >> user_ip.addr.s_oct;
	cout<<"\nEnter the third octet : ";
	cin>> user_ip.addr.t_oct;
	cout<<"\nEnter the fourth octet : ";
	cin>> user_ip.addr.fo_oct;
	cout<<"\n\nEnter the cidr : ";
	cin>> user_ip.cidr;
	
	cout<<"\n\nThe given ip is : \t";
	cout<<user_ip.addr.f_oct<<"."<<user_ip.addr.s_oct<<"."<<user_ip.addr.t_oct;
	cout<<"."<<user_ip.addr.fo_oct<<" /"<<user_ip.cidr<<endl;
	return 0;
}
