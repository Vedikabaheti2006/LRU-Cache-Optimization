#include <iostream>
#include <unordered_map>

using namespace std;

struct Node {
    int key;
    int value;
    Node* prev;
    Node* next;
    Node(int k, int v) : key(k), value(v), prev(nullptr), next(nullptr) {}
};

class LRUCache {
private:
    int capacity;
    unordered_map<int, Node*> cache; 
    Node* head; 
    Node* tail; 

    void remove(Node* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
    void addToFront(Node* node) {
        node->next = head->next;
        node->prev = head;
        head->next->prev = node;
        head->next = node;
    }

public:
    LRUCache(int cap) : capacity(cap) {
        head = new Node(0, 0);
        tail = new Node(0, 0);
        head->next = tail;
        tail->prev = head;
    }

    int get(int key) {
        if (cache.find(key) == cache.end()) {
            return -1;
        }
        Node* node = cache[key];
        remove(node);
        addToFront(node);
        return node->value;
    }

    void put(int key, int value) {
        if (cache.find(key) != cache.end()) {
            remove(cache[key]);
            delete cache[key];
        }

        Node* newNode = new Node(key, value);
        addToFront(newNode);
        cache[key] = newNode;

        if (cache.size() > capacity) {
            Node* lru = tail->prev;
            remove(lru);
            cache.erase(lru->key);
            delete lru;
        }
    }
};
int main() {
    int cap;
    cout << "--- DSA Project: Optimized LRU Cache (C++) ---" << endl;
    cout << "Enter Cache Capacity: ";
    cin >> cap;

    LRUCache lru(cap);

    while (true) {
        cout << "\nOptions: 1. Put(k, v)  2. Get(k)  3. Exit" << endl;
        int choice;
        cin >> choice;

        if (choice == 1) {
            int k, v;
            cout << "Enter Key: "; cin >> k;
            cout << "Enter Value: "; cin >> v;
            lru.put(k, v);
            cout << "Added (" << k << ", " << v << ") to cache." << endl;
        } else if (choice == 2) {
            int k;
            cout << "Enter Key: "; cin >> k;
            int res = lru.get(k);
            if (res != -1) cout << "Value: " << res << endl;
            else cout << "Key not found!" << endl;
        } else if (choice == 3) {
            break;
        } else {
            cout << "Invalid choice!" << endl;
        }
    }
    return 0;
}
