
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
struct IPNode {
    
    ip_address_t *address;
    int port;
    IPNode *next = NULL;
    
    IPNode() {
        address = NULL;
        port = NULL;
    }
    
    IPNode(const ip_address_t *address, const int& value) {
        address = address;
        port = value;
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


IPNode* find(IPNode *node, const ip_address_t *address, bool getTail) {
    
    if (node==NULL) return NULL;
    else {
        if (node->address == address) {
            return node;
        }
        else {
            if (node->next==NULL&&getTail) {
                return node;
            } else {
                return find(node->next,address,getTail);
            }
        }
    }
    
}


public:

RoutingHashTable (unsigned int size): tableSize(size) {
    nodes = new IPNode[tableSize];
}

~RoutingHashTable() {
    delete[] nodes;
}

void setPort(const ip_address_t *address, const int& value) {
    unsigned int index = hashFunc(address);
    IPNode *newNode = new IPNode(address,value);
    IPNode *parentNode = find(&nodes[index],address,true);
    
    if (parentNode==NULL) {
        nodes[index] = *newNode;
    } else {
        nodes[index].next = newNode;
    }
    
}

int getPort(const ip_address_t *address) {
    unsigned int index = hashFunc(address);
    IPNode *node = find(&nodes[index],address,false);
    if (node==NULL) {
        return -1;
    } else {
        return node->port;
    }
}

};

RoutingHashTable lookupTable(400);

void cam_init()
{

}

void cam_add_entry(ip_address_t *address, int port)
{
	lookupTable.setPort(address,port);
}

int cam_lookup_address(ip_address_t *address)
{
	return lookupTable.getPort(address);
}

void cam_free()
{
}
