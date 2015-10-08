
CXX=g++
CXXFLAGS=-std=c++11 -Wall
LDFLAGS= -lboost_system -lpthread

BINARY:=awesome_chat
BUILDDIR:=build

SUBDIRS:=$(shell ls -F | grep "\/" | grep -v build | grep -v Debug) 
DIRS:=./ SUBDIRS

SRC:=$(shell find ./ -name "*.cpp")
#SRC:=$(foreach d, $(DIRS), $(whildcard $(d)*.cpp) )

OBJ:=$(patsubst ./%.cpp, $(BUILDDIR)/%.o, $(SRC))
DEPS:=$(patsubst ./%.cpp, $(BUILDDIR)/%.d, $(SRC))

all: dirs $(BINARY) 

clean:
	rm -f -r $(BUILDDIR)/*
	rm -f $(BINARY)

dirs:	builddir subdirs

builddir:
	mkdir -p $(BUILDDIR)

subdirs:
	$(foreach d, $(SUBDIRS), mkdir -p $(BUILDDIR)/$(d) ; )

$(BUILDDIR)/%.o: %.cpp makefile
	$(CXX) -c -MMD -MP $< -o $@ $(CXXFLAGS)

$(BINARY): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

-include $(DEPS)
