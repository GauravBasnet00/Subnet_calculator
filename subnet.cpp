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

struct add_factor{
	base_ip beg;
	base_ip end;
};


const base_ip classA = {255,0,0,0};
const base_ip classB = {255,255,0,0};
const base_ip classC = {255,255,255,0};

void match_subnet(){}

subnet *create_subnet(ip_addr *subnet, add_factor factor){
		subnet *new_subnet = new subnet;
	for(i=1;i<=cidr;i++){
			 new_subnet->start.f_oct = subnet->addr.f_oct + factor.beg.f_oct;
			 new_subnet->start.s_oct = subnet->addr.s_oct + factor.beg.s_oct;
   			 new_subnet->start.t_oct = subnet->addr.t_oct + factor.beg.t_oct;
   			 new_subnet->start.fo_oct = subnet->addr.fo_oct + factor.beg.fo_oct;
   			 
   			new_subnet->end.f_oct = subnet->addr.f_oct + factor.end.f_oct;
		    new_subnet->end.s_oct = subnet->addr.s_oct + factor.end.s_oct;
		    new_subnet->end.t_oct = subnet->addr.t_oct + factor.end.t_oct;
		    new_subnet->end.fo_oct = subnet->addr.fo_oct + factor.end.fo_oct;
	}
}

void create_subnetmast(ip_addr *ip){}

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
