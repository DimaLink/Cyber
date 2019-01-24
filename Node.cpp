#include <iostream>
#include "Node.h"

Node::Node()
{
	name = nullptr;
	content = nullptr;
}

Node::Node(char * _name, char * _content)
{
	setData(_name,_content);
}

Node::~Node()
{
	clearData();
}

void Node::setName(char * _name)
{
	clearName();

	if (_name != nullptr)
	{
		int _nameLength = strlen(_name);
		if (_nameLength > 0)
		{
			name = new char[_nameLength+1];
			strcpy_s(name, _nameLength+1, _name);
		}
	}
}

void Node::setContent(char * _content)
{
	clearContent();

	if (_content != nullptr)
	{
		int _contentLength = strlen(_content);
		if (_contentLength > 0)
		{
			content = new char[_contentLength +1];
			strcpy_s(content,_contentLength+1, _content);
		}
	}
}

void Node::setData(char * _name, char * _content)
{
	setName(_name);
	setContent(_content);
}

char * Node::getName()
{
	return name;
}

char * Node::getContent()
{
	return content;
}

void Node::clearName()
{
	if (name != nullptr)
	{
		delete[] name;
		name = nullptr;
	}
}

void Node::clearContent()
{
	if (content != nullptr)
	{
		delete[] content;
		content = nullptr;
	}
}

void Node::clearData()
{
	clearName();
	clearContent();
}