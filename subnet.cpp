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
	unsigned int cidr;
	subnet *next;
};

struct add_factor{
	base_ip beg;
	base_ip end;
};


// standard subnet mask for the class A - C
const base_ip classA = {255, 0, 0, 0};
const base_ip classB = {255, 255, 0, 0};
const base_ip classC = {255, 255, 255, 0};

const base_ip null_class = {0, 0, 0, 0};

// invert subnet mask for the addition to find ranges
const base_ip i_classA = {0, 255, 255, 255};
const base_ip i_classB = {0, 0, 255, 255};
const base_ip i_classC = {0, 0, 0, 255};


void print_octets(base_ip octet){
	cout<<octet.f_oct<<"."<<octet.s_oct<<"."<<octet.t_oct<<"."<<octet.fo_oct;
}


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

			print_octets(current->start);
			cout << "   -   ";

			print_octets(current->end);
			cout << endl;

			if( ip->addr.f_oct == current->start.f_oct && ip->addr.s_oct == current->start.s_oct &&
				ip->addr.t_oct == current->start.t_oct && ip->addr.fo_oct == current->start.fo_oct ){
				cout<<"It is not an usable IP as it is a network address.";
			}
			else if( ip->addr.f_oct == current->end.f_oct && ip->addr.s_oct == current->end.s_oct &&
				ip->addr.t_oct == current->end.t_oct && ip->addr.fo_oct == current->end.fo_oct ){
				cout<<"It is not an usable IP as it is a broadcast address.";
			}
			else
				cout<<"\n\nIt is a usable address with following as : \n Network id :  ";
				print_octets(current->start);
				cout << "\n Broadcast address : ";
				print_octets(current->end);
				cout<<endl;

				cout<<endl<<" Host IP range : \n ";	
				if (current->cidr == 31){
					cout<<"\nNo hosts possible for the subnetwork.\n";
				}
				else {
					cout<<current->start.f_oct<<"."<<current->start.s_oct<<"."<<current->start.t_oct<<"."<<current->start.fo_oct+1<<" - ";
					cout<<current->end.f_oct<<"."<<current->end.s_oct<<"."<<current->end.t_oct<<"."<<current->end.fo_oct-1<<endl;
				}
			found = true;
			
		}
		current = current->next;
	}
	if (!found)
	{
		cout << "The given IP ";
		print_octets(ip->addr);
		cout<<" does not belong in any subnet." << endl;
	}
}

void list_traverse(subnet *list){
	if (list == NULL){
		cout<<"NO data"<<endl;
	}
	else {
		subnet  *pthis = list;
		int i=1;
		cout<<endl<<endl;
		int cidr = pthis->cidr;
		cout<<"Index\t\t Network Id \t\t\tUsable Host Address  \t\t\t\tBroadcast Id"<<endl<<endl;
		while (pthis != NULL){
			cout<<i<<". \t\t  ";
			print_octets(pthis->start);
			cout<<"\t\t\t";
			if (cidr == 31)
				cout<<"No hosts possible\t\t\t\t";
			else {
				cout<<pthis->start.f_oct<<"."<<pthis->start.s_oct<<"."<<pthis->start.t_oct<<"."<<pthis->start.fo_oct+1<<" - ";
				cout<<pthis->end.f_oct<<"."<<pthis->end.s_oct<<"."<<pthis->end.t_oct<<"."<<pthis->end.fo_oct-1<<"\t\t\t";
			}
			print_octets(pthis->end);
			cout<<endl;

			pthis = pthis->next;
			i++;
		}
	}
}

subnet *create_subnet(ip_addr *subnet_id, add_factor factor){        
		subnet *new_subnet;
		subnet *pfirst  = NULL;
		subnet *pthis = NULL;
	 	subnet subnet_temp ;
		subnet_temp.start = subnet_id->addr;
	 	add_factor original = factor;
		factor.beg = null_class;   // it is set to null class as an exception to generate the first subnetid 
		int cidr = subnet_id->cidr;
	 	int x = cidr % 8;
		int y = pow(2,x);	
	
	 	for(int i=1;i<=y;i++) {

			new_subnet = new subnet;
			new_subnet->next = NULL;
			new_subnet->cidr = cidr;
	
			new_subnet->start.f_oct = subnet_temp.start.f_oct + factor.beg.f_oct;
			new_subnet->start.s_oct = subnet_temp.start.s_oct + factor.beg.s_oct;
   			new_subnet->start.t_oct = subnet_temp.start.t_oct + factor.beg.t_oct;
   			new_subnet->start.fo_oct = subnet_temp.start.fo_oct + factor.beg.fo_oct;
   			 
   			new_subnet->end.f_oct = new_subnet->start.f_oct + factor.end.f_oct;
		    new_subnet->end.s_oct = new_subnet->start.s_oct + factor.end.s_oct;
		    new_subnet->end.t_oct = new_subnet->start.t_oct + factor.end.t_oct;
		    new_subnet->end.fo_oct = new_subnet->start.fo_oct + factor.end.fo_oct;
		 	subnet_temp = *new_subnet;		

		if (pfirst==NULL){
				pfirst = new_subnet;
				factor = original;
		}
				
		else{
			pthis = pfirst;
				
			while(pthis->next != NULL){
			pthis = pthis->next;
			}

			pthis->next = new_subnet;
				
			}
	}	
	
	cout<<endl<<endl;
	cout<<"Total no of hosts : "<<pow(2,32-cidr);
	cout<<"\nTotal no of sub-nets : "<< y; 	
	cout<<"\nSubnet Mask : ";
	print_octets(subnet_id->mask);
	cout<<endl;

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
	//no_hosts here don't indicate the total no of hosts in the network rather it denotes the total no of bits of the octet to be used for the hosts

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

	network_add.cidr = cidr;
	network_add.mask = ip->mask;
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
	print_octets(user_ip.addr);
	cout<<"/"<<user_ip.cidr<<endl;
	if (user_ip.cidr == 32){
		cout<<"\nThe give ip  :  ";
		print_octets(user_ip.addr);
		cout<<" doesn't have any useable ip address. And it lacks the valid sub-networks as well."<<endl;
	}
	else 
		create_subnetmask(&user_ip);

	return 0;
}
