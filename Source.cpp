#pragma once
#include<iostream>
#include<iostream>
#include<fstream>
#include<string>

using namespace std;
class Teacher
{
private:

	int groups;
	int labs;
	string subject;
	int curLabs;
public:
	string fio;
	Teacher() : fio("-"), groups(0), labs(0), subject("-"), curLabs(0) {}
	Teacher(string f, int g, int l, string s, int cl) : fio(f), groups(g), labs(l), subject(s), curLabs(cl) {}
	void set_fio(string f)
	{
		fio = f;
	}
	void set_groups(int g)
	{
		groups = g;
	}
	void set_labs(int l)
	{
		labs = l;
	}
	void set_subject(string s)
	{
		subject = s;
	}
	void set_curLabs(int cl)
	{
		curLabs = cl;
	}
	string get_fio()
	{
		return fio;
	}
	int get_groups()
	{
		return groups;
	}
	int get_labs()
	{
		return labs;
	}
	string get_subject()
	{
		return subject;
	}
	int get_curLabs()
	{
		return curLabs;
	}

	friend ostream& operator<<(ostream& out, const Teacher t)
	{
		out << "\nFull name - " << t.fio << "\nNumber of groups - " << t.groups << "\nNumber of labs per subject - " << t.labs << "\nSubject - " << t.subject << "\nNumber of current labs - " << t.curLabs << endl;
		return out;
	}

	friend istream& operator>>(istream& in, Teacher& t)
	{
		in >> t.fio;
		in >> t.groups;
		in >> t.labs;
		in >> t.subject;
		return in;
	}

	friend bool operator==(Teacher t1, Teacher t2) {
		if (t1.labs - t1.curLabs == t2.labs - t2.curLabs)
			return true;
		else
			return false;
	}

	friend bool operator<(const Teacher t1, const Teacher t2)
	{
		if (t1.labs - t1.curLabs < t2.labs - t2.curLabs)
			return true;
		else
			return false;
	}

	friend bool operator>(const Teacher t1, const Teacher t2)
	{
		if (t1.labs - t1.curLabs > t2.labs - t2.curLabs)
			return true;
		else
			return false;
	}

};

using namespace std;
class Exception
{
};


class  Node
{
public:
	Teacher data;
	Node* next;
	Node() : data(), next(nullptr) { }

	Node(Teacher d) : data(d), next(nullptr) { }
};


class Ring
{
private:
	Node* head;
	int size;
public:

	Ring() :head(nullptr), size(0) {}

	void push(Teacher x)
	{
		if (head == nullptr)
		{
			Node* element = new Node(x);
			head = new Node(x);
			element->next = head;
			head = element;
			size++;
		}
		else
		{
			Node* tmp = head;
			int i = 0;
			while (i < size - 1)
			{
				tmp = tmp->next;
				i++;
			}
			tmp->next = new Node(x);
			tmp->next->next = head;
			size++;
		}
	}
	void pop()
	{
		if (size == 0)
			throw Exception();
		Node* tmp = head;
		head = head->next;
		delete tmp;
		size--;
		Node* t = head;
		int i = 0;
		while (i < size - 1)
		{
			t = t->next;
			i++;
		}
		t->next = head;
	}
	void output()
	{
		if (size == 0)
			throw Exception();
		Node* tmp = head;
		int i = 0;
		while (i < size)
		{
			cout << "   " << tmp->data;
			tmp = tmp->next;
			i++;
		}
	}
	Node* get_node()
	{
		return head;
	}
	int get_size()
	{
		return size;
	}
	friend ostream& operator<<(ostream& out, const Node& node)
	{
		out << node.data;
		return out;
	}
};


class Iterator
{
private:
	Node* node;
	int size;
	int current;
public:

