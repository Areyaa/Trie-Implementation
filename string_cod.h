// Nicolae Alina-Elena, 311 CA

#ifndef __STRING_COD__H
#define __STRING_COD__H

#include <iostream>
#include <string>


/* functie ce transforma cuvintele primite din fisier in sirul de cifre 
corespunzator tastelor de la telefon */
std :: string cod (std :: string a)
{
	std :: string b;
	
	for (unsigned int i = 0 ; i < a.length () ; i++)
	{
		if (a [i] == 'a' || a [i] == 'b' || a [i] == 'c')
		{
			b += '2';
		}
		
		if (a [i] == 'd' || a [i] == 'e' || a [i] == 'f')
		{
			b += '3';
		}
		
		if (a [i] == 'g' || a [i] == 'h' || a [i] == 'i')
		{
			b += '4';
		}
		
		if (a [i] == 'j' || a [i] == 'k' || a [i] == 'l')
		{
			b += '5';
		}
		
		if (a [i] == 'm' || a [i] == 'n' || a [i] == 'o')
		{
			b += '6';
		}
		
		if (a [i] == 'p' || a [i] == 'q' || a [i] == 'r' || a [i] == 's')
		{
			b += '7';
		}
		
		if (a [i] == 't' || a [i] == 'u' || a [i] == 'v')
		{
			b += '8';
		}
		
		if (a [i] == 'w' || a [i] == 'x' || a [i] == 'y' || a [i] == 'z')
		{
			b += '9';
		}
	}
		
	return b;
}

#endif // __STRING_COD__H
