# $Id: GNUmakefile,v 1.1 1999-01-07 16:05:40 gunter Exp $
# --------------------------------------------------------------
# GNUmakefile for examples module.  Gabriele Cosmo, 06/04/98.
# --------------------------------------------------------------

name := antiNeu
G4TARGET := $(name)
G4EXLIB := true

ifndef G4INSTALL
  G4INSTALL = ../../../..
endif

.PHONY: all
all: lib bin

include $(G4INSTALL)/config/architecture.gmk

EXTRALIBS := $(shell $(ROOTSYS)/bin/root-config --libs)
CPPFLAGS += $(shell $(ROOTSYS)/bin/root-config --cflags)

include $(G4INSTALL)/config/binmake.gmk