	Iterator(Ring* element) : current(0)
	{
		node = element->get_node();
		size = element->get_size();
	}
	void begin()
	{
		if (size == 0)
			throw Exception();
		if (current != 0)
		{
			while (current < size)
			{
				current++;
				node = node->next;
			}
			current = 0;
		}

	}
	void search(Teacher x)
	{
		if (size == 0)
			throw Exception();
		int i = 0;
		while (i < size)
		{
			if (x == node->data)
			{
				cout << "\nElement\n " << x << "\nfound" << endl;
				return;
			}
			if (current == size - 1)
				current = 0;
			else
				current++;
			node = node->next;
			i++;
		}
		cout << "\nElement\n " << x << " \nnot found" << endl;
	}
	Iterator& operator++()
	{
		if (size == 0)
			throw Exception();
		if (size == 1)
			current = 0;
		else
			current++;
		node = node->next;
		return *this;
	}
	Teacher operator*() {
		return node->data;
	}
	void operator = (Teacher x)
	{
		if (size == 0)
			throw Exception();
		node->data = x;
	}
	Iterator& operator[](int index)
	{
		if (size == 0)
			throw Exception();
		Node* tmp = node;
		while (1)
		{
			if (current == index)
			{
				node = tmp;
				return *this;
			}
			tmp = tmp->next;
			if (current == size - 1)
				current = 0;
			else
				current++;
		}
	}
	void shell()
	{
		if (size == 0)
			throw Exception();
		int step, i, j;
		Teacher tmp;
		for (step = size / 2; step > 0; step /= 2)
			for (i = step; i < size; i++)
				for (j = i - step; j >= 0 && (*this)[j].node->data > (*this)[j + step].node->data; j -= step)
				{
					tmp = (*this)[j].node->data;
					(*this)[j].node->data = (*this)[j + step].node->data;
					(*this)[j + step].node->data = tmp;
				}
	}
	void sort_special()
	{
		if (size == 0)
			throw Exception();
		int step, i, j;
		Teacher tmp;
		for (step = size / 2; step > 0; step /= 2)
			for (i = step; i < size; i++)
			{
				for (j = i - step; j >= 0 && (*this)[j].node->data.get_subject() > (*this)[j + step].node->data.get_subject() &&
					(*this)[j].node->data.get_labs() - (*this)[j].node->data.get_curLabs() == (*this)[j + step].node->data.get_labs() - (*this)[j + step].node->data.get_curLabs(); j -= step)
				{
					tmp = (*this)[j].node->data;
					(*this)[j].node->data = (*this)[j + step].node->data;
					(*this)[j + step].node->data = tmp;
				}
			}

	}
	friend ostream& operator<<(ostream& out, const Iterator& it)
	{
		out << it.node;
		return out;
	}
};

enum Key { no = 0, txt, bin };

