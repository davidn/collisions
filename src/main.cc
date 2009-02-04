/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * main.cc
 * Copyright (C) David Newgas 2009 <dn271@cam.ac.uk>
 * 
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <getopt.h>

#include "particle.h"

#define TMAX_DEFAULT 1000

using namespace std;

void iterate (double tmax, vector<particle> particles, ostream & output)
{
	vector<particle>::iterator outer,inner;
	vector<particle*> colliders,collidees;
	vector<particle*>::iterator collider,collidee;
	double tnext;
	double tthis;
	double time;
	while(time < tmax)
	{
		output << time << "\t" ;
		tnext = tmax - time; // don't consider beyond end
		for( outer = particles.begin() ; outer != particles.end(); outer ++)
		{
			output << *outer << "\t";
			for (inner = outer; inner != particles.end(); inner ++)
			{
				if (inner != outer)
				{
					tthis = (outer->x - inner->x)/(inner->v - outer->v);
					if((tthis < tnext) && (tthis > 0))
					{
						colliders.clear();
						collidees.clear();
						tnext = tthis;
					}
					if(tthis == tnext)
					{
						colliders.push_back(& *outer);
						collidees.push_back(& *inner);
					}
				}
			}
		}
		output << endl;

		time += tnext;
		
		for( outer = particles.begin() ; outer != particles.end(); outer ++)
		{
			outer->x += tnext * outer->v;
		}
		collider = colliders.begin();
		collidee = collidees.begin();
		while(collider !=colliders.end() && collidee != collidees.end())
		{
			**collider << **collidee;
			collider ++;
			collidee ++;
		}
	}
}

int main(int argc, char ** argv)
{
	istream *input = &cin;
	ostream *output = &cout;
	vector<particle> particles;
	int opt, method;
	double tmax = TMAX_DEFAULT;
	
	// initialise options
	while ((opt=getopt (argc,argv,"i:ht:f:o:"))!=-1)
	{
		switch (opt)
		{
			case 'f':
				input = new ifstream(optarg);
				if (! input->good())
				{
					printf("Could not open %s for reading\n",optarg);
					exit(1);
				}
				break;
			case 'o':
				output = new ofstream(optarg);
				if (! input->good())
				{
					printf("Could not open %s for writeing\n",optarg);
					exit(1);
				}
				break;
			case 't':
				tmax = atof(optarg);
				break;
			default:
				fprintf (stderr, "Unrecognised option: %d\n",opt);
			case '?':
			case 'h':
				fprintf(stderr, "Usage: %s [-t max_time] [-f infile] [-o outfile]\n",argv[0]);
				exit(1);
		}
	}
	
	// initialise particles
	while ( ! input->eof() )
	{
		particle next;
		*input >> next;
		if (input->fail())
			break;
		particles.push_back(next);
	}
	
	// run iterations
	iterate(tmax, particles, *output);
	
	// end
	exit(0);
}
