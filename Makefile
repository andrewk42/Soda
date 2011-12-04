CXX = u++					                    # compiler
CXXFLAGS = -g -Wall -Wno-unused-label -MMD	    # compiler flags
MAKEFILE_NAME = ${firstword ${MAKEFILE_LIST}}	# makefile name

OBJECTS1 = soda.o config.o bank.o parent.o card.o office.o nameserver.o machine.o plant.o truck.o student.o printer.o
EXEC1 = soda				                    # executable name

DEPENDS = ${OBJECT1:.o=.d}			            # substitute ".o" with ".d"

#############################################################

.PHONY : all clean

all : ${EXEC1}					                # build executable

${EXEC1} : ${OBJECTS1}				            # link step 1st executable
	${CXX} $^ -o $@

#############################################################

${OBJECT1} : ${MAKEFILE_NAME}			        # OPTIONAL : changes to this file => recompile

-include ${DEPENDS}				                # include *.d files containing program dependences

clean :						                    # remove files that can be regenerated
	rm -f *.d *.o ${EXEC1} interference
