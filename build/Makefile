DEBUG = -g
CFLAGS = ${DEBUG} -Wall -c
LFLAGS = ${DEBUG} -Wall
INCLUDES =  -I . -I ../ -I ../src
CXX = g++

SRC_DIR = ../src/model ../src/utils
CPP_SOURCES = $(shell find $(SRC_DIR) -name "*.cpp")
CPP_OBJECTS = $(patsubst %.cpp,%.o,${CPP_SOURCES})
EXECUTABLES = $(addprefix ../bin/, wfst-lm-decoder)

TEST_DIR = ../test
TEST_SOURCES = $(shell find ${TEST_DIR} -name "test*.cpp")
TEST_OBJECTS = $(patsubst %.cpp,%.o,${TEST_SOURCES})
#TEST_EXECUTABLES = $(addprefix ../test/,$(patsubst %.cpp,%,${TEST_SOURCES}))
#TEST_EXECUTABLES = $(addprefix ../bin/,$(patsubst %.cpp,%,${TEST_SOURCES}))
TEST_EXECUTABLES = $(patsubst %.cpp,%,${TEST_SOURCES})

all: build

build: ${CPP_OBJECTS}

test: $(CPP_OBJECTS) $(TEST_OBJECTS) $(TEST_EXECUTABLES)
	make ${TEST_EXECUTABLES}

${TEST_EXECUTABLES}: ${CPP_OBJECTS} ${TEST_OBJECTS}
#	${CXX} $(LFLAGS) $(INCLUDES) ${CPP_OBJECTS}  $(patsubst ../bin/%,%,$@).o -o $@
#	${CXX} $(LFLAGS) $(INCLUDES) ${CPP_OBJECTS}  $(patsubst ../test/%,%,$@).o -o $@
	${CXX} $(LFLAGS) $(INCLUDES) ${CPP_OBJECTS}  $(TEST_OBJECTS) -o $@

%.o: %.cpp
	$(CXX) $(CFLAGS) $(INCLUDES) $< -o $@

clean:
	@rm -f ${CPP_OBJECTS} ${TEST_OBJECTS} ${EXECUTABLES} ${TEST_EXECUTABLES}
