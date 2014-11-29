#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

struct string_node{
    const char *str;
    string_node *next;
};

string_node *msd_sort(string_node *list_p, int digit )
{

    const int range = 256;

    string_node *buckets[range];
    memset(buckets, 0, sizeof(buckets) );

    string_node **next_item_pp[range];
    for (int i = 0; i < range; i++)
        next_item_pp[i] = &buckets[i];

    while (list_p)
    {
        string_node* temp = list_p;
        list_p = list_p->next;

        temp->next = NULL;

        char c = (char)temp->str[digit];
        *next_item_pp[c]=temp;
        next_item_pp[c]=&temp->next;
    }

    string_node* result_p = NULL;
    string_node** next_pp = &result_p;

    *next_pp = buckets[0];
    while (*next_pp)
        next_pp = &((*next_pp)->next);

    for (int i = 1; i < range; ++i)
    {
        if (!buckets[i])
            continue;
        if (buckets[i]->next == NULL)
            *next_pp = buckets[i];
        else
            *next_pp = msd_sort(buckets[i], digit + 1);

        while (*next_pp)
            next_pp = &((*next_pp)->next);
    }
    return result_p;
}

int main()
{
    vector<string> strs;
    string str;

    for(;;) {
        cin >> str;
        if (cin.eof()) break;
        strs.push_back(str);
    }

    string_node* list_p = NULL;
    string_node** curr_pp = &list_p;
    for (int i=0 ; i<strs.size(); i++) {
        *curr_pp = new string_node();
        (*curr_pp)->str = strs[i].c_str();
        (*curr_pp)->next = NULL;
        curr_pp = &(*curr_pp)->next;
    }

    list_p = msd_sort(list_p, 0);

    while(list_p)
    {
        cout << list_p->str << endl;
        string_node* tmp = list_p;
        list_p = list_p->next;
        delete tmp;
    }
    return 0;
}