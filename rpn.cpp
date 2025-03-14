#include<iostream>

using namespace std;

class Stack {
    struct Node {
        union {
            char operation;
            int number;
        } data;
        bool isNumber;
        Node* next;
    };

public:
    Node* head;
    Stack() {
        head = nullptr;
    }

    ~Stack() {
        while (head != nullptr) {
            Node* n = head->next;
            head = n;
        }
    }

    void add(char value) {
        Node* n = new Node;
        n->data.operation = value;
        n->isNumber = false;
        n->next = head;
        head = n;
    }

    void add(int value) {
        Node* n = new Node;
        n->data.number = value;
        n->isNumber = true;
        n->next = head;
        head = n;
    }

    void remove() {
        if (head != nullptr)
        {
            Node* n = head->next;
            delete head;
            head = n;
        }
        else
        {
            return;
        }
    }

    const void print() const {
        Node* current = head;
        while (current != nullptr) {
            if (current->isNumber)
                cout << current->data.number << " ";
            else {
                if (current->data.operation == 'M') {
                    if (current->next->data.operation == 'A')
                        cout << "MAX";
                    else if (current->next->data.operation == 'I')
                        cout << "MIN";
                    current = current->next; // skip to the next element
                    current = current->next;
                }
                else if (current->data.operation == 'I')
                {
                    cout << "IF ";
                    current = current->next;
                }
                else
                {
                    cout << current->data.operation << " ";
                }
            }
            current = current->next;
        }
        cout << endl;
    }

    Stack reverseStack() {
        Stack reversed;
        while (head != nullptr)
        {
            if (head->isNumber)
            {
                reversed.add(head->data.number);
            }
            else
            {
                reversed.add(head->data.operation);
            }
            remove();
        }
        return reversed;
    }
};

int priority(char c)
{
    switch (c)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case 'N':
        return 3;
    default:
        return 0;
    }
}

void handleInput(char c, Stack & final, Stack& operators);

void handleBracket(Stack & final, Stack& operators)
{
    while (operators.head != nullptr && operators.head->data.operation != '(')
    {
        final.add(operators.head->data.operation);
        operators.remove();
    }
    operators.remove();
}

void handleOperator(char c, Stack & final, Stack& operators)
{
    while (operators.head != nullptr && priority(c) <= priority(operators.head->data.operation))
    {
        final.add(operators.head->data.operation);
        operators.remove();
    }
    operators.add(c);
}

void handleM(Stack & final)
{
    bool MAX = true; // function min or max?
    char c;
    Stack tmpStack;
    int arg = 1; // number of arguments min/max
    int tmp = 1;

    cin >> c; // loaded first character M 
    if (c == 'I')
    {
        MAX = false;
    }

    cin >> c >> c; // loaded M--(
    while (tmp)
    {
        cin >> c;
        if (c == '(')
        {
            tmp++;
        }
        else if (c == ')')
        {
            tmp--;
            if (tmp == 0) break;

        }
        if (c == ',')
        {
            while (tmpStack.head != nullptr)
            {
                final.add(tmpStack.head->data.operation); // delete all opeartors except those in argument
                tmpStack.remove();
            }
            arg++;
        }
        else
        {
            handleInput(c, final, tmpStack);
        }
    }
    while (tmpStack.head != nullptr)
    {
        final.add(tmpStack.head->data.operation);
        tmpStack.remove();
    }
    if (MAX)
    {
        final.add('M'); final.add('A'); final.add('X'); final.add(arg);
    }
    else
    {
        final.add('M'); final.add('I'); final.add('N'); final.add(arg);
    }
}

void handleIF(Stack & final)
{
    char c;
    Stack tmpStack;
    int tmp = 1;
    cin >> c >> c; // loaded IF(
    while (tmp)
    {
        cin >> c;
        if (c == '(')
        {
            tmp++;
        }
        else if (c == ')')
        {
            tmp--;
            if (tmp == 0) break;

        }
        if (c == ',')
        {
            while (tmpStack.head != nullptr)
            {
                final.add(tmpStack.head->data.operation); // delete all opeartors except those in argument
                tmpStack.remove();
            }
        }
        else
        {
            handleInput(c, final, tmpStack);
        }
    }
    while (tmpStack.head != nullptr)
    {
        final.add(tmpStack.head->data.operation);
        tmpStack.remove();
    }
    final.add('I'); final.add('F');
}

void handleN(Stack & final)
{
    char c;
    Stack tmpStack;
    cin >> c; // loaded first character after N
    if (c == '(')
    {
        tmpStack.add(c);
        int tmp = 1;
        while (tmp)
        {
            cin >> c;
            if (c == '(')
            {
                tmp++;
            }
            else if (c == ')')
            {
                tmp--;
                if (tmp == 0)
                {
                    handleInput(c, final, tmpStack);
                    break;
                }

            }
            handleInput(c, final, tmpStack);
        }
        while (tmpStack.head != nullptr)
        {
            final.add(tmpStack.head->data.operation);
            tmpStack.remove();
        }
        final.add('N');
    }
    else
    {
        handleInput(c, final, tmpStack);
        final.add('N');
    }
}

