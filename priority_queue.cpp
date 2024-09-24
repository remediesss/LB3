#include <iostream>
#include <cstdint>
#include <string>
#include <limits>

struct node;

void delete_node(node* n);
void info_for_node(node* temp);

struct node {
    std::string     data;
    uint32_t        priority;
    node*           next;
    node*           prev;

    explicit node(const std::string& str, uint32_t prior)
        : data(str), priority(prior), next(nullptr), prev(nullptr) 
    {}
};

struct priority_queue {

    priority_queue() : head(nullptr), tail(nullptr), max_prior(0) 
    {}
    ~priority_queue() 
    {
        while (node* n = pop()) 
        {
            delete n;
        }
    }

    void append(node* new_node) 
    {
        if (!head) {
            head = tail = new_node;
            max_prior = new_node->priority;
            return;
        }

        node* temp = head;
        while (temp != nullptr && new_node->priority >= temp->priority) 
        {
            temp = temp->next;
        }

        if (temp == head) 
        {
            new_node->next = head;
            head->prev = new_node;
            head = new_node;
        }
        else if (!temp)
        {
            tail->next = new_node;
            new_node->prev = tail;
            tail = new_node;
        }
        else 
        {
            new_node->next = temp;
            new_node->prev = temp->prev;
            temp->prev->next = new_node;
            temp->prev = new_node;
        }

        if (new_node->priority > max_prior)
        {
            max_prior = new_node->priority;
        }
    }

    void printAll() const 
    {
        if (!head) 
        {
            std::cout << "Queue is empty\n\n";
            return;
        }
        node* temp = head;
        while (temp != nullptr) 
        {
            info_for_node(temp);
            temp = temp->next;
        }
    }

    node* pop() 
{
    if (!tail) { return nullptr; }

    node* temp = tail;

    if (head == tail) 
    {
        head = nullptr;
        tail = nullptr;
    } 
    else 
    {
        tail = tail->prev;
        tail->next = nullptr;
    }

    temp->prev = nullptr;
    return temp;
}

    uint32_t get_max_prior() const { return max_prior; }

private:
    node* head;
    node* tail;
    uint32_t max_prior;
};

node* wrapper() 
{
    std::cout << "Enter info (string): ";
    std::string buffer;
    std::getline(std::cin, buffer);

    uint32_t prior;
    std::cout << "Enter prior (integer): ";
    if (!(std::cin >> prior)) 
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cerr << "Invalid input, please enter an integer for priority.\n";
        return nullptr;
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return new node(buffer, prior);
}

void delete_node(node* n)
{
    delete n;
}

void info_for_node(node* temp) 
{
    std::cout << "Info for node:\n";
    std::cout << "Data: " << temp->data << "\n";
    std::cout << "Priority: " << temp->priority << "\n";
}

void start() 
{
    priority_queue pr_q;

    while (true) 
    {
        std::cout << "Options:\n";
        std::cout << "1. Append\n";
        std::cout << "2. Pop\n";
        std::cout << "3. Print Queue\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";

        uint16_t choice;
        if (!(std::cin >> choice)) 
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << "Invalid choice, please enter a number from 1 to 4.\n";
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) 
        {
        case 1:
            while (true) 
            {
                std::cout << "Enter '~' to stop appending.\n";
                node* new_node = wrapper();
                if (!new_node) break;
                pr_q.append(new_node);
            }
            break;
        case 2:
            if (node* popped = pr_q.pop()) 
            
            {
                info_for_node(popped);
                delete_node(popped);
            }
            else 
            {
                std::cout << "Queue is empty.\n\n";
            }
            break;
        case 3:
            pr_q.printAll();
            break;
        case 4:
            std::cout << "Exiting...\n";
            return;
        default:
            std::cerr << "Invalid choice, please enter a number from 1 to 4.\n";
            break;
        }
    }
}

int main() 
{
    start();
    return 0;
}
