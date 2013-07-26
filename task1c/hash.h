 
// Hash node class
class HashNode {
public:
    HashNode(ip_address_t key, int value);
 
    ip_address_t key();
    int value();
    HashNode* next();
    void set_value(int value);
    void set_next(HashNode* next);
 
private:
    // Key-value pair
    ip_address_t _key;
    int _value;
    HashNode* _next;
};
 
// Hash map class
class HashMap {
public:
    HashMap();
    ~HashMap();
 
    // Should be optimized according to specific needs
    int HashFunc(ip_address_t key);
    void Put(ip_address_t key, int value);
    void Remove(ip_address_t key);
 
private:
    // Hash table
    HashNode** _table;
};