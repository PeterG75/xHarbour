#
# $Id$
#

ifeq ($(HB_MAIN),)
    HB_MAIN = std
endif

ROOT = ../../

PRG_SOURCES=\
	hbdoc.prg \
	genos2.prg \
	gentrf.prg \
	genng.prg \
	genhtm.prg \
	genchm.prg \
	genrtf.prg \
	genhpc.prg \
	genasc.prg \
	teeasc.prg \
	html.prg \
	ng.prg \
	os2.prg \
	rtf.prg \
	troff.prg \
	fclass1.prg \
	ffile1.prg \
	ft_funcs.prg \

PRG_MAIN=hbdoc.prg

LIBS=\
	debug \
	vm \
	rtl \
	rdd \
	rtl \
	vm \
	macro \
	pp \
	lang \
	common \

ifeq ($(HB_ARCHITECTURE)/$(HB_COMPILER),w32/mingw32)
LIBS += mainstd
endif

include $(TOP)$(ROOT)config/bin.cf

