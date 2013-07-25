
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

/*
struct cam_t {
	int port;
d	ip_address_t address*;
	cam_t next;
} cam;
*/
class RoutingHashTable {
struct IPNode {
    
    const ip_address_t *address;
    int port;
    IPNode *next;
    
    IPNode() {
        this->address = NULL;
        this->port = NULL;
	this->next = NULL;
    }
    
    IPNode(const ip_address_t *address, const int& value) {
        this->address = address;
        this->port = value;
	this->next = NULL;
    }

    void setNext(IPNode *node) {
    	this->next = node;
    }

    int getPort() {
    	return this->port;
    }
};

private:

IPNode *nodes;
unsigned int tableSize;

unsigned int hashFunc(const ip_address_t *address) {
    int prime = 59;
    unsigned int hash = address->n1+
    address->n2+
    address->n3+
    address->n4*prime;
    return hash % tableSize;
}

bool isSameIP(const ip_address_t *addr1, const ip_address_t *addr2) {
	if (addr1==NULL&&addr2==NULL){
		cout << "Both addresses are null." << endl;
		return TRUE;
	}
	else if (addr1==NULL||addr2==NULL) {
		cout << "Ad1:" << addr1 << "Ad2:" << addr2 << endl;
		cout << "One address is null." << endl;
		return FALSE; }
	else if (addr1->n1 == addr2->n1) {
	   cout << "Addresses not null." << endl;
	   if (addr1->n2 == addr2->n2) {
	   	if (addr1->n3 == addr2->n3) {
			if (addr1->n4 == addr2->n4) {
				return TRUE;
			}
		}
           }
	}
	return FALSE;
}


public:

RoutingHashTable (unsigned int size): tableSize(size) {
    nodes = new IPNode*[tableSize];
    for (unsigned int i = 0; i < tableSize; i++) {
	nodes[i] = NULL;
    } 
}

~RoutingHashTable() {
    for (unsigned int i = 0; i < tableSize; i++) {
    	IPNode* node = nodes[i];
	while (node != NULL) {
		IPNode* prev = node;
		node = node->next;
		delete node;
	}
    }
    delete[] nodes;
}

void setPort(const ip_address_t *address, const int& value) {
    unsigned int index = hashFunc(address);
    cout << "Assigning index:" << index << "-" << address->n1 <<  endl;

    IPNode *parent = NULL;
    IPNode *node = nodes[index];

    while (node!=NULL&&isSameIP(address,node->address)) {
	parent = node;
	node = node->next;
    }

    if (node==NULL) {
	node = new IPNode(address,value);
	if (parent == NULL) {
        	nodes[index] = node;
        } else {
		parent->setNext(node);
	}
    } else {
	node->port = value;
    }

}

int getPort(const ip_address_t *address) {
 
    unsigned int index = hashFunc(address);
    IPNode *node = nodes[index];

    while (node!=NULL) {
	if (isSameIP(address,node->address)) {
        	return node->port;
        } else {
        	node = node->next;
        }
    }
    return -1;

}

};

RoutingHashTable lookupTable(400);

void cam_init()
{

}

void cam_add_entry(ip_address_t *address, int port)
{
	cout << "Attempting to add: " << address->n1 << " to "
 << port << endl;	
	lookupTable.setPort(address,port);
}

int cam_lookup_address(ip_address_t *address)
{
	return lookupTable.getPort(address);
}

void cam_free()
{
}
