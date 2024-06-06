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
			cout << "The given ip \t" << ip->addr.f_oct << "." << ip->addr.s_oct << "." << ip->addr.t_oct << ".";
			cout << ip->addr.fo_oct << "\tis inside the range" << endl;

			cout << current->start.f_oct << "." << current->start.s_oct << "." << current->start.t_oct << ".";
			cout << current->start.fo_oct << "   -   ";

			cout << current->end.f_oct << "." << current->end.s_oct << "." << current->end.t_oct << ".";
			cout << current->end.fo_oct << endl;
			if( ip->addr.f_oct == current->start.f_oct && ip->addr.s_oct == current->start.s_oct &&
				ip->addr.t_oct == current->start.t_oct && ip->addr.fo_oct == current->start.fo_oct ){
				cout<<"It is not an usable IP as it is a network address.";
			}
			else if( ip->addr.f_oct == current->end.f_oct && ip->addr.s_oct == current->end.s_oct &&
				ip->addr.t_oct == current->end.t_oct && ip->addr.fo_oct == current->end.fo_oct ){
				cout<<"It is not an usable IP as it is a broadcast address.";
			}
			else
				cout<<"It is a usable address whose network ip is: "<< current->start.f_oct << "." ;
				cout<< current->start.s_oct << "." << current->start.t_oct << "."<< current->start.fo_oct << " and the broadcast address is: ";
				cout << current->end.f_oct << "." << current->end.s_oct << "." << current->end.t_oct << ".";
				cout << current->end.fo_oct << endl;
			found = true;
			
		}
		current = current->next;
	}
	if (!found)
	{
		cout << "The given IP " << ip->addr.f_oct << "." << ip->addr.s_oct << "." << ip->addr.t_oct << ".";
		cout << ip->addr.fo_oct << " does not belong in any subnet." << endl;
	}
}

void list_traverse(subnet *list){
	if (list == NULL){
		cout<<"NO data"<<endl;
	}
	else {
		subnet  *pthis = list;
		int i=1;
		while (pthis != NULL){
			cout<<endl<<endl<<i<<".\nStart phase " ;
			cout<<pthis->start.f_oct<<"."<<pthis->start.s_oct<<"."<<pthis->start.t_oct<<"."<<pthis->start.fo_oct<<endl;
		cout<<"End Phase : ";
		cout<<pthis->end.f_oct<<"."<<pthis->end.s_oct<<"."<<pthis->end.t_oct<<"."<<pthis->end.fo_oct<<endl;
			
	pthis = pthis->next;
	i++;
	}
	}
}

subnet *create_subnet(ip_addr *subnetb, add_factor factor)
{        subnet *new_subnet;
		 subnet *pfirst  = NULL;
		 subnet *pthis = NULL;
	 	 subnet subnet_t ;
		subnet_t.start = subnetb->addr;
	 	add_factor news = factor;
		factor.beg = null_class;

	 	int x = subnetb->cidr % 8;
		int y = pow(2,x);	
	
	 	for(int i=1;i<=y;i++) {

			new_subnet = new subnet;
			new_subnet->next = NULL;
			
			new_subnet->start.f_oct = subnet_t.start.f_oct + factor.beg.f_oct;
			new_subnet->start.s_oct = subnet_t.start.s_oct + factor.beg.s_oct;
   			new_subnet->start.t_oct = subnet_t.start.t_oct + factor.beg.t_oct;
   			new_subnet->start.fo_oct = subnet_t.start.fo_oct + factor.beg.fo_oct;
   			 
   			new_subnet->end.f_oct = new_subnet->start.f_oct + factor.end.f_oct;
		    new_subnet->end.s_oct = new_subnet->start.s_oct + factor.end.s_oct;
		    new_subnet->end.t_oct = new_subnet->start.t_oct + factor.end.t_oct;
		    new_subnet->end.fo_oct = new_subnet->start.fo_oct + factor.end.fo_oct;
		 	subnet_t = *new_subnet;		

		if (pfirst==NULL){
				pfirst = new_subnet;
				factor.beg = news.beg;
		}
				
		else{
			pthis = pfirst;
				
			while(pthis->next != NULL){
			pthis = pthis->next;
			}

			pthis->next = new_subnet;
				
			}
	}	
	
	list_traverse(pfirst);
	cout<<endl<<endl;
	return pfirst;
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
	network_add.cidr = cidr;

	subnet *sub_networks = create_subnet(&network_add, R);
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
