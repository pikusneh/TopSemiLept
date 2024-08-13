# ROOT configuration
rootlibs := $(shell root-config --libs)
rootflags := $(shell root-config --cflags)

# Correction library configuration
CORRECTION_INCDIR:=$(shell correction config --incdir)
CORRECTION_LIBDIR:=$(shell correction config --libdir)

# Directories and files
OBJDIR:=src
SRCDIR:=src

# Compilation and linking flags
SOFLAGS       = -shared
LD = g++ -m64 -g -Wall
# CXXFLAGS = -O0 -g -Wall -fmessage-length=0 $(rootflags) -fPIC -pthread -DSTANDALONE -I$(SRCDIR) -I$(CORRECTION_INCDIR) -I.

# CXXFLAGS = -O0 -g -Wall -fmessage-length=0 $(rootflags) -fpermissive -fPIC -pthread -DSTANDALONE -I$(SRCDIR) -I$(CORRECTION_INCDIR)
CXXFLAGS = -O0 -g -Wall -fmessage-length=0 $(rootflags) -fPIC -I$(SRCDIR) -I$(CORRECTION_INCDIR) -I.

# Source files and objects
SRCS := $(wildcard $(SRCDIR)/*.cpp)
HEADERS = $(wildcard $(SRCDIR)/*.h)
OBJS := $(patsubst %.cpp,%.o,$(SRCS)) $(SRCDIR)/rootdict.o

# Libraries
LIBS_EXE = $(rootlibs) -lMathMore -lGenVector -lcorrectionlib -L$(CORRECTION_LIBDIR) 
LIBS = $(rootlibs) 

# Target
TARGET =	nanoaodrdataframe

all:	$(TARGET) libnanoadrdframe.so 

all: $(EXECUTABLE)
	@echo "";
	@echo "*********************************";
	@echo "";
	@echo "     La compilation est finie :) ";
	@echo "";
	@echo "   Quel codeur!!!!!!!!!!... <3 <3 <3";
	@echo "";
	@echo "*********************************";

clean:
	rm -f $(OBJS) $(TARGET) libnanoaodrdframe.so $(SRCDIR)/rootdict.C rootdict_rdict.pcm
	rm -rf .nfs*

# # Generate dictionary
# $(SRCDIR)/rootdict.C: $(SRCDIR)/NanoAODAnalyzerrdframe.h $(SRCDIR)/SkimEvents.h $(SRCDIR)/Linkdef.h 
# $(SRCDIR)/rootdict.C: $(SRCDIR)/NanoAODAnalyzerrdframe.h $(SRCDIR)/TopSemiLeptAnalyzer.h $(SRCDIR)/Linkdef.h  

$(SRCDIR)/rootdict.C: $(SRCDIR)/NanoAODAnalyzerrdframe.h $(SRCDIR)/SkimEvents.h $(SRCDIR)/TopSemiLeptAnalyzer.h $(SRCDIR)/Linkdef.h
	rm -f $@
	rootcling -I$(CORRECTION_INCDIR) -I$(SRCDIR) $@ $^

	rm -f rootdict_rdict.pcm
	ln -s $(SRCDIR)/rootdict_rdict.pcm .

$(SRCDIR)/rootdicttmp.C: $(SRCDIR)/testing.h $(SRCDIR)/test_Linkdef.h 
	rm -f $@
	rootcling -I$(CORRECTION_INCDIR) -I$(SRCDIR) $@ $^

libtest.so: $(SRCDIR)/testing.o $(SRCDIR)/rootdicttmp.o
	$(LD) $(SOFLAGS) $(LIBS) -o $@ $^ 

$(SRCDIR)/rootdicttmp.o: $(SRCDIR)/rootdicttmp.C
	$(CXX) -c -o $@ $(CXXFLAGS) $<

# Build the shared library
libnanoadrdframe.so: $(OBJS)
	$(LD) $(SOFLAGS) $(LIBS) -o $@ $^ 

# Special cases
$(SRCDIR)/RoccoR.o: $(SRCDIR)/RoccoR.cpp $(SRCDIR)/RoccoR.h
	g++ -c -o $@ $(CXXFLAGS) $<

$(SRCDIR)/rootdict.o: $(SRCDIR)/rootdict.C
	$(CXX) -c -o $@ $(CXXFLAGS) $<

# Compile object files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) -c -o $@ $(CXXFLAGS) $<

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET)  $(OBJS) $(LIBS_EXE)

