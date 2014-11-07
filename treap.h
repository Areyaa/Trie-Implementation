// Nicolae Alina-Elena, 311 CA

#ifndef __TREAP__H
#define __TREAP__H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include "node.h"


// clasa care contine implementarea unui treap
template <typename T> class Treap
{
	private:
	
		T key; // cheia este de tip Node: cuvant + numar aparitii
		int priority; // prioritatea este random
		Treap <T> *left, *right; // cei doi fii (caracteristici unui BST)
		bool nil; // un nod este nil cand nu contine date (nod fictiv)
		// numarul de descendenti al fiecarui nod (inclusiv el insusi)
		int nr_nodes;
		
	public:
	
		Treap ()
		{
			priority = -1;
			left = NULL;
			right = NULL;
			nil = true; // initial nodul este nil
			nr_nodes = 0; // si nu are descendenti
		}
	
		~Treap()
		{
			if (left != NULL)
			{
				delete left;
			}
			
			if (right != NULL)
			{
				delete right;
			}
		}
		
		/* metoda ce returneaza numarul de descendenti al nodului parinte
		(numarul maxim de noduri din treap-ul curent) */
		int noduri (Treap <T> *&fatherPointer)
		{
			return fatherPointer -> nr_nodes;
		}
		
		// adauga date in nodul de tip nil
		void addData (Treap <T> *&fatherPointer, T &key, int &priority)
		{
			fatherPointer -> nil = false;
			fatherPointer -> key = key;
			fatherPointer -> priority = priority;
			fatherPointer -> nr_nodes = 1;
			fatherPointer -> left = new Treap <T> ();
			fatherPointer -> right = new Treap <T> ();
  		}
  		
  		// metoda ce sterge datele dintr-un nod, transformandu-l in nil
  		void delData (Treap <T> *&fatherPointer)
  		{
			fatherPointer -> nil = true;
			fatherPointer -> priority = -1;
			
			if (fatherPointer -> left)
			{
				delete fatherPointer -> left;
			}
			
			if (fatherPointer -> right)
			{
				delete fatherPointer -> right;
			}
			
			fatherPointer -> left = NULL;
			fatherPointer -> right = NULL;
			fatherPointer -> nr_nodes = 0;
		}
		
		// returneaza "true" daca un nod este nil si "false" in caz contrar
		bool isNil (Treap <T> *&fatherPointer)
		{
    		return fatherPointer -> nil;
  		}
		
		// returneaza 1 daca gaseste un nod cu cheia "key" in treap
		bool find (Treap <T> *&fatherPointer, T &key)
		{
    		if (isNil (fatherPointer))
    		{
      			return false;
    		}
			
			// daca cheia nodului curent este cea cautata, cautarea se incheie
   			if (fatherPointer -> key == key)
   			{
   				return true;
   			}
   			else
   			{
   				/* altfel se cauta pe una din cele doua ramuri ale treap-ului
   				in functie de raportarea la "key" (cautare binara) */
   				if (key > fatherPointer -> key)
   				{
   					find (fatherPointer -> right, key);
   				}
   				else
   				{
   					find (fatherPointer -> left, key);
   				}
   			}
   		}
   		
   		/* metoda ce roteste arborele spre dreapta si recalculeaza dimensiunea
   		subarborilor */
   		void rotateRight (Treap <T> *&nod)
   		{
   			int nr = nod -> nr_nodes; // se retine numarul maxim de noduri
   			// se retine numarul de noduri din ramura dreapta
   			int l = nod -> right -> nr_nodes;
   			
   			/* si se adauga numarul de noduri de pe partea dreapta din ramura 				stanga a lui "nod" atata timp cat e posibil */
   			if (!isNil (nod -> left))
   			{
   				l += nod -> left -> right -> nr_nodes;
   			}
   			
   			/* se interschimba nodurile pentru efectuarea rotatiei */
   			Treap <T> *aux = nod -> left;
   			nod -> left = aux -> right;
   			aux -> right = nod;
   			nod = aux;
   			
   			/* se atribuie noile dimensiuni nodurilor ce si-au schimbat 
   			valorile numarului de descendenti in timpul rotatiei */
   			nod -> nr_nodes = nr;
   			nod -> right -> nr_nodes = l + 1;
    	}
    	 
		/* metoda ce roteste arborele spre stanga si recalculeaza dimensiunea
   		subarborilor, folosind algoritmul de la "rotateRight" */ 	
    	void rotateLeft (Treap <T> *&nod)
    	{
    		int nr = nod -> nr_nodes;
   			int l = nod -> left -> nr_nodes;
   			
   			if (!isNil (nod -> right))
   			{
   				l += nod -> right -> left -> nr_nodes;
   			}
   			
   			Treap <T> *aux = nod -> right;
   			nod -> right = aux -> left;
   			aux -> left = nod;
   			nod = aux;
   			
   			nod -> nr_nodes = nr;
   			nod -> left -> nr_nodes = l + 1;
  		}
 		
		// metoda ce insereaza un nod in treap
		void insert (Treap <T> *&fatherPointer, T &key, int priority)
		{
			if (isNil (fatherPointer))
			{
				addData (fatherPointer, key, priority);
				return;
			}
			else
			{
				if (key < fatherPointer -> key)
				{
					fatherPointer -> nr_nodes ++;
					insert (fatherPointer -> left, key, priority);
				}
				else
				{
					fatherPointer -> nr_nodes ++;
					insert (fatherPointer -> right, key, priority);
				}
			}

			if (fatherPointer -> left -> priority > fatherPointer -> priority)
			{
				rotateRight (fatherPointer);
			}
			else if (fatherPointer -> right -> priority > fatherPointer -> 
																	priority)
			{
				rotateLeft (fatherPointer);
			}
 		}
 		
 		// metoda ce sterge un nod din treap
 		void erase (Treap <T> *&fatherPointer, T &key)
 		{
			if (isNil (fatherPointer))
			{
			  return;
			}

			if (key < fatherPointer -> key)
			{
				fatherPointer -> nr_nodes --;
				erase (fatherPointer -> left, key);
			}
			else if (key > fatherPointer -> key)
			{
			
					fatherPointer -> nr_nodes --;
					erase (fatherPointer -> right, key);
			}
			else if (isNil (fatherPointer -> left) && isNil (fatherPointer -> 
																	right))
			{
				 delData (fatherPointer);
			}
			else
			{
				if (fatherPointer -> left -> priority > fatherPointer -> right 
																-> priority)
				{
					rotateRight (fatherPointer);
					erase (fatherPointer, key);
				}
				else
				{
					rotateLeft (fatherPointer);
					erase (fatherPointer, key);
				}
			}
		}

	  	// metoda ce realizeaza afisarea in inordine a nodurilor din treap
	  	void inOrder (Treap <T> *&fatherPointer, int &k)
	  	{
			if (isNil (fatherPointer))
			{
			  return;
			}
			
			if (fatherPointer -> left != NULL)
			{
				inOrder (fatherPointer -> left, k++);
			}
			
			std :: cout << key << " ";
			
			if (fatherPointer -> right != NULL)
			{
				inOrder (fatherPointer -> right, k++);
			}
		}
		
		// metoda ce afiseaza nodurile din treap pe nivele
	    void showLevels (Treap <T> *&fatherPointer, int &k) 
	    {
	    	if (fatherPointer)
	    	{
	    		std :: cout << "Nodul = " << fatherPointer -> key.cuvant << 
	    																'\t';
	    		std :: cout << "cu prioritatea = " << fatherPointer -> 
	    													priority << '\t';
	    		std :: cout << "pe nivelul = " << k << '\t';
	    		std :: cout << "cu numarul de aparitii = " << fatherPointer -> 
	    												key.aparitii << '\t';
	    		std :: cout << "cu numarul de noduri: " << fatherPointer -> 
	    											nr_nodes << std :: endl;
	    		
	    		showLevels (fatherPointer -> left, k + 1);
	    		showLevels (fatherPointer -> right, k + 1);
			}
   		}
   		
   		/* metoda ce realizeaza cautarea in treap a nodului cu pozitia k in 
   		sortarea nodurilor in ordine crescatoare */
		T findK (Treap <T> *&fatherPointer, int k)
		{
			/* daca fatherPointer este un nod frunza, atunci cheia ce trebuie 
			returnata este chiar cea a lui fatherPointer */
			if (isNil (fatherPointer -> right) && isNil (fatherPointer -> 
																		left))
			{
				return fatherPointer -> key;
			} 
			
			/* se retine in variabila "fallen" diferenta dintre numarul maxim 
			de noduri si numarul de noduri de pe ramura dreapta */ 
			int fallen = fatherPointer -> nr_nodes - fatherPointer -> right -> 
																	nr_nodes;
			
			// se compara "fallen" cu pozitia k la care dorim sa ajungem
			if (k == fallen)
			{
				// daca sunt egale, inseamna ca s-a ajuns la nodul dorit
				return fatherPointer -> key;
			}
			else if (k < fallen)
			{
			// daca e mai mare, inseamna ca trebuie cautat in subarborele stang
				return findK (fatherPointer -> left, k);
			}
			else
			{
			// daca e mai mic, trebuie cautat in subarborele drept
				return findK (fatherPointer -> right, k - fallen);
			}
		}
};


#endif // __TREAP__H
