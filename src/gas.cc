/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * gas.cc
 * Copyright (C) David Newgas 2009 <dn271@cam.ac.uk>
 * 
 */

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <getopt.h>

using namespace std;


int main(int argc, char ** argv)
{
	int opt, number;
	double mass, radius, start, end, speed;
	
	srand(0);
	
		// initialise options
	while ((opt=getopt (argc,argv,"+ts:"))!=-1)
	{
		switch (opt)
		{
			case 't':
				cout << "0\t";
				break;
			case 's':
				srandom(atoi(optarg));
				break;
			default:
				cerr << "Unrecognised option: %d" << opt << endl;
			case '?':
			case 'h':
				cerr << "Usage: " << argv[0] << " [-t] [-s seed] number mass radius start_position end_position speed\n" << endl;
				exit(1);
	
		}
	}
	if(argc - optind != 6 )
	{
		cerr << "Usage: " << argv[0] << " [-s seed] number mass radius start_position end_position speed\n" << endl;
		exit(1);
	}
	number = atoi(argv[optind++]);
	mass = atof(argv[optind++]);
	radius = atof(argv[optind++]);
	start = atof(argv[optind++]);
	end = atof(argv[optind++]);
	speed = atof(argv[optind++]);
	while(number --)
	{
		cout << mass << ' ' << radius << ' ' << start + (double)rand() * (end-start) / RAND_MAX << ' ' << ((rand()&1)?-1:1)*speed << endl;
	}
}