class File
{
private:
	fstream file;
	string name;
	Key key;
	int size;
public:
	File() : name("-"), key(no), size(0) {}
	File(string n, Key k) : name(n), key(k), size(0) {}
	friend File& operator<<(File& file, const char* s)
	{

		if (!file.file.is_open())
		{
			throw 1;
		}

		/*catch (int i)
		{
			Exception ex(i);
			ex.Print();
		}*/
		string str = s;
		file.file << str;
		return file;
	}
	friend fstream& operator<<(fstream& out, Teacher& t) {

		if (!out.is_open())
		{
			throw 1;
		}

		/*catch (int i)
		{
			Exception ex(i);
			ex.Print();
		}*/
		int a = out.tellg();
		string fio = t.get_fio();
		size_t len1 = fio.length() + 1;

		int groups = t.get_groups();
		int labs = t.get_labs();
		int curLabs = t.get_curLabs();

		string subject = t.get_subject();
		size_t len2 = subject.length() + 1;

		out.write((char*)(&len1), sizeof(len1));
		out.write((char*)(fio.c_str()), len1);

		out.write((char*)(&groups), sizeof(groups));
		out.write((char*)(&labs), sizeof(labs));

		out.write((char*)(&len2), sizeof(len2));
		out.write((char*)(subject.c_str()), len2);

		out.write((char*)(&curLabs), sizeof(curLabs));

		return out;
	}
	friend File& operator<<(File& file, Teacher& t)
	{
		int pos = 0, a = 0, size = 0;

		if (!file.file.is_open())
		{
			cout << "1";
		}

		/*catch (int i)
		{
			Exception ex(i);
			ex.Print();
		}*/
		if (file.key == txt) {
			file.file << t.get_fio() << " " << t.get_groups() << " " << t.get_labs() << " "
				<< t.get_subject() << " " << t.get_curLabs() << endl;
		}
		else if (file.key == bin) {
			string fio = t.get_fio();
			size_t len1 = fio.length() + 1;

			int groups = t.get_groups();
			int labs = t.get_labs();
			int curLabs = t.get_curLabs();

			string subject = t.get_subject();
			size_t len2 = subject.length() + 1;

			file.file.write((char*)(&len1), sizeof(len1));
			file.file.write((char*)(fio.c_str()), len1);

			file.file.write((char*)(&groups), sizeof(groups));
			file.file.write((char*)(&labs), sizeof(labs));

			file.file.write((char*)(&len2), sizeof(len2));
			file.file.write((char*)(subject.c_str()), len2);
			file.file.write((char*)(&curLabs), sizeof(curLabs));
		}
		return file;
	}
	friend ostream& operator<<(ostream& out, File& file)
	{
		int a = 0;

		if (!file.file.is_open())
		{
			throw 1;
		}

		/*catch (int i)
		{
			Exception ex(i);
			ex.Print();
		}*/
		if (file.key == txt) {
			string str;
			while (!file.file.eof()) {
				getline(file.file, str);
				a = file.file.tellg();
				cout << str << endl;
			}
		}
		else if (file.key == bin) {
			int i = 0;
			int size = 0, step = 0;
			/*Teacher tmp;*/
			while (i < file.size) {
				int labs = 0;
				int groups = 0;
				int curLabs = 0;

				size_t len = 0;

				file.file.read((char*)(&len), sizeof(len));
				char* f = new char[len];

				file.file.read((char*)(f), len);
				f[len - 1] = '\0';

				file.file.read((char*)(&groups), sizeof(int));
				file.file.read((char*)(&labs), sizeof(int));

				file.file.read((char*)(&len), sizeof(len));
				char* s = new char[len];

				file.file.read((char*)(s), len);
				s[len - 1] = '\0';

				file.file.read((char*)(&curLabs), sizeof(int));

				cout << f << " " << groups << " " << labs << " " << s << " " << curLabs << endl;

				delete[] f;
				delete[] s;
				i++;

			}
		}
		return out;
	}