void handleInput(char c, Stack & final, Stack& operators)
{
    if (isdigit(c)) // input number
    {
        int num;
        cin.putback(c);
        cin >> num;
        final.add(num);
    }
    else if (c == '(')
    {
        operators.add(c);
    }
    else if (c == ')')
    {
        handleBracket(final, operators);
    }
    else if (c == '+' || c == '-' || c == '/' || c == '*')
    {
        handleOperator(c, final, operators);
    }
    else if (c == 'M')
    {
        handleM(final);
    }
    else if (c == 'I')
    {
        handleIF(final);
    }
    else if (c == 'N')
    {
        handleN(final);
    }
}

void notation(Stack* final, Stack* operators, int n)
{
    char c = ' ';
    int stacks_read = 0;
    while (stacks_read < n) {
        while (c != '.') {
            cin >> c;
            handleInput(c, final[stacks_read], operators[stacks_read]);
        }
        while (operators[stacks_read].head != nullptr)
        {
            final[stacks_read].add(operators[stacks_read].head->data.operation);
            operators[stacks_read].remove();
        }
        c = ' ';
        stacks_read++;
    }
}

void PLUS(Stack& result)
{
    cout << "+" << " ";
    result.print();
    int b = result.head->data.number;
    result.remove();
    int a = result.head->data.number;
    result.remove();
    result.add(a + b);
}

void MINUS(Stack& result)
{
    cout << "-" << " ";
    result.print();
    int b = result.head->data.number;
    result.remove();
    int a = result.head->data.number;
    result.remove();
    result.add(a - b);
}

void TIMES(Stack& result)
{
    cout << "*" << " ";
    result.print();
    int b = result.head->data.number;
    result.remove();
    int a = result.head->data.number;
    result.remove();
    result.add(a * b);
}

void DIVIDE(Stack& result, bool& error)
{
    cout << "/" << " ";
    result.print();
    int b = result.head->data.number;
    result.remove();
    int a = result.head->data.number;
    result.remove();
    if (b != 0)
    {
        result.add(a / b);
    }
    else
    {
        cout << "ERROR" << endl;
        error = true;
    }
}

void NEGATION(Stack& result)
{
    cout << "N" << " ";
    result.print();
    int a = result.head->data.number;
    result.remove();
    result.add(-a);
}

void MIN(Stack& result, int arg)
{
    cout << "MIN" << arg << " ";
    result.print();
    int min = result.head->data.number;
    result.remove();
    for (int i = 0; i < arg - 1; i++)
    {
        if (result.head->data.number < min)
        {
            min = result.head->data.number;
        }
        result.remove();
    }
    result.add(min);
}

void MAX(Stack& result, int arg)
{
    cout << "MAX" << arg << " ";
    result.print();
    int max = result.head->data.number;
    result.remove();
    for (int i = 0; i < arg - 1; i++)
    {
        if (result.head->data.number > max)
        {
            max = result.head->data.number;
        }
        result.remove();
    }
    result.add(max);
}

void IF(Stack& result)
{
    cout << "IF" << " ";
    result.print();
    int c = result.head->data.number;
    result.remove();
    int b = result.head->data.number;
    result.remove();
    int a = result.head->data.number;
    result.remove();
    if (a > 0)
    {
        result.add(b);
    }
    else
    {
        result.add(c);
    }
}

void calculation(Stack & final)
{
    Stack reversed = final.reverseStack();
    Stack result;
    reversed.print();
    bool error = false;

    while (reversed.head != nullptr)
    {
        if (reversed.head->isNumber)
        {
            result.add(reversed.head->data.number);
        }
        else
        {
            switch (reversed.head->data.operation)
            {
            case '+':
                PLUS(result);
                break;
            case '-':
                MINUS(result);
                break;
            case '*':
                TIMES(result);
                break;
            case '/':
                DIVIDE(result, error);
                if (error)
                {
                    return;
                }
                break;
            case 'N':
                NEGATION(result);
                break;
            case 'M':
                if (reversed.head->next->data.operation == 'I')
                {
                    reversed.remove();
                    reversed.remove();
                    int number = reversed.head->next->data.number;
                    reversed.remove();
                    MIN(result, number);
                }
                else
                {
                    reversed.remove();
                    reversed.remove();
                    int number = reversed.head->next->data.number;
                    reversed.remove();
                    MAX(result, number);
                }
                break;
            case 'I':
                IF(result);
                break;
            }
        }
        reversed.remove();
    }
    result.print();
}

int main()
{
    int n = 0;
    cin >> n;
    Stack* final = new Stack[n];
    Stack* operators = new Stack[n];
    notation(final, operators, n);
    cout << endl;
    for (int i = 0; i < n; i++)
    {
        calculation(final[i]);
        cout << endl;
    }
    delete[] final;
    delete[] operators;
    return 0;
}