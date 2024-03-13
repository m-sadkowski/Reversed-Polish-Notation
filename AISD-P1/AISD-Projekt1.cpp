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
				else if (prev->data.operation == 'I')
				{
					cout << "IF ";
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
	default:
		return 0;
	}
}

void handleInput(char c, Stack& final, Stack& operators);

void handleBracket(Stack& final, Stack& operators)
{
	while (operators.head->data.operation != '(' && operators.head != nullptr)
	{
		final.add(operators.head->data.operation);
		operators.remove();
	}
	operators.remove();
}

void handleOperator(char c, Stack& final, Stack& operators)
{
	while (operators.head != nullptr && priority(c) <= priority(operators.head->data.operation))
	{
		final.add(operators.head->data.operation);
		operators.remove();
	}
	operators.add(c);
}

void handleM(Stack& final, Stack& operators)
{
	bool MAX = true; // funkcja min czy max?
	char c;
	Stack tmpStack;
	int arg = 1; // liczba argumentĂłw funkcji min/max
	int tmp = 1;

	cin >> c; // wczytano pierwszy znak po M 
	if (c == 'I')
	{
		MAX = false;
	}

	cin >> c >> c; // wczytano M--(
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
				final.add(tmpStack.head->data.operation); // WYRZUÄ† WSZYSTKIE OPERATORY OPRĂ“CZ TYCH KTĂ“RE OTRZYMAĹEĹš W ARGUMENCIE
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
	tmpStack.~tmpStack();
	if (MAX)
	{
		final.add('M'); final.add('A'); final.add('X'); final.add(arg);
	}
	else
	{
		final.add('M'); final.add('I'); final.add('N'); final.add(arg);
	}
}

void handleIF(Stack & final, Stack& operators)
{
	char c;
	Stack tmpStack;
	int tmp = 1;
	cin >> c >> c; // wczytano pierwszy znak po IF(
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
			if(tmp == 0) break;
			
		}
		if (c == ',')
		{
			while (tmpStack.head != nullptr)
			{
				final.add(tmpStack.head->data.operation); // WYRZUÄ† WSZYSTKIE OPERATORY OPRĂ“CZ TYCH KTĂ“RE OTRZYMAĹEĹš W ARGUMENCIE
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
	tmpStack.~tmpStack();
	final.add('I'); final.add('F');
}

/*TO DO */ void handleN(Stack & final, Stack& operators)
{
	char c;
	Stack tmpStack;
	int tmp = 1;
	cin >> c; // wczytano pierwszy znak po N
	if (c == '(')
	{
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
	}
	else
	{
		handleInput(c, final, tmpStack);
	}
	tmpStack.~tmpStack();
	operators.add('N');
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
		handleM(final, operators);
	}
	else if (c == 'I')
	{
		handleIF(final, operators);
	}
	else if (c == 'N')
	{
		handleN(final, operators);
	}
}

void notation(Stack* final, Stack* operators, int n)
{
	char c = ' ';
	for (int i = 0; i < n; i++)
	{
		while (c != '.')
		{
			cin >> c;
			handleInput(c, final[i], operators[i]);
		}
		if (c == '.')
		{
			while (operators[i].head != nullptr)
			{
				final[i].add(operators[i].head->data.operation);
				operators[i].remove();
			}
		}
	}
}

int main()
{
	int n = 0;
	cin >> n;
	Stack* final = new Stack[n];
	Stack* operators = new Stack[n];
	notation(final, operators, n);
	for (int i = 0; i < n; i++)
	{
		final[i].print();
		cout << endl;
	}
	return 0;
}

// N TO FIX