
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

// Configurable table size constant
const int TABLE_SIZE = NUMBER_ENTRIES_IN_ROUTING_TABLE;

// Hash node class
class HashNode {
public:
    HashNode(ip_address_t key, int value) :
        _key(key), _value(value), _next(0) {
    }
 
    ip_address_t key() {
        return _key;
    }
    int value() {
        return _value;
    }
    HashNode* next() {
        return _next;
    }
    void setValue(int value) {
        _value = value;
    }
    void setNext(HashNode* next) {
        _next = next;
    }
 
private:
    // Key-value pair
    ip_address_t _key;
    int _value;
 
    HashNode* _next;
};
 
// Hash map class
class HashMap {
public:
    HashMap() {
        table = new HashNode*[TABLE_SIZE];
        for (int i = 0; i < TABLE_SIZE; ++i)
            table[i] = 0;
    }
    ~HashMap() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            HashNode* node = table[i];
            while (node != 0) {
                HashNode* prev = node;
                node = node->next();
                delete prev;
            }
        }
    }
 
    // Should be optimized according to specific needs
    int HashFunc(ip_address_t& key) {
        int index = (key.n1 + key.n2 + key.n3 + key.n4)*59;
		return index % TABLE_SIZE;
    }
 
    int get(ip_address_t& key) {
        int index = HashFunc(key);
        HashNode* node = table[index];
 
        while (node != 0) {
            if (node->key().n1 == key.n1 && node->key().n2 == key.n2 && node->key().n3 == key.n3 && node->key().n4 == key.n4) {
                return node->value();
            }
            node = node->next();
        }
        return -1;
    }
 
    void put(ip_address_t& key, int value) {
        int index = HashFunc(key);
        HashNode* parent = 0;
        HashNode* node = table[index];
 
        while (node != 0 && (node->key().n1 != key.n1 || node->key().n2 != key.n2 || node->key().n3 != key.n3 || node->key().n4 != key.n4)) {
            parent = node;
            node = node->next();
        }
 
        if (node == 0) {
            node = new HashNode(key, value);
            if (parent == 0) {
                table[index] = node;
            } else {
                parent->setNext(node);
            }
        } else {
            node->setValue(value);
        }
    }

    void Remove(ip_address_t& key) {
        int index = HashFunc(key);
        HashNode* node = table[index];
        HashNode* parent = 0;

        while (node != 0) {
            if (node->key().n1 == key.n1 && node->key().n2 == key.n2 && node->key().n3 == key.n3 && node->key().n4 == key.n4) {
                break;
            }
            parent = node;
            node = node->next();
        }
        if (node == 0)
            return;
        else {
            if (parent == 0) {
                table[index] = node->next();
            } else {
                parent->setNext(node->next());
            }
            delete node; 
        }
    }
 
private:
    // Hash table
    HashNode** table;
};

HashMap routingTable;

void cam_init()
{

}

void cam_add_entry(ip_address_t *address, int port)
{
	cout << "Attempting to add: " << address->n1 <<"."<< address->n2 <<"."<< address->n3 <<"."<< address->n4 << " - to " << port << "\n";	
	routingTable.put(*address, port);
}

int cam_lookup_address(ip_address_t *address)
{
	return routingTable.get(*address);
}

void cam_free()
{
	
}
