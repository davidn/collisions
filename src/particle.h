/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * COLLISIONS
 * Copyright (C) David Newgas 2009 <dn271@cam.ac.uk>
 * 
 */

#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include <iostream>

class particle
{
	public:
		double im;// inverse mass
		double x; // position
		double r; // radius
		double v; // velocity
		
		double momentum(); // not actually used
		double energy();   //     "      "
};

std::ostream & operator << (std::ostream &self, const particle &part);
std::istream & operator >> (std::istream &self, particle &part);
particle & operator << (particle & self, particle &other );

#endif // _PARTICLE_H_
