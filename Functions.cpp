#include <iostream>


//first clear array
void clear2DimensionCharArray(char *** _array, int _size)
{
	if (_array != nullptr)
	{
		for (int i = 0; i < _size; ++i)
		{
			delete[] * (*_array + i);
			*(*_array + i) = nullptr;
		}
		delete *_array;
		*_array = nullptr;
	}
}

//  1) _array should be cleared! call clear2DimensionCharArray!  2) _valueString format : "|word1|word2|word3"
void set2DimensionCharArray(char *** _array, char * _valueString)
{
	if (_valueString != nullptr)
	{
		int _valueStringLength = strlen(_valueString);
		int _arraySize = 0;
		for (int i = 0; i < _valueStringLength; ++i)
		{
			if (*(_valueString + i) == '|')
			{
				_arraySize++;
			}
		}

		if (_arraySize > 0)
		{
			*_array = new char* [_arraySize];
			for (int i = 0; i < _arraySize; ++i)
			{
				*(*_array + i) = nullptr;
			}

			int wordLength = 0;
			int wordCounter = 0;
			int wordStartIndex = 1;

			for (int i = 0; i <= _valueStringLength; ++i)
			{
				if ((*(_valueString + i) == '|') ||  (i == _valueStringLength) )
				{
					

					if (wordCounter != 0)
					{
						*(*_array + wordCounter - 1) = new char[wordLength+1];
						strncpy_s(*(*_array + wordCounter - 1), wordLength + 1, (_valueString + wordStartIndex)  , wordLength);
					}
					wordStartIndex = i+1;
					wordCounter++;
					wordLength = 0;
				}
				else
				{
					wordLength++;
				}
			}
		}
	}
}

void clearAndSet2DimensionCharArray(char *** _array, int _size, char * _valueString)
{
	clear2DimensionCharArray(_array,  _size);
	set2DimensionCharArray  (_array,  _valueString);
}