	~File() { file.close(); }
	void open(string mode)
	{
		switch (key)
		{
		case txt: {
			if (mode == "r") {
				file.open(name, ios_base::in);   //äëÿ ââîäà
			}
			else if (mode == "add") {
				file.open(name, ios_base::app);  //çàïèñü â êîíåö ôàéëà
			}
			else if (mode == "w") {
				file.open(name, ios_base::out);  //äëÿ âûâîäà
			}
			else if (mode == "wr") {
				file.open(name, ios_base::in | ios_base::out); //äëÿ ââîäà è âûâîäà
			}
			break;
		}
		case bin: {
			if (mode == "r") {
				file.open(name, ios_base::binary | ios_base::in);    //äëÿ ââîäà
			}
			else if (mode == "add") {
				file.open(name, ios_base::binary | ios_base::app);   //çàïèñü â êîíåö ôàéëà
			}
			else if (mode == "w") {
				file.open(name, ios_base::binary | ios_base::out);   //äëÿ âûâîäà
			}
			else if (mode == "wr") {
				file.open(name, ios_base::binary | ios_base::in | ios_base::out);   //äëÿ ââîäà è âûâîäà
			}
			break;
		}

		}
		/*if (!file.is_open())
		{
			throw ;
		}
		*/
	}
	void close()
	{
		file.close();
	}
	void begin()
	{
		file.seekg(0, ios_base::beg);  //ïåðåìåùåíèå óêàçàòåëÿ ïîçèöèîíèðîâàíèÿ â íà÷àëî ôàéëà
	}
	void set_size(int s) {
		size = s;
	}
	int get_size() {
		return	size;
	}
	Teacher read()
	{
		string str;
		Teacher t;
		getline(this->file, str, ' ');
		t.set_fio(str);
		getline(this->file, str, ' ');
		t.set_groups(stoi(str));
		getline(this->file, str, ' ');
		t.set_labs(stoi(str));
		getline(this->file, str, ' ');
		t.set_subject(str);
		getline(this->file, str);
		t.set_curLabs(stoi(str));
		return t;
	}
	void edit(int line, Teacher mas[]) {
		this->open("wr");

		int a, b;

		/*try {
			if (!file.is_open())
			{
				throw 1;
			}
		}
		catch (int i)
		{
			Exception ex(i);
			ex.Print();
			return;
		}*/
		Teacher tmp;
		if (this->key == txt) {
			string str;
			for (int i = 0; i < line - 1; i++)
				getline(this->file, str);
			getline(this->file, str, ' ');
			tmp.set_fio(str);
			getline(this->file, str, ' ');
			tmp.set_groups(stoi(str));
			getline(this->file, str, ' ');
			tmp.set_labs(stoi(str));
			getline(this->file, str, ' ');
			tmp.set_subject(str);
			getline(this->file, str);
			tmp.set_curLabs(stoi(str));
		}
		else if (this->key == bin) {
			size_t len = 0;
			for (int i = 0; i < line; i++) {
				this->file.read((char*)(&len), sizeof(len));
				char* n = new char[len];
				string fio;
				string subject;
				int groups = 0, labs = 0, curLabs = 0;

				this->file.read((char*)(n), len);
				fio = n;
				fio[len - 1] = '\0';
				this->file.read((char*)(&groups), sizeof(int));
				this->file.read((char*)(&labs), sizeof(int));

				this->file.read((char*)(&len), sizeof(len));
				this->file.read((char*)(n), len);
				subject = n;
				subject[len - 1] = '\0';

				this->file.read((char*)(&curLabs), sizeof(int));

				tmp.set_fio(fio);
				tmp.set_groups(groups);
				tmp.set_labs(labs);
				tmp.set_subject(subject);
				tmp.set_curLabs(curLabs);
				delete[]n;
			}
			a = file.tellg();
		}

		cout << "What do you want to change?\n1 - fio\n2 - number of groups\n3 - number of labs per subject\n4 - subject\n5 - number of current labs" << endl;
		int choice;
		cin >> choice;
		cout << "Put new data: ";
		switch (choice) {
		case 1: {
			string a;
			rewind(stdin);
			cin >> a;
			tmp.set_fio(a);
			break;
		}
		case 2: {
			int a;
			cin >> a;
			tmp.set_groups(a);
			break;
		}
		case 3: {
			int a;
			cin >> a;
			tmp.set_labs(a);
			break;
		}
		case 4: {
			string a;
			rewind(stdin);
			cin >> a;
			tmp.set_subject(a);
			break;
		}
		case 5: {
			int a;
			cin >> a;
			tmp.set_curLabs(a);
			break;
		}
		}
		a = file.tellg();
		file.seekg(0, ios_base::end);
		b = file.tellg();
		this->file.seekg(0, ios_base::beg);
		if (this->key == txt) {
			string tmp;
			for (int i = 0; i < line - 1; i++)
				getline(this->file, tmp);
			int pos = this->file.tellg();
			this->file.seekg(pos, ios_base::beg);
			this->file << tmp;
			return;
		}
		else if (this->key == bin) {
			for (int i = 0; i < line - 1; i++)
			{
				size_t len = 0;
				this->file.read((char*)(&len), sizeof(len));
				char* n = new char[len];
				string fio;
				string subject;
				int groups = 0, labs = 0, curLabs = 0;

				this->file.read((char*)(n), len);
				fio = n;
				fio[len - 1] = '\0';
				this->file.read((char*)(&groups), sizeof(int));
				this->file.read((char*)(&labs), sizeof(int));

				this->file.read((char*)(&len), sizeof(len));
				//char* k = new char[len];
				this->file.read((char*)(n), len);
				/*subject = k;
				subject[len - 1] = '\0';*/

				this->file.read((char*)(&curLabs), sizeof(int));

				delete[] n;
				//delete[]k;
			}
			int pos = this->file.tellg();

			char* last = new char[b - a];
			this->file.read((char*)last, static_cast<std::streamsize>(b) - a);

			this->close();
			this->open("w");
			pos = this->file.tellg();

			for (int i = 0; i < get_size(); i++) {
				if (i != line - 1)
					file << mas[i];
				else {
					file << tmp;
					mas[i].set_fio(tmp.get_fio());
					mas[i].set_groups(tmp.get_groups());
					mas[i].set_labs(tmp.get_labs());
					mas[i].set_subject(tmp.get_subject());
					mas[i].set_curLabs(tmp.get_curLabs());
				}
			}
		}

		this->close();
	}

