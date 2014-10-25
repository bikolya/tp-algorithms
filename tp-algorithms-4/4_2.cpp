#include <iostream>
#include <deque>

class Deque_elem {
public:
	int data;
	Deque_elem *prev;
	Deque_elem *next;
};

class Deque {
public:
	Deque() {
		head = NULL;
		tail = NULL;
    }

	~Deque() {
    }

	void push_back(int a);
	void push_front(int a);
	int  pop_back();
	int  pop_front();

private:
	Deque_elem *head;
	Deque_elem *tail;
};

void Deque::push_back(int a) {
	if(tail != NULL) {
		tail->prev = new Deque_elem;
		tail->prev->data = a;
		tail->prev->next = tail;
		tail->prev->prev = NULL;
		tail = tail->prev;
	}
	else {
		tail = head = new Deque_elem;
		tail->data = a;
		tail->next = NULL;
		tail->prev = NULL;
	}
}

void Deque::push_front(int a) {
	if(head != NULL) {
		head->next = new Deque_elem;
		head->next->data = a;
		head->next->prev = head;
		head->next->next = NULL;
		head = head->next;
	}
	else {
		tail = head = new Deque_elem;
		tail->data = a;
		tail->next = NULL;
		tail->prev = NULL;
	}
}

int Deque::pop_back() {
	int a = 0;
	if(tail != NULL) {
		a = tail->data;
		if(tail != head) {
		    tail = tail->next;
		    delete tail->prev;
		    tail->prev = NULL;
		}
		else {
			delete tail;
			tail = head = NULL;
		}
	}
	else {
		a = -1;
	}
	return a;
}

int Deque::pop_front() {
	int a = 0;
	if(head != NULL) {
		a = head->data;
		if(tail != head) {
		    head = head->prev;
		    delete head->next;
		    head->next = NULL;
		}
		else {
			delete head;
			tail = head = NULL;
		}
	}
	else {
		a = -1;
	}
	return a;
}

int main() {
    Deque deck;
	int n, a, b;
    bool yes_flag = true;
    std::cin >> n;
    for (int i = 0; i < n && yes_flag; ++i) {
        std::cin >> a >> b;
		switch(a) {
            case 1:
                deck.push_back(b);
                break;
            case 2:
                if (deck.pop_back() != b)
                    yes_flag = false;
                break;
            case 3:
                deck.push_front(b);
                break;
            case 4:
                if (deck.pop_front() != b)
                    yes_flag = false;
                break;
            default:
                break;
        }
	}
    if (yes_flag)
        std::cout << "YES";
    else
        std::cout << "NO";
	return 0;
}
