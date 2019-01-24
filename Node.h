#pragma once
#ifndef NODE_H
#define NODE_H

class Node
{
public:
	Node();
	Node(char *, char *);
	~Node();

	void setName(char *);
	void setContent(char * );
	void setData(char *, char *);

	char * getName();
	char * getContent();


	void clearName();
	void clearContent();
	void clearData();

private:
	char * name;
	char * content;
};

#endif
