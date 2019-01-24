#include <iostream>
#include "SoundList.h"

SoundList::SoundList()
{
	first = nullptr;
}

SoundList::~SoundList()
{
	deleteAll();
}

bool SoundList::isEmpty()
{
	return (first == nullptr);
}

int SoundList::getTotal()
{
	if (first == nullptr)
	{
		return 0;
	}
	else
	{
		SoundElement * current = first;
		int total = 0;

		if (current != nullptr)
		{
			total++;
			current = current->getNext();
		}
	}
}

void SoundList::addFirst(char * _file)
{

	SoundElement * newFirst = new SoundElement(_file);

	if (first == nullptr)
	{
		/*nothing to do*/
	}
	else
	{
		newFirst->setNext(first);
	}
	first = newFirst;
}


void SoundList::addLast(char * _file)
{
	if (first == nullptr)
	{
		addFirst(_file);
	}
	else
	{
		SoundElement * current = first;

		SoundElement * element = new SoundElement(_file);

		while (current->getNext() != nullptr)
		{
			current = current->getNext();
		}
		current->setNext(element);
	}
}

 SoundElement * SoundList::getElement(int _index)
{
	 if (first == nullptr)
	 {
		 return nullptr;
	 }
	 else
	 {
		 int total = getTotal();

		 if ((_index > 0) && (_index <= total))
		 {
			 
			 SoundElement * current = first;
			 int currentIndex = 1;

			 while (current != nullptr)
			 {
				 if (currentIndex == _index)
				 {
					 return current;
				 }

				 currentIndex++;
				 current = current->getNext();
			 }

		 }
	 }
	 return nullptr;
}

 void SoundList::deleteFirst()
 {
	 if (first == nullptr)
	 {
		 /*nothing to do*/
	 }
	 else
	 {
		 SoundElement * deleteElement = first;
		 first = first->getNext();
		 delete  deleteElement;
	 }
 }


 void SoundList::deleteLast()
 {
	 if (first != nullptr)
	 {
		 if (first->getNext() == nullptr)
		 {
			 deleteFirst();
		 }
		 else
		 {
			 SoundElement * current = first;

			 while ((current->getNext())->getNext() != nullptr)
			 {
				 current = current->getNext();
			 }
			 SoundElement * deleteElement = current->getNext();
			 current->setNext(nullptr);
			 delete deleteElement;
		 }
	 }
 }

 void SoundList::deleteAll()
 {
	 if (first != nullptr)
	 {
		 while (first != nullptr)
		 {
			 deleteFirst();
		 }
	 }
 }


