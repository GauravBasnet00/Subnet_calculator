#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

struct base_ip
{
	unsigned int f_oct, s_oct, t_oct, fo_oct;
};

struct ip_addr
{
	base_ip addr;
	unsigned int cidr;
	base_ip mask;
};

struct subnet
{
	base_ip start;
	base_ip end;
	base_ip mask;
	subnet *next;
};

struct add_factor
{
	base_ip beg;
	base_ip end;
};

// standard subnet mask for the class A - C
const base_ip classA = {255, 0, 0, 0};
const base_ip classB = {255, 255, 0, 0};
const base_ip classC = {255, 255, 255, 0};

const base_ip null_class = {0, 0, 0, 0};
const base_ip all_active = {255, 255, 255, 255};

// invert subnet mask for the addition to find ranges
const base_ip i_classA = {0, 255, 255, 255};
const base_ip i_classB = {0, 0, 255, 255};
const base_ip i_classC = {0, 0, 0, 255};

// Helper function to check if ip is inside the range or not. or bigger than ending address.
bool is_ip_inside_range(base_ip addr, base_ip start, base_ip end)
{
	// Checks if the address is smaller than starting or bigger than ending
	if (addr.f_oct < start.f_oct || addr.f_oct > end.f_oct)
		return false;
	if (addr.s_oct < start.s_oct || addr.s_oct > end.s_oct)
		return false;
	if (addr.t_oct < start.t_oct || addr.t_oct > end.t_oct)
		return false;
	if (addr.fo_oct < start.fo_oct || addr.fo_oct > end.fo_oct)
		return false;
	return true;
}

void match_subnet(ip_addr *ip, subnet *sub_networks)
{
	subnet *current = sub_networks;
	bool found = false;
	while (current != NULL && !found)
	{
		if (is_ip_inside_range(ip->addr, current->start, current->end))
		{
			// Ip is inside range
			cout << "The given ip" << ip->addr.f_oct << "." << ip->addr.s_oct << "." << ip->addr.t_oct << ".";
			cout << ip->addr.fo_oct << "is inside the range" << endl;

			cout << current->start.f_oct << "." << current->start.s_oct << "." << current->start.t_oct << ".";
			cout << current->start.fo_oct << "   -   ";

			cout << current->end.f_oct << "." << current->end.s_oct << "." << current->end.t_oct << ".";
			cout << current->end.fo_oct << endl;
			found = true;
			break;
		}
		current = current->next;
	}
	if (!found)
	{
		cout << "The given IP " << ip->addr.f_oct << "." << ip->addr.s_oct << "." << ip->addr.t_oct << ".";
		cout << ip->addr.fo_oct << " does not belong to any subnet." << endl;
	}
}

subnet *create_subnet(ip_addr *subnetb, add_factor factor)
{
	return NULL;
}

void create_subnetmask(ip_addr *ip)
{ // find subnetmask for the cidr
	add_factor R;
	ip_addr network_add;
	int cidr = ip->cidr;
	int q, r, mask_value = 0;
	q = cidr / 8;
	r = cidr % 8;
	int no_hosts = pow(2, 8 - r);

	for (int i = 0; i < r; i++)
		mask_value += pow(2, 7 - i);

	if (q == 1)
	{
		ip->mask = classA;
		ip->mask.s_oct = mask_value;
		R.beg = null_class;
		R.beg.s_oct = no_hosts;
		R.end = i_classA;
		R.end.s_oct = no_hosts - 1;
		network_add = {ip->addr.f_oct, 0, 0, 0};
	}
	else if (q == 2)
	{
		ip->mask = classB;
		ip->mask.t_oct = mask_value;
		R.beg = null_class;
		R.beg.t_oct = no_hosts;
		R.end = i_classB;
		R.end.t_oct = no_hosts - 1;
		network_add = {ip->addr.f_oct, ip->addr.s_oct, 0, 0};
	}
	else
	{
		ip->mask = classC;
		ip->mask.fo_oct = mask_value;
		R.beg = null_class;
		R.beg.fo_oct = no_hosts;
		R.end = i_classC;
		R.end.fo_oct = no_hosts - 1;
		network_add = {ip->addr.f_oct, ip->addr.s_oct, ip->addr.t_oct, 0};
	}

	/* cout<<"\nThe subnet mask is : ";
	cout<<ip->mask.f_oct<<"."<<ip->mask.s_oct<<"."<<ip->mask.t_oct;
	cout<<"."<<ip->mask.fo_oct<<endl;

	cout<<"\nThe Addition factor R1 : ";
	cout<<R.beg.f_oct<<"."<<R.beg.s_oct<<"."<<R.beg.t_oct;
	cout<<"."<<R.beg.fo_oct<<endl;

	cout<<"\nThe addition factor R2 : ";
	cout<<R.end.f_oct<<"."<<R.end.s_oct<<"."<<R.end.t_oct;
	cout<<"."<<R.end.fo_oct<<endl;

	cout<<"\nThe network addresss is : ";
	cout<<network_add.addr.f_oct<<"."<<network_add.addr.s_oct<<".";
	cout<<network_add.addr.t_oct<<"."<<network_add.addr.fo_oct<<endl;
	*/

	subnet *sub_networks = create_subnet(ip, R);
	match_subnet(ip, sub_networks);
}

int main()
{
	ip_addr user_ip;
	cout << "\nEnter the given ip and the cidr : " << endl;
	cout << "\nEnter the first octet : ";
	cin >> user_ip.addr.f_oct;
	cout << "\nEnter the second octet : ";
	cin >> user_ip.addr.s_oct;
	cout << "\nEnter the third octet : ";
	cin >> user_ip.addr.t_oct;
	cout << "\nEnter the fourth octet : ";
	cin >> user_ip.addr.fo_oct;
	cout << "\n\nEnter the cidr : ";
	cin >> user_ip.cidr;

	cout << "\n\nThe given ip is : \t";
	cout << user_ip.addr.f_oct << "." << user_ip.addr.s_oct << "." << user_ip.addr.t_oct;
	cout << "." << user_ip.addr.fo_oct << " /" << user_ip.cidr << endl;
	create_subnetmask(&user_ip);
	return 0;
}
