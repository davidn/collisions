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

#define TMAX_DEFAULT 1000

using namespace std;

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

ostream & operator << (ostream &self, const particle &part)
{
	 self << part.x << " " << part.v;
}

istream & operator>> (istream &self, particle &part)
{
		self >> part.im >> part.r >> part.x >> part.v;
}

particle & operator << (particle & self, particle &other )
{
	double zmf_v = (self.v * other.im + other.v * self.im) / (self.im + other.im);
	
	self.v = 2 * zmf_v - self.v;
	other.v = 2 * zmf_v - other.v;
}

void iterate (double tmax, vector<particle> particles, ostream & output)
{
	vector<particle>::iterator outer,inner,collider,collidee;
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
			for (inner = particles.begin(); inner != particles.end(); inner ++)
			{
				if (inner != outer)
				{
					tthis = (outer->r + inner->r + outer->x - inner->x)/(inner->v - outer->v);
					if((tthis < tnext) && (tthis > 0))
					{
						tnext = tthis;
						collider = outer;
						collidee = inner;
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
		*collider << *collidee;
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

double particle::momentum()
{
	return v / im;
}

double particle::energy()
{
	return v * v / 2 / im;
}