// Nicolae Alina-Elena, 311 CA

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <math.h>
#include "trie.h"


int main (int argc, char *argv [])
{
	srand (time (0));
	
	std :: ifstream fin;
	std :: ofstream fout;
		
	fin.open ("date.in");

	fout.open ("date.out");
	
	Trie *mytrie = new Trie (); // se declara trie-ul
	
	long int n, m, y;
	unsigned int j;
	std :: string x;
	
	fin >> n; // n = numarul de cuvinte inserate

	for (long int i = 0 ; i < n ; i++)
	{
		fin >> x >> y; // x = cuvant, y = numar aparitii
		mytrie -> addword (mytrie, x, y); // se adauga cuvantul in trie
	}
	
	fin >> m; // m = numarul de cuvinte cautate

	for (long int i = 0 ; i < m ; i++)
	{
		fin >> x; // sirul de cifre pentru care se cere cuvantul corespondent
	
		int v [3] = {0}; // v = vector cu 3 elemente (informatii in README)
		/* ok ramane 0 cat timp nu se ajunge la caracterul '*' in parcurgerea 
		stringului x */
		int ok = 0;
	  	
	  	// se parcurge x pentru a retine lungimea sirului pana la '*'
	  	for (j = 1 ; j <= x.length () ; j++)
	  	{
	  		if (!ok)
	  		{
	  			v [0] ++;
	  		}
	  		
	  		if (x [j] == '*')
	  		{
	  			v [1] = 1;
	  			ok = 1;
	  			break;
	  		}
	  	}
	  	
	  	long int zece = 1;
	  	long int numar = 0; // va retine valoarea elementului de dupa '*'
	  	
	  	for (unsigned int k = j + 1 ; k < x.length () ; k++)
	  	{
	  		numar = numar * zece + (int) x [k] - 48; // cod ASCII - 48 = cifra
	  		zece = 10;
	  	}
	  	
	  	v [2] = numar; // mai multe detalii in README
	  	
	  	// se afiseaza cuvantul corespunzator cerintei in fisierul "date.out"
	  	fout << mytrie -> get (mytrie, x, v) << '\n'; 
	}
	
	delete mytrie; // se elibereaza memoria alocata
	
	fin.close ();
	fout.close ();
	
	return 0;		
}
