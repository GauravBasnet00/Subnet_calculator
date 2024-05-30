#include <iostream>
#include <cstdlib>


struct ipv4{
	unsigned int first=0, second=0, third=0,fourth=0 , cidr=0;
};	

const ipv4 classA= {255};
const ipv4 classB = {255,255};
const ipv4 classC = {255,255,255};

using namespace std;

void create_subnet(ipv4 given_ip){
	ipv4 subnet_mask;
	int x = given_ip.cidr/8;
		

}

int main(){
	ipv4 given_ip;
	cout<<"\nEnter the four octets of an ipv4 : "<<"\nFirst octet : ";
	cin>>given_ip.first;
	cout<<"\nSecond octet : ";
	cin>>given_ip.second;
	cout<<"\nThird octet : ";
	cin>>given_ip.third;
	cout<<"\nFouth octet : ";
	cin>> given_ip.fourth;
	cout<<"\nEnter the cidr : ";
	cin>>given_ip.cidr;
	system("clear");
	cout<<"\nThe given ip is : "<<"\t "<<given_ip.first<<"."<<given_ip.second;
	cout<<"."<<given_ip.third<<"."<<given_ip.fourth<<"/"<<given_ip.cidr<<endl;	
	return 0;
}
