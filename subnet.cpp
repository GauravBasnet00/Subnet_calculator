#include <iostream>
#include <cstdlib>

struct ipv4
{
	unsigned int first, second, third, fourth, cidr;
};

const ipv4 classA = {255, 0, 0, 0, 8};
const ipv4 classB = {255, 255, 0, 0, 16};
const ipv4 classC = {255, 255, 255, 0, 24};

using namespace std;

ipv4 create_subnet_mask(ipv4 given_ip)
{
	ipv4 subnet_mask;
	int calc_class = given_ip.cidr / 8;
	switch (calc_class)
	{
	case 1:
		subnet_mask = classA;
		break;
	case 2:
		subnet_mask = classB;
		break;
	case 3:
		subnet_mask = classC;
		break;
	default:
		break;
	}
	return subnet_mask;
}

int main()
{
	ipv4 given_ip;
	cout << "\nEnter the four octets of an ipv4 : " << "\nFirst octet : ";
	cin >> given_ip.first;
	cout << "\nSecond octet : ";
	cin >> given_ip.second;
	cout << "\nThird octet : ";
	cin >> given_ip.third;
	cout << "\nFouth octet : ";
	cin >> given_ip.fourth;
	cout << "\nEnter the cidr : ";
	cin >> given_ip.cidr;

	cout << "\nThe given ip is : " << "\t " << given_ip.first << "." << given_ip.second;
	cout << "." << given_ip.third << "." << given_ip.fourth << "/" << given_ip.cidr << endl;
	ipv4 subnet = create_subnet_mask(given_ip);
	cout << "\nThe Subnet is : " << "\t " << subnet.first << "." << subnet.second;
	cout << "." << subnet.third << "." << subnet.fourth << "/" << subnet.cidr << endl;
	return 0;
}
