/***************************************************************************
                          tree.h  -  description
                             -------------------
    begin                : Tue Dec 4 2001
    copyright            : (C) 2001 by James Burton
    email                : jdburto@clemson.edu
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef TREE_H
#define TREE_H

#include "object.h"
#include "material.h"




/**
  *@author James Burton
  */

class Tree : public Object{

private:

	Material * leaves;
	Material * trunk;

	

public: 
	Tree();
	Tree(float x, float y, float z);
	void draw();
  void refresh();
	~Tree();
};

#endif
