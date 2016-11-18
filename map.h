/*
 * map.h
 *
 *  Created on: 2016/11/11
 *      Author: user
 */

#ifndef MAP_H_
#define MAP_H_

#include "object.h"

class map {
private:
	int handle[50];
public:
	map();
	virtual ~map();
	object *get_obj();
	int get_objnum();

	void Initialize();
	void DrawInitialize();
	void DrawFinalize();

	void Update();
	void Draw();
};

#endif /* MAP_H_ */
