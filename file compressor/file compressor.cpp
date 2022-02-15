#include <iostream>
#include <fstream>      // std::ifstream
using namespace std;

class snode
{
public:
	int f;
	char s[256], code[256];
	snode* le = NULL, * ri = NULL;
};
class node
{
public:
	int f;
	char s[256];
	snode* ro = NULL;
	node* next = NULL;
};
class node2
{
public:
	char s;
	char code[256];
	node2* next;
};
class list2
{
public:
	node2* head;
	node2* tail;
	list2()
	{
		head = NULL;
		tail = NULL;
	}

	void attach(node2* pnn)
	{
		if (head == NULL)
		{
			head = pnn;
			tail = pnn;
		}
		else
		{
			tail[0].next = pnn;
			tail = pnn;
		}
	}
};
class list
{
public:
	node* head;
	node* tail;
	list()
	{
		head = NULL;
		tail = NULL;
	}
	~list()
	{
		node* pt;
		while (head != NULL)
		{
			pt = head;
			head = head[0].next;

		}
	}
	void attach(node* pnn)
	{
		if (head == NULL)
		{
			head = pnn;
			tail = pnn;
		}
		else
		{
			tail[0].next = pnn;
			tail = pnn;
		}
	}
	void insert(node* pnn)
	{
		if (head == NULL)
		{
			head = pnn;
			tail = pnn;
		}
		else
		{
			int fa = 0;
			node* pb = NULL, * pt = head;
			while (pt != NULL)
			{
				if (pt->f > pnn->f)
				{
					if (head == pt)
					{
						head = pnn;
						pnn->next = pt;
					}
					else
					{
						pb->next = pnn;
						pnn->next = pt;
					}


					fa = 1;
					break;


				}
				pb = pt;
				pt = pt->next;
			}
			if (!fa)
			{
				pb->next = pnn;
				tail = pnn;
			}
		}
	}
};
void d(snode* pt, snode* pb, char f, list2& l2, int& ct)
{
	if (pt == NULL)
		return;

	int i = 0;
	if (f != NULL)
	{

		for (i = 0; pb->code[i] != NULL; i++)
		{
			pt->code[i] = pb->code[i];
		}
		pt->code[i] = f;
		pt->code[i + 1] = NULL;
	}
	else
	{
		pt->code[i] = f;
		pt->code[i + 1] = NULL;
	}
	d(pt->le, pt, '0', l2, ct);

	if (pt->ri == NULL && pt->le == NULL)
	{
		ct++;
		int k;
		node2* pnn = new node2;
		//cout << pt->s[0] << endl;
		pnn->s = pt->s[0];
		for (k = 0; pt->code[k] != NULL; k++)
		{
			//cout << pt->code[k];
			pnn->code[k] = pt->code[k];
		}
		pnn->code[k] = NULL;
		pnn->next = NULL;
		l2.attach(pnn);
		//cout << endl;
	}
	d(pt->ri, pt, '1', l2, ct);

}


void main()
{

	ofstream   fl2("Debug\\CompresedTestCase.txt", ofstream::binary);
	ifstream   fl("Debug\\TestCase.bmp", ifstream::binary);
	list l;
	int i, ct = 0, N;
	char x[400000], y[400000];
	fl.seekg(0, fl.end);//make ct =0
	N = fl.tellg(); //N=the ct
	//cout << N << endl;
	fl.seekg(0, fl.beg);
	int k = 0;
	char ch;
	for (i = 0; i < N; i++)
	{
		fl.read(&ch, 1);
		x[k] = ch;
		k++;
	}

	node* pnn = new node;
	for (i = 0; i < N; i++)
	{
		y[i] = x[i];
	}
	//know the F
	ct = 1;
	for (int k = 0 + 1; k < N; k++)
	{
		if (x[k] == x[0])
		{
			ct++;
		}
	}
	pnn->s[0] = x[0];
	pnn->s[1] = NULL;
	pnn->f = ct;
	pnn->next = NULL;
	l.insert(pnn);
	snode* ri, * le, * ro;
	for (i = 1; i < N; i++)
	{
		int ct = 1;
		if (y[i] != x[0])
		{
			for (int k = i + 1; k < N; k++)
			{
				if (y[k] == y[i])
				{
					ct++;
					y[k] = x[0];
				}
			}
			pnn = new node;
			pnn->s[0] = y[i];
			pnn->f = ct;
			pnn->next = NULL;
			l.insert(pnn);
		}
	}


	//make the tree
	node* pt, * pt2 = NULL;
	for (pt = l.head; pt->next != NULL; pt = l.head)
	{
		pt2 = pt->next;
		l.head = pt2->next;
		ro = new snode;
		pnn = new node;
		for (i = 0; pt->s[i] != NULL; i++)
		{
			ro->s[i] = pt->s[i];
			pnn->s[i] = pt->s[i];
		}
		for (int k = 0; pt2->s[k] != NULL; k++)
		{
			ro->s[i] = pt2->s[k];
			pnn->s[i] = pt2->s[k];
			i++;
		}
		ro->s[i] = NULL;
		pnn->s[i] = NULL;


		pnn->f = pt2->f + pt->f;
		ro->f = pnn->f;

		if (pt->ro == NULL)
		{
			le = new snode;
			le->f = pt->f;
			le->s[0] = pt->s[0];
			ro->le = le;
			delete pt;
		}
		else
		{
			ro->le = pt->ro;
		}
		if (pt2->ro == NULL)
		{
			ri = new snode;
			ri->f = pt2->f;
			ri->s[0] = pt2->s[0];
			ro->ri = ri;
			delete pt2;
		}
		else
		{
			ro->ri = pt2->ro;
		}
		pnn->ro = ro;
		l.insert(pnn);
	}
	list2 l2;
	node2* pt22;
	ct = 0;
	d(l.head->ro, NULL, NULL, l2, ct);


	//phase 2
	for (pt22 = l2.head; pt22 != NULL; pt22 = pt22->next)
	{
		char q = pt22->s;
		fl2.write(&q, 1);
		for (i = 0; pt22->code[i] != NULL; i++)
		{
			q = pt22->code[i];
			fl2.write(&q, 1);
		}
		q = '.';
		fl2.write(&q, 1);
	}
	char q = '.';
	fl2.write(&q, 1);
	q = '.';
	fl2.write(&q, 1);
	q = '.';
	fl2.write(&q, 1);
	//phase 2 start here


	int ib = 7, m = 0, ib2;
	unsigned char t = 0, mask = 1, r, c[200000], r2;
	for (i = 0; i < N; i++)
	{
		//search to the code
		for (pt22 = l2.head; ; pt22 = pt22->next)
		{
			if (x[i] == pt22->s)
			{
				break;
			}
		}
		for (k = 0; pt22->code[k] != NULL; k++)
		{
			if (pt22->code[k] == '1')
			{
				t = t | (mask << ib);
				mask = 1;

			}
			ib--;
			if (ib == -1)
			{
				ib = 7;
				//cout << t << endl;
				c[m] = t;
				c[m + 1] = NULL;
				t = 0;
				m++;
			}
		}
	}

	if (ib != -1)
	{
		//cout << t << endl;
		c[m] = t;
		c[m + 1] = NULL;
	}
	ib2 = ib;

	char ib22 = ib2 + 48;
	fl2.write(&ib22, 1);
	char un;

	for (i = 0; i < m + 1; i++)
	{
		un = c[i];
		fl2.write(&un, 1);
	}
	unsigned char a = un;
	cout << "Done";

}