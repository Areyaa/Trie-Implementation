// Nicolae Alina-Elena, 311 CA

#ifndef __TRIE__H
#define __TRIE__H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include "treap.h"
#include "node.h"
#include "string_cod.h"


/* clasa Trie contine implementarea structurii de date trie in care se retin
toate cuvintele din fisierul "date.in" */
class Trie
{
	private:
	
	// vector = vector de 8 pointeri de tip Trie care reprezinta cele 8 taste
		Trie *vector [8];
	/* treap = un pointer de tip Treap cu elemente de tip Node care pointeaza
	la inceputul treap-ului fiecarui pointer de tip trie din vector */
		Treap <Node> *treap;

	public:
	
		Trie ()
		{
			treap = new Treap <Node> ();
			
			for (int i = 0 ; i <= 7 ; i++)
			{
				vector [i] = NULL;
			}
		}
		
		~Trie ()
		{
			if (treap)
			{
				delete treap;
			}
			
			for (int i = 0 ; i <= 7 ; i++)
			{
                if (vector [i] != NULL)
                {
                	delete vector [i];
                }          
            }
		}
		
		// functia de inserare a cuvintelor in trie
		void addword (Trie *&fatherPointer, std :: string a, long int aparitie)
		{
			std :: string x;
			x = cod (a); // codul in cifre corespunzator stringului "a"
			int n = a.length (); // n = lungimea stringului
			
			Node nod; // se creeaza un nou nod, caruia i se atribuie valorile:
			nod.cuvant = a;
			nod.aparitii = aparitie;
			
			/* se retine nodul parinte din trie (cel initial) in variabila 
			"fallen" pentru a evita modificarea parintelui */
			Trie *fallen = fatherPointer;
		
			/* se parcurge stringul x pentru a naviga prin toate nodurile din
			trie corespunzatoare cifrelor ce-l alcatuiesc pe x */
			for (int i = 0 ; i < n ; i++)
			{
				int tasta = (int) x [i] - 48; // cifra = ASCII - 48
				
				/* daca nu exista un trie pentru un element din "vector", se
				creeaza si pointerul fallen isi schimba valoarea, pentru a 
				continua parcurgerea */
				if (fallen -> vector [tasta - 2] == NULL)
				{
					fallen -> vector [tasta - 2] = new Trie ();
				}
				
				fallen = fallen -> vector [tasta - 2];
			}
			
			/* o data ajuns in nodul din trie corespunzator lui x, se creeaza
			un treap (daca nu exista) si se insereaza noul nod (format din
			cuvant si numar de aparitii */
			if (fallen -> treap == NULL)
			{
				fallen -> treap = new Treap <Node> ();
			}
			
			fallen -> treap -> insert (fallen -> treap, nod, rand () % 10000);
		}
		
		/* functie ce returneaza cuvantul cu cel mai mare numar de aparitii
		sau al x + 1 - lea cuvant (in functie de cerinta user-ului) */
		std :: string get (Trie *&fatherPointer, std :: string a, int v[])
		{
			// daca string-ul "a" (citit de la tastatura) nu contine '*'
			if (v [1] == 0)
			{
				int n = a.length ();
				Trie *fallen = fatherPointer;
				
				/* se parcurge fiecare caracter din string si se face 
				conversia lui la int pentru a putea naviga cu pointerul 
				"fallen" prin nodurile din trie */  
				for (int i = 0 ; i < n ; i++)
				{
					int tasta = (int) a [i] - 48;
					fallen = fallen -> vector [tasta - 2];
				}
				
				/* nr_noduri = numarul de noduri al treap-ului curent (care 
				contine cuvintele corespunzatoare sirului de cifre primit ca 
				parametru) */	
				int nr_noduri = fallen -> treap -> noduri (fallen -> treap);
				Node nod;
				/* se cauta cuvantul cu cele mai multe aparitii (adica cel
				de pe pozitia = cu numarul maxim de noduri din treap <=> 	
				extremitatea dreapta <=> maxim ca numar de aparitii) */
				nod = fallen -> treap -> findK (fallen -> treap, nr_noduri);
				// se sterge nodul din treap
				fallen -> treap -> erase (fallen -> treap, nod);
				// se incrementeaza numarul lui de aparitii 
				nod.aparitii ++;
				// si se insereaza din nou in treap
				fallen -> treap -> insert (fallen -> treap, nod, rand () % 
																		10000);
				
				return nod.cuvant;
			}
			else
			{
				// daca stringul contine caracterul '*'
				Trie *fallen = fatherPointer;
				
				/* se parcurge trie-ul pana la treap-ul corespunzator 	
				secventei de cifre date */
				for (int i = 0 ; i < v [0] ; i++)
				{
					int tasta = (int) a [i] - 48;
					fallen = fallen -> vector [tasta - 2];
				}
				
				// nr_noduri = numarul maxim de noduri din treap
				int nr_noduri = fallen -> treap -> noduri (fallen -> treap);
				Node nod;
				// se gaseste nodul in treap
				nod = fallen -> treap -> findK (fallen -> treap, nr_noduri - v 
															[2] % nr_noduri);
				// se sterge
				fallen -> treap -> erase (fallen -> treap, nod);
				// se incrementeaza numarul de aparitii
				nod.aparitii ++;
				// se insereaza din nou in treap
				fallen -> treap -> insert (fallen -> treap, nod, rand () % 
																		10000);
				
				return nod.cuvant;
			}
		}
};

#endif //__TRIE__H
