#pragma once
#ifndef OBJECT_LIST_H
#define OBJECT_LIST_H

template <class T>
class ObjectElement
{
public:
	ObjectElement<T>();
	ObjectElement<T>( T , ObjectElement<T> * =nullptr);
	~ObjectElement<T>();

	void setObject(T );
	void setNext(ObjectElement<T> *);
	T * getObject();
	ObjectElement<T> * getNext();
	

private:

	T object;
	ObjectElement<T> * next;
};

template <class T>
ObjectElement<T>::ObjectElement()
: object()
{
	next = nullptr;
}


template <class T>
ObjectElement<T>::~ObjectElement()
{
/*nothing to do*/
}


template<class T>
void ObjectElement<T>::setObject(T  _object)
{
	object = _object;
}

template <class T>
void ObjectElement<T>::setNext(ObjectElement<T> * _next)
{
	next = _next;
}

template <class T>
T * ObjectElement<T>::getObject()
{
	return &object;
}

template <class T>
ObjectElement<T> * ObjectElement<T>::getNext()
{
	return next;
}

template <class T>
ObjectElement<T>::ObjectElement(T _object, ObjectElement<T> *  _next )
{
	setObject(_object);
	setNext(_next);
}


template <class T>
class ObjectList
{
public:
	ObjectList();
	~ObjectList();

	bool isEmpty();
	int getTotal();

	void addFirst(T );
	void addElement(T);

	void deleteElement(int);
	void deleteFirst();
	void deleteLast();
	void deleteAll();

	ObjectElement<T> * getElement(int);

private:
	ObjectElement<T> * first;
};


template <class T>
ObjectList<T>::ObjectList()
{
	first = nullptr;
}

template <class T>
ObjectList<T>::~ObjectList()
{
	if (first != nullptr)
	{
		deleteAll();
		first = nullptr;
	}
}

template <class T>
bool ObjectList<T>::isEmpty()
{
	return (first == nullptr);
}


template <class T>
int ObjectList<T>::getTotal()
{
	if (first == nullptr)
	{
		return 0;
	}
	else
	{
		ObjectElement<T> * current = first;
		int total = 0;

		while (current != nullptr)
		{
			total++;
			current = current->getNext();
		}
		return total;
	}
}

template <class T>
void ObjectList<T>::addFirst( T  _object)
{
	if (first == nullptr)
	{
		ObjectElement<T> * objectElement = new ObjectElement<T>(_object);
		first = objectElement;
	}
	else
	{
		ObjectElement<T> * nextElement = first->getNext();
		delete first;
		first = nullptr;
		ObjectElement<T> * objectElement = new ObjectElement<T>(_object, nextElement);
		first = objectElement;

	}
}

template <class T>
void ObjectList<T>::addElement(T  _object)
{
	if (first == nullptr)
	{
		addFirst(_object);
	}
	else
	{
		ObjectElement<T> * current = first;
		while (current->getNext() != nullptr)
		{
			current = current->getNext();
		}
		ObjectElement<T> * newlement = new ObjectElement<T>(_object);
		current->setNext(newlement);
	}
}


template <class T>
void ObjectList<T>::deleteFirst()
{
	if (first != nullptr)
	{
		ObjectElement<T> * nextElement = first->getNext();
		delete first;
		first = nextElement;
	}
}


template <class T>
void ObjectList<T>::deleteLast()
{
	if (first != nullptr)
	{
		if (first->getNext() == nullptr)
		{
			deleteFirst();
		}
		else
		{
			ObjectElement<T> * currentElement = first;
			while ((currentElement->getNext())->getNext() != nullptr)
			{
				currentElement = currentElement->getNext();
			}
			delete currentElement->getNext();
			currentElement->setNext(nullptr);
		}
	}
}


template <class T>
void ObjectList<T>::deleteElement(int _index)
{
	if (first != nullptr)
	{
		int total = getTotal();

		if ((_index > 0) && (_index <= total))
		{
			if (_index == 1)
			{
				deleteFirst();
			}
			else
			{
				if (_index == total)
				{
					deleteLast();
				}
				else
				{
					ObjectElement<T> * currentElement = first;
					int currentIndex = 1;


					while (currentElement != nullptr)
					{
						if (currentIndex = _index - 1)
						{
							ObjectElement<T> * deleteElement = currentElement->getNext();
							currentElement->setNext( (currentElement->getNext())->getNext() );
							delete deleteElement;
							break;

						}
						currentIndex++;
					    currentElement = currentElement->getNext();
					}
				}
			}


			
			




		}
	}
}


template <class T>
void ObjectList<T>::deleteAll()
{
	if (first != nullptr)
	{
		ObjectElement<T> * currentElement = first;

		while (currentElement != nullptr)
		{
			currentElement = currentElement->getNext();
			deleteFirst();
		}
	}
}

template <class T>
ObjectElement<T> * ObjectList<T>::getElement(int _index)
{
	if (first != nullptr)
	{
		int total = getTotal();
		
		if ((_index > 0) && (_index <= total))		
		{
 			ObjectElement<T> * currentElement = first;
			int currentIndex = 1;

			while (currentElement != nullptr)
			{
				if (currentIndex == _index)
				{
					return currentElement;
					break;
				}

				currentElement = currentElement->getNext();
				currentIndex++;
			}
		}
	}
	return nullptr;
}


#endif