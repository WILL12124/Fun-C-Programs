#include <stdio.h>

typedef struct linkedList_practice
{
    float GPA;
    char grade;
    char name[20];
    struct linkedList_practice *next;
} LInk;

int main(int argc, char const *argv[])
{
    LInk student1 = {3.88, 'A', "William", NULL}; // LInk 为变量名称！！，还未declare
    student1.GPA = 3.92;
    printf("%.2f", student1.GPA);
    return 0;
}

/*Node *search(Node *head, int key)
{
    Node *current = head;
    // insert your code in the line below between the parentheses
    while ()
    {
        current = current->link;
    }
    return current;
}*/