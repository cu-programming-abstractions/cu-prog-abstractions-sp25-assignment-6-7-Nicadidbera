#include "list.h"
#include <stdexcept>

LinkedList::LinkedList() = default;

LinkedList::LinkedList(const LinkedList& other) {
    head = deepCopy(other.head);
}

LinkedList& LinkedList::operator=(LinkedList rhs) {
    std::swap(head, rhs.head);
    return *this;
}
LinkedList::~LinkedList() { freeChain(head); }

void LinkedList::prepend(int value) {
    head = new Node{value, head};
}

void LinkedList::append(int value) {
    Node* newNode = new Node{value, nullptr};

    if (isEmpty()) {
        head = newNode;
    } else {
        Node* curr = head;
        while (curr->next != nullptr) {
            curr = curr->next;
        }
        curr->next = newNode;
    }
}

int LinkedList::removeFront() {
    if (isEmpty()) throw runtime_error("removeFront on empty list");

    Node* oldHead = head;
    int data = oldHead->data;
    head = head->next;
    delete oldHead;
    return data;
}

bool LinkedList::isEmpty() const { return head == nullptr; }

void LinkedList::print(ostream& out) const {
    out << '[';
    for (Node* cur = head; cur; cur = cur->next) {
        out << cur->data;
        if (cur->next) out << " → ";
    }
    out << ']';
}

LinkedList::Node* LinkedList::deepCopy(Node* src) {
    if (src == nullptr) return nullptr;

    Node* newNode = new Node{src->data, nullptr};
    newNode->next = deepCopy(src->next);
    return newNode;
}
void LinkedList::freeChain(Node* n) {
    while (n) {
        Node* next = n->next;
        delete n;
        n = next;
    }
}
