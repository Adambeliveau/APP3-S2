#ifndef VECTEUR_H
#define VECTEUR_H




#include<iostream>
#include<fstream>

using namespace std;


template<class T>
class Vecteur {

	int capacity; //nb max d'items qui peuvent etre stockes
	int size; //nb d'items qui sont stockes
	int index; 
	T* ptrs; //tableau ou sont stock les ptrs de Ts	


public:
	Vecteur()
	{

		capacity = 1;
		size = 0;
		index = -1;
		ptrs = new T[capacity];
		

	}
	Vecteur(int cap)
	{
		capacity = cap;

	}
	~Vecteur()
	{}

	int getCapacity()
	{
		return capacity;
	}
	int getindex() { return index; }
	T getVecteur() { return ptrs; }
	int getSize()
	{
		return size;
	}
	void doubleVecteur()
	{
		T* temporaire = new T[capacity*2];
		temporaire = ptrs;

		for (int i = 0; i < capacity; i++)
		{
			temporaire[i] = ptrs[i];
		}
	
	

		size = capacity;
		capacity *= 2;
		ptrs = new T[capacity];

		for (int i = 0; i < capacity; i++)
		{
			ptrs[i] = temporaire[i];
		}
		delete[] temporaire;
	}
	void viderVecteur()
	{
		capacity = 1;
		ptrs = new T[capacity];

		size = 0;
	}
	bool isEmpty()
	{
		bool isVide = false;


		if (size == 0)
		{
			isVide = true;
		}
		return isVide;
	} //vrai si le vecteur est vide
	bool add(T nouveau)
	{//mode pile

		if (capacity == size) {
			doubleVecteur();
		}
		ptrs[size] = nouveau;

		for (int i = size - 1; i >= 0; i--)
		{
			swap(ptrs[i], ptrs[i + 1]);
		}
		

		size++;
		index = 0;

		return 1;
	}
	T retrait(int index)
	{

		T** ptrtemp = new T*[1];
		ptrtemp[0] = ptrs[index];

			for (int i = index; i < size - 1; i++) {
				ptrs[i] = ptrs[i + 1];
			}
		
		ptrs[size - 1] = NULL;
		size--;
		return ptrtemp[0];
		


	}
	T getT(int index)
	{


		if (index<0 || index>size)
			return NULL;
		else
		{
			return ptrs[index];
		}

	}
	void afficher(ostream& s)
	{
		for (int i = 0; i < size; i++)
		{
			s << ++ptrs << endl;
		}
	
		
	}

	T& operator[](int i)
	{
		if (i < 0 || i >= size) 
			throw 1;
		
		return ptrs[i];	
	}
	T operator++()
	{
		if (index == size)
			index = 0;
		
		index++;
		return ptrs[index-1];
	}
	T operator--()
	{
		if (index <= 1)
			index = size+1;

		index--;
		return ptrs[index-1];
	}
	
	void operator+=(T value)
	{//mode file
		if (capacity == size) {
			doubleVecteur();
		}


		ptrs[size] = value;


		size++;
		index = 0;

	}

};
#endif // !VECTEUR_H
