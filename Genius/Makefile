CXX ?= g++

CXXFLAGS += -c -Wall $(shell pkg-config --cflags opencv4)
LDFLAGS += $(shell pkg-config --libs --static opencv4)

all: facedetectSimple

facedetectSimple: facedetectSimple.o; $(CXX) $< -o $@ $(LDFLAGS)

%.o: %.cpp; $(CXX) $< -o $@ $(CXXFLAGS)

clean: ; rm -f facedetectSimple.o facedetectSimple
