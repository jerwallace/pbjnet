
/*******************************************************
 *
 *  Routing Table Routines
 *
 *  Created by Peter Lee, Bahman Razmpa, Jeremy Wallace
 *  University of British Columbia
 *
 *  This is where you will put your routines to implement
 *  the routing table.  You should use the headers as
 *  supplied.  All your code will go in this
 *  file (and in cam.h)
 *
 ******************************************************/

#include "defs.h"
#include "hashmap.cpp"

// Configurable table size constant
const int TABLE_SIZE = 40000;

HashMap routingTable(TABLE_SIZE);

void cam_init()
{
    // Unused.
}

void cam_add_entry(ip_address_t *address, int port)
{
	//cout << "Attempting to add: " << address->n1 <<"."<< address->n2 <<"."<< address->n3 <<"."<< address->n4 << " - to " << port << "\n";
	routingTable.put(*address, port);
}

int cam_lookup_address(ip_address_t *address)
{
	return routingTable.get(*address);
}

void cam_free()
{
	cout << "The largest bucket is: " << routingTable.getBiggestBucketSize() << endl;    
}
