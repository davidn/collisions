## Process this file with automake to produce Makefile.in

## Created by Anjuta

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" 

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = collisions \
	interpolate\
	gas

gas_SOURCES = \
	gas.cc

interpolate_SOURCES = \
	interpolate.cc\
	particle.cc  \
	particle.h

collisions_SOURCES = \
	main.cc     \
	particle.h     \
	particle.cc

collisions_LDFLAGS = 

collisions_LDADD = 

plot_DATA = \
	plot

plotdir = \
	$(pkgdatadir)
