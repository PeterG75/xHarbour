##################################
# $Id$
#
# Toplevel XWT makefile

all:
	make -C src
	make -C xwt_gtk

clean:
	make -C src clean
	make -C xwt_gtk clean
	make -C tests clean


install: all
	make -C src install
	make -C xwt_gtk install

.PHONY: clean install

