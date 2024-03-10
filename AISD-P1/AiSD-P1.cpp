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
			delete head;
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
		Node* n = head->next;
		delete head;
		head = n;
	}

	void print() {
		Node* current = head;
		Node* prev = nullptr;
		Node* next = nullptr;

		// go to the end of the stack
		while (current != nullptr) {
			next = current->next;
			current->next = prev;
			prev = current;
			current = next;
		}

		// go back to the beginning and print
		while (prev != nullptr) {
			if (prev->isNumber)
				cout << prev->data.number << " ";
			else
				// when operator is M, we need to print it as MAX or MIN
				if (prev->data.operation == 'M')
				{
					if (prev->next->data.operation == 'A')
					{
						cout << "MAX";
					}
					else if (prev->next->data.operation == 'I')
					{
						cout << "MIN";
					}
					prev = prev->next;
					prev = prev->next;
				}
				else
				{
					cout << prev->data.operation << " ";
				}
			prev = prev->next;
		}
	}
};

int priority(char c) {
	switch (c) {
		case '(':
			return 0;
		case '+':
		case '-':
			return 1;
		case '*':
		case '/':
			return 2;
		case 'M':
		case 'N':
		case 'I':
			return 3;
	}
	return -1;
}

void handleOperator(char c, Stack* final, Stack* operators, int& tmp);

void handleFunctionM(char c, Stack* final, Stack* operators, int& tmp)
{
	cin >> c;
	int which = 0;
	if (c == 'A')
		which = 1;
	else
		which = 2;
	cin >> c >> c >> c;
	Stack operatorStack;
	//while input is operand or operator different than ')' x++, push numbers to final and operators to stack
	int x = 1; // number of numbers in min/max function
	while (c != ')') 
	{
		if (isdigit(c)) 
		{
			int num;
			cin.putback(c);
			cin >> num;
			final[tmp].add(num);
		}
		else if (c == ',')
		{
			while (operatorStack.head != nullptr)
			{
				final[tmp].add(operatorStack.head->data.operation);
				operatorStack.remove();
			}
			x++;
		}
		else
		{
			handleOperator(c, final, &operatorStack, tmp);
		}
		cin >> c;
	}
	if (which == 1)
	{
		final[tmp].add('M'); final[tmp].add('A'); final[tmp].add('X');
	}
	else
	{
		final[tmp].add('M'); final[tmp].add('I'); final[tmp].add('N');
	}
	final[tmp].add(x);
	cout << "I 'm here\n";
}

void handleOperator(char c, Stack* final, Stack* operators, int& tmp)
{
	if (c == '(')
	{
		operators[tmp].add(c);
	}
	else if (c == ')')
	{
		while (operators[tmp].head->data.operation != '(') {
			final[tmp].add(operators[tmp].head->data.operation);
			operators[tmp].remove();
		}
		operators[tmp].remove();
	}
	else  if (c == 'M')
	{  
		handleFunctionM(c, final, operators, tmp);
	}
	else if (c == 'I')
	{
		cin >> c;
		// OBSŁUGA IF
	}
	else if (c == 'N')
	{
		while (operators[tmp].head != nullptr && priority(operators[tmp].head->data.operation) > priority(c)) {
			final[tmp].add(operators[tmp].head->data.operation);
			operators[tmp].remove();
		}
		operators[tmp].add(c);
	}
	else if (c == '/' || c == '*' || c == '-' || c == '+')
	{
		//pull from stack all operators with higher or equal priorities and write to final
		while (operators[tmp].head != nullptr && priority(operators[tmp].head->data.operation) >= priority(c)) {
			final[tmp].add(operators[tmp].head->data.operation);
			operators[tmp].remove();
		}
		operators[tmp].add(c);
	}
}

void handleInput(int n, Stack* final, Stack* operators) 
{
	char c;
	int tmp = 0;
	while (tmp != n)
	{
		cin >> c;
		if (isdigit(c)) // input number
		{
			int num;
			cin.putback(c);
			cin >> num;
			final[tmp].add(num);
		}
		else if (c == '.') // end of expression
		{
			while (operators[tmp].head != nullptr)
			{
				final[tmp].add(operators[tmp].head->data.operation);
				operators[tmp].remove();
			}
			tmp++;
		}
		else
		{
			handleOperator(c, final, operators, tmp); // input operator
		}
	}
}

int main()
{
	int n = 0;
	cin >> n;
	Stack* final = new Stack[n]; 
	Stack* operators = new Stack[n];
	handleInput(n, final, operators);
	for (int i = 0; i < n; i++)
	{
		final[i].print();
		cout << endl;
	}
	delete[] final;
	delete[] operators;
	return 0;
}
