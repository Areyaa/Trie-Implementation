// Nicolae Alina-Elena, 311 CA

#ifndef __NODE__H
#define __NODE__H


/* nodurile din treap vor fi de tip Node: formate din cuvantul reprezentativ
si numarul de aparitii ale acestuia */
class Node
{
	public:
	
		long int aparitii;
		std :: string cuvant;
		
		Node ()
		{}
		
		~Node ()
		{}
	
		/* am supraincarcat operatorii ">, <, == si !=", pentru a se respecta
		regulile de inserare in treap */ 
		friend int operator > (const Node &a, const Node &b);
		friend int operator < (const Node &a, const Node &b);
		friend int operator == (const Node &a, const Node &b);
		friend int operator != (const Node &a, const Node &b);
};

/* nodul a este considerat mai mare decat nodul b atunci cand numarul de 
aparitii al lui a > numarul de aparitii al lui b; daca acestea sunt egale, 
se compara lexicografic */
int operator > (const Node &a, const Node &b)
{
	if (a.aparitii > b.aparitii)
	{
		return 1;
	}
	else
	{
		if (a.aparitii == b.aparitii)
		{
			if (a.cuvant < b.cuvant)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		
		return 0;
	}
}

int operator < (const Node &a, const Node &b)
{
	if (a.aparitii < b.aparitii)
	{
		return 1;
	}
	else
	{
		if (a.aparitii == b.aparitii)
		{
			if (a.cuvant > b.cuvant)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		return 0;
	}
}

/* nodurile a si b sunt considerate egale cand cuvintele, dar si numarul de 
aparitii ale fiecarui nod corespund */
int operator == (const Node &a, const Node &b)
{
	if (a.aparitii == b.aparitii && a.cuvant == b.cuvant)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int operator != (const Node &a, const Node &b)
{
	if (a.aparitii != b.aparitii && a.cuvant != b.cuvant)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

#endif // __NODE__H