	void bouble_sort_fio()
	{
		string tmp;
		string s1, s2;
		int pos;
		this->open("wr");
		/*try {
			if (!file.is_open())
			{
				throw 1;
			}
		}
		catch (int i)
		{
			Exception ex(i);
			ex.Print();
			return;
		}*/
		for (int i = 0; i < this->size - 1; i++) {
			for (int j = 0; j < this->size - i - 1; j++)
			{
				this->file.seekg(0, ios_base::beg);
				for (int k = 0; k < j; k++)
					getline(this->file, s1);
				getline(this->file, s1, ' ');
				getline(this->file, s2);
				getline(this->file, s2, ' ');
				if (s1 > s2)
				{
					this->file.seekg(0, ios_base::beg);
					pos = this->file.tellg();
					for (int k = 0; k <= j; k++)
					{
						getline(this->file, s1);
						pos = this->file.tellg();
					}
					tmp = s1;
					getline(this->file, s2);
					this->file.seekg(0, ios_base::beg);
					for (int k = 0; k < j; k++)
					{
						getline(this->file, s1);
					}
					pos = this->file.tellg();
					this->file.seekg(pos, ios_base::beg);
					this->file << s2 << '\n';
					this->file << tmp << '\n';
				}
			}
		}
		this->close();
	}
	void bouble_sort_groups() {
		string tmp;
		string s1, s2;
		int i1, i2;
		int pos;
		this->open("wr");
		/*try {
			if (!file.is_open())
			{
				throw 1;
			}
		}
		catch (int i)
		{
			Exception ex(i);
			ex.Print();
			return;
		}*/
		for (int i = 0; i < this->size - 1; i++) {
			for (int j = 0; j < this->size - i - 1; j++)
			{
				this->file.seekg(0, ios_base::beg);
				for (int k = 0; k < j; k++)
					getline(this->file, s1);
				for (int t = 0; t < 2; t++)
					getline(this->file, s1, ' ');
				getline(this->file, s2);
				for (int t = 0; t < 2; t++)
					getline(this->file, s2, ' ');
				i1 = stoi(s1);
				i2 = stoi(s2);
				if (i1 > i2)
				{
					this->file.seekg(0, ios_base::beg);
					pos = this->file.tellg();
					for (int k = 0; k <= j; k++) {
						getline(this->file, s1);
						pos = this->file.tellg();
					}
					tmp = s1;
					getline(this->file, s2);
					this->file.seekg(0, ios_base::beg);
					for (int k = 0; k < j; k++) {
						getline(this->file, s1);
					}
					pos = this->file.tellg();
					this->file.seekg(pos, ios_base::beg);
					this->file << s2 << '\n';
					this->file << tmp << '\n';
				}
			}
		}
		this->close();
	}
	void bouble_sort_labs() {
		string tmp;
		string s1, s2;
		int i1, i2;
		int pos;
		this->open("wr");
		/*try {
			if (!file.is_open())
			{
				throw 1;
			}
		}
		catch (int i)
		{
			Exception ex(i);
			ex.Print();
			return;
		}*/
		for (int i = 0; i < this->size - 1; i++) {
			for (int j = 0; j < this->size - i - 1; j++) {
				this->file.seekg(0, ios_base::beg);
				for (int k = 0; k < j; k++) {
					getline(this->file, s1);
				}
				for (int t = 0; t < 3; t++)
					getline(this->file, s1, ' ');
				getline(this->file, s2);
				for (int t = 0; t < 3; t++)
					getline(this->file, s2, ' ');
				i1 = stoi(s1);
				i2 = stoi(s2);
				if (i1 > i2) {
					this->file.seekg(0, ios_base::beg);
					pos = this->file.tellg();
					for (int k = 0; k <= j; k++) {
						getline(this->file, s1);
						pos = this->file.tellg();
					}
					tmp = s1;
					getline(this->file, s2);
					this->file.seekg(0, ios_base::beg);
					for (int k = 0; k < j; k++) {
						getline(this->file, s1);
					}
					pos = this->file.tellg();
					this->file.seekg(pos, ios_base::beg);
					this->file << s2 << '\n';
					this->file << tmp << '\n';
				}
			}
		}
		this->close();
	}
	void bouble_sort_subject()
	{
		string tmp;
		string s1, s2;
		int pos;
		this->open("wr");
		/*try {
			if (!file.is_open())
			{
				throw 1;
			}
		}
		catch (int i)
		{
			Exception ex(i);
			ex.Print();
			return;
		}*/
		for (int i = 0; i < this->size - 1; i++) {
			for (int j = 0; j < this->size - i - 1; j++)
			{
				this->file.seekg(0, ios_base::beg);
				for (int k = 0; k < j; k++)
					getline(this->file, s1);
				for (int t = 0; t < 4; t++)
					getline(this->file, s1, ' ');
				getline(this->file, s2);
				for (int t = 0; t < 4; t++)
					getline(this->file, s2, ' ');
				if (s1 > s2)
				{
					this->file.seekg(0, ios_base::beg);
					pos = this->file.tellg();
					for (int k = 0; k <= j; k++)
					{
						getline(this->file, s1);
						pos = this->file.tellg();
					}
					tmp = s1;
					getline(this->file, s2);
					this->file.seekg(0, ios_base::beg);
					for (int k = 0; k < j; k++)
					{
						getline(this->file, s1);
					}
					pos = this->file.tellg();
					this->file.seekg(pos, ios_base::beg);
					this->file << s2 << '\n';
					this->file << tmp << '\n';
				}
			}
		}
		this->close();
	}
	void bouble_sort_curLabs() {
		string tmp;
		string s1, s2;
		int i1, i2;
		int pos;
		this->open("wr");
		/*try {
			if (!file.is_open())
			{
				throw 1;
			}
		}
		catch (int i)
		{
			Exception ex(i);
			ex.Print();
			return;
		}*/
		for (int i = 0; i < this->size - 1; i++) {
			for (int j = 0; j < this->size - i - 1; j++) {
				this->file.seekg(0, ios_base::beg);
				for (int k = 0; k < j; k++) {
					getline(this->file, s1);
				}
				for (int t = 0; t < 4; t++)
					getline(this->file, s1, ' ');
				getline(this->file, s1);
				//getline(this->file, s2);
				for (int t = 0; t < 4; t++)
					getline(this->file, s2, ' ');
				getline(this->file, s2);
				i1 = stoi(s1);
				i2 = stoi(s2);
				if (i1 > i2) {
					this->file.seekg(0, ios_base::beg);
					pos = this->file.tellg();
					for (int k = 0; k <= j; k++) {
						getline(this->file, s1);
						pos = this->file.tellg();
					}
					tmp = s1;
					getline(this->file, s2);
					this->file.seekg(0, ios_base::beg);
					for (int k = 0; k < j; k++) {
						getline(this->file, s1);
					}
					pos = this->file.tellg();
					this->file.seekg(pos, ios_base::beg);
					this->file << s2 << '\n';
					this->file << tmp << '\n';
				}
			}
		}
		this->close();
	}
};


