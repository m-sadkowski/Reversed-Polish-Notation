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
		while (current != nullptr) {
			if (current->isNumber)
				cout << current->data.number << " ";
			else
				cout << current->data.operation << " ";
			current = current->next;
		}
	}

	void printReverse() {
		Node* current = head;
		Node* prev = nullptr;
		Node* next = nullptr;

		// Przechodzenie na koniec stosu
		while (current != nullptr) {
			next = current->next;
			current->next = prev;
			prev = current;
			current = next;
		}

		// Przechodzenie po odwróconym stosie i wypisywanie elementów
		while (prev != nullptr) {
			if (prev->isNumber)
				cout << prev->data.number << " ";
			else
				cout << prev->data.operation << " ";
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
		// ------------------------------------------------------------DO ZMIAN
		cin >> c;
		int which = 0;
		if (c == 'A')
		{
			which = 1;
		}
		else if (c == 'I')
		{
			which = 2;
		}
		cin >> c >> c;
		//while input different than ')' tmp++, push numbers to final
		int x = 0;
		while (c != ')') {
			if (isdigit(c)) {
				int num;
				cin.putback(c);
				cin >> num;
				final[tmp].add(num);
				x++;
			}
			else if (c != ',')
			{
				handleOperator(c, final, operators, tmp);
				x++;
			}
			cin >> c;
		}
		if (which == 1)
		{
			final[tmp].add('M');
			final[tmp].add('A');
			final[tmp].add('X');
		}
		if (which == 2)
		{
			final[tmp].add('M');
			final[tmp].add('I');
			final[tmp].add('N');
		}
		final[tmp].add(x);

		// ------------------------------------------------------------DO ZMIAN
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
		//pull from stack all operators with higher or equal(not less important) priorities and write to final
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
		final[i].printReverse();
		cout << endl;
	}
	return 0;
}
