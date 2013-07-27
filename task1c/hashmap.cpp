
/*******************************************************
 *
 *  Routing Table Routines
 *
 *  Created by Peter Lee, Bahman Razmpa and Jeremy Wallace
 *  University of British Columbia
 *
 *  This data structure was created to store ip_address_t elements
 *  as a key and match them to ports.
 *
 ******************************************************/

/**
 * The hash node class contains the data structure of each node that is stored in the hash map.
 */
class HashNode {
public:
    
    /**
     * Constructor initializes the hash map node.
     * @param key The IP Address to use as the key of the node.
     * @param value The port number to store in the node.
     */
    HashNode(ip_address_t key, int value) :
        _key(key), _value(value), _next(0) {
    }

    /**
     * Getters and setters are below for all of the stored data.
     */
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


/**
 * The HashMap class stores ip address nodes in the map based on a hashed algorithm.
 * In this case, we use the sum of the IP address octets and multiply it by a prime number (59).
 * This is to ensure low distribution in the index values.
 */
class HashMap {
public:

    /**
     * The constructor initializes the table.
     * @param tableSize the size of the table.
     */
    HashMap(int size) : tableSize(size) {
	biggestBucket = 0;
        table = new HashNode*[tableSize];
        for (int i = 0; i < tableSize; ++i)
            table[i] = 0;
    }

    /**
     * The destructor clears the hash map from memory.
     */
    ~HashMap() {
        for (int i = 0; i < tableSize; ++i) {
            HashNode* node = table[i];
            while (node != 0) {
                HashNode* parent = node;
                node = node->next();
                delete parent;
            }
        }
    }

    /**
     * This method returns a port number based on the ip address.
     * @param key: The reference of the IP address that we need to find in the map.
     * @return The IP address port number.
     */
    int get(ip_address_t& key) {
        int index = hashFunc(key);
        HashNode* node = table[index];

        while (node != 0) {
            if (node->key().n1 == key.n1 && node->key().n2 == key.n2 && node->key().n3 == key.n3 && node->key().n4 == key.n4) {
                return node->value();
            }
            node = node->next();
        }
        return -1;
    }

    /**
     * The biggest bucket in the hash map.
     */
    int getBiggestBucketSize() {
	return biggestBucket;
    }

    /**
     * This method adds a new record to the hash map.
     * @param key The IP address key
     * @param value The port number for this address.
     */
    void put(ip_address_t& key, int value) {
        int index = hashFunc(key);
        int numInBucket = 0;

	HashNode* parent = 0;
        HashNode* node = table[index];

        while (node != 0 && (node->key().n1 != key.n1 || node->key().n2 != key.n2 || node->key().n3 != key.n3 || node->key().n4 != key.n4)) {
            parent = node;
            node = node->next();
	    numInBucket++;
        }

        if (node == 0) {
            node = new HashNode(key, value);
            if (parent == 0) {
                table[index] = node;
            } else {
		numInBucket++;
                parent->setNext(node);
            }
        } else {
            node->setValue(value);
        }
	
	if (numInBucket > biggestBucket)
		biggestBucket = numInBucket;
    }

    /**
     * This method is used to remove an address from the hash map.
     * @param key The IP address to remove.
     */
    void remove(ip_address_t& key) {
        int index = hashFunc(key);
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

    /**
     * The hash function that is used to generate the index.
     * In this case, we used the sum of the IP address octets and multiplied it by 59.
     * @param key The IP Address to create a hash index for.
     */
    int hashFunc(ip_address_t& key) {
        int index = (key.n1*67 + key.n2*97 + key.n3*83 + key.n4*61);
		return index % tableSize;
    }

    int biggestBucket;
    int tableSize;
    // The hash table.
    HashNode** table;
};