using namespace std;
int main()
{
	Teacher t1("Alexandra_Sergeevna_Sidorovich", 4, 10, "OAIP", 6);
	Teacher t2("Sergey_Valentinovich_Batyukov", 3, 4, "TEC", 3);
	Teacher t3("Iuliia_Yurievna_Zheltko", 2, 9, "KPiAP", 7);
	Teacher t4("Konstantin_Igorevich_Davydovich", 3, 12, "BZH", 8);
	Teacher t5("Svetlana_Sergeevna_Stoma", 4, 4, "EP", 3);
	Teacher un[5] = { t1,t2,t3,t4,t5 };
	cout << "\n-------TXT in TXT mode-------\n";
	File f1("1.txt", txt);
	f1.open("w");
	f1.set_size(5);
	f1 << t1;
	f1 << t2;
	f1 << t3;
	f1 << t4;
	f1 << t5;
	f1.close();
	f1.open("r");
	cout << f1;
	f1.close();
	cout << "\n--------------------------------------------------------";
	cout << "\n-------TXT in BIN mode-------\n";
	File f2("2.txt", bin);
	f2.open("w");
	f2.set_size(5);
	f2 << t1;
	f2 << t2;
	f2 << t3;
	f2 << t4;
	f2 << t5;
	f2.close();
	f2.open("r");
	cout << f2;
	f2.close();
	cout << "\n--------------------------------------------------------";
	cout << "\n-------BIN in BIN mode-------\n";
	File f3("3.bin", bin);
	f3.open("w");
	f3.set_size(5);
	f3 << t1;
	f3 << t2;
	f3 << t3;
	f3 << t4;
	f3 << t5;
	f3.close();
	f3.open("r");
	cout << f3;
	f3.close();
	cout << "\n--------------------------------------------------------\n";

	int i = 0, line = 0;
	do {
		cout << "Enter the line that you want to change:" << endl;
		cin >> line;
		f2.edit(line, un);
		f2.open("r");
		cout << "\n--------------------------------------------------------\n";
		//cout << f2;
		f2.close();
		cout << "Do you want to change anything else?\n1 - yes\n0 - no" << endl;
		rewind(stdin);
		cin >> i;
	} while (i);
	cout << "\n--------------------------------------------------------\n";
	cout << "Sort by fio:" << endl;
	cout << "\n--------------------------------------------------------\n";
	f1.bouble_sort_fio();
	f1.open("r");
	cout << f1;
	f1.close();
	cout << "\n--------------------------------------------------------\n";
	cout << "Sort by number of groups:" << endl;
	cout << "\n--------------------------------------------------------\n";
	f1.bouble_sort_groups();
	f1.open("r");
	cout << f1;
	f1.close();
	cout << "\n--------------------------------------------------------\n";
	cout << "Sort by number of labs:" << endl;
	cout << "\n--------------------------------------------------------\n";
	f1.bouble_sort_labs();
	f1.open("r");
	cout << f1;
	f1.close();
	cout << "\n--------------------------------------------------------\n";
	cout << "Sort by subject:" << endl;
	cout << "\n--------------------------------------------------------\n";
	f1.bouble_sort_subject();
	f1.open("r");
	cout << f1;
	f1.close();
	cout << "\n--------------------------------------------------------\n";
	cout << "Sort by number of current labs:" << endl;
	cout << "\n--------------------------------------------------------\n";
	f1.bouble_sort_curLabs();
	f1.open("r");
	cout << f1;
	f1.close();

	Ring r;
	f1.open("r");
	Teacher t;
	for (int i = 0; i < f1.get_size(); i++)
	{
		t = f1.read();
		r.push(t);
	}
	r.output();
	Iterator I(&r);
	I.shell();
	cout << "\n--------------------------------------------------------\n";
	cout << "\nAfter sorting by the number of NON-issued labs\n";
	cout << "\n--------------------------------------------------------\n";
	r.output();
	cout << "\n--------------------------------------------------------\n";
	cout << "\nAfter sorting subjects in alphabetical order depending on the number of NON-issued labs\n";
	cout << "\n--------------------------------------------------------\n";
	I.sort_special();
	r.output();
}