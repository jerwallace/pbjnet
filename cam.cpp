
/*******************************************************
 *
 *  Routing Table Routines
 *
 *  Created by _________, University of British Columbia
 *
 *  This is where you will put your routines to implement
 *  the routing table.  You should use the headers as
 *  supplied.  All your code will go in this
 *  file (and in cam.h)
 *
 ******************************************************/

#include "defs.h"

/* Note that you probably want to have a data structure
   that is accessable to all routines in this file.  To do
   this, you probably would define some structure (perhaps
   called cam_t in the file cam.h.  Then you could 
   create a variable of this type here by using:

   cam_t cam;

   This will create  a variable called cam (of type cam_h)
   that can be accessed by any routine in this file.  */


class IPHashTable {

private:
	int* port;
	unsigned int tableSize;
	
	unsigned int hashFunc(const ip_address_t* address) {
		unsigned int hash = 5381;
		for (unsigned int i = 0; i < (address->n1+address->n2+address->n3); i++)
			hash = ((hash<<5)+hash) + i;
		return hash % tableSize;
	}

	public:
	IPHashTable(unsigned int size): tableSize(size) {
		port = new int[tableSize];
	}
	~IPHashTable() {
		delete[] port;
	}
	void set (const ip_address_t *address, const int& value) {
		unsigned int index = hashFunc(address);
		std::cout << "Set: "<<index << ": " << value;
		port[index] = value;
	}
	int get(const ip_address_t* address) {
		unsigned int index = hashFunc(address);
		std::cout << "Get: "<< index <<std::endl;
		return port[index];
	}
};

IPHashTable lookupTable(400);

void cam_init()
{

}

void cam_add_entry(ip_address_t *address, int port)
{
	lookupTable.set(address,port);
}

int cam_lookup_address(ip_address_t *address)
{
	return lookupTable.get(address);
}

void cam_free()
{
}
