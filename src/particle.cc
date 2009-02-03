/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * COLLISIONS
 * Copyright (C) David Newgas 2009 <dn271@cam.ac.uk>
 * 
 */

#include <iostream>
#include "particle.h"

std::ostream & operator << (std::ostream &self, const particle &part)
{
	 self << part.x << " " << part.v;
}

std::istream & operator >> (std::istream &self, particle &part)
{
		self >> part.im >> part.r >> part.x >> part.v;
}

particle & operator << (particle & self, particle &other )
{
	double zmf_v = (self.v * other.im + other.v * self.im) / (self.im + other.im);
	
	self.v = 2 * zmf_v - self.v;
	other.v = 2 * zmf_v - other.v;
}

double particle::momentum()
{
	return v / im;
}

double particle::energy()
{
	return v * v / 2 / im;
}

/*vector<particle> vector<particle>::duplicate(vector<particle> &self)
{
	vector<particle> created;
	vector<particle>::iterator Iter = self.begin();
	
}*/
