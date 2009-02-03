/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * interpolate.cc
 * Copyright (C) David Newgas 2009 <dn271@cam.ac.uk>
 * 
 */

#define TMAX_DEFAULT 1000
#define TSTEP_DEFAULT 1

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include "particle.h"

using namespace std;

vector<particle> readline()
{
	vector<particle> particles;
	particle *next;
	next = new particle;
	char line[256];
	char * current = line;
	cin.getline (line,256,'\n');
	while(current && sscanf(current,"%lf %lf\t",&next->x,&next->v)==2)
	{
		particles.push_back(*next);
		next = new particle;
		current = strchr(current+1, '\t');
		
	}
	return particles;
}

int main(int argc, char ** argv)
{
	int opt;
	double tstep = TSTEP_DEFAULT, tmax = TMAX_DEFAULT, nexttime, time , lasttime;
	vector<particle> particles, nextparticles;
	particle *next;
		// initialise options
	while ((opt=getopt (argc,argv,"t:s:"))!=-1)
	{
		switch (opt)
		{
			case 't':
				tmax = atof(optarg);
				break;
			case 's':
				tstep = atof(optarg);
				break;
			default:
				fprintf (stderr, "Unrecognised option: %d\n",opt);
			case '?':
			case 'h':
				fprintf(stderr, "Usage: %s [-t max_time] [-s step]\n",argv[0]);
				exit(1);
	
		}
	}
	cin >> time;
	lasttime = time;
	particles = readline();
	cout << time << "\t";
	for(vector<particle>::iterator iter = particles.begin(); iter != particles.end(); iter++)
	{
		cout << *iter << "\t";
	}
	cout << endl;
	while (time < tmax)
	{
		cin >> nexttime;
		if(cin.good())
		{
			nextparticles = readline();
		}
		else
			nexttime = tmax+tstep;
		while (nexttime > lasttime + tstep && lasttime < tmax)
		{
			cout << lasttime + tstep << "\t";
			for(vector<particle>::iterator iter = particles.begin(); iter != particles.end(); iter++)
			{
				iter->x += iter->v * (lasttime + tstep - time);
				cout << *iter << "\t";
			}
			cout << endl;
			
			lasttime += tstep;
			time = lasttime;
		}
		time = nexttime;
		particles = nextparticles;
	}
}
