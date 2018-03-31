CC=g++-7
CC_FLAGS=-c -std=c++11
INCLUDES=-I include
LD_FLAGS=-fopenmp
SRCDIR=src
BUILDDIR=build
TARGET=bin/exec

SOURCES=$(shell find $(SRCDIR) -type f -name *.cpp)
OBJS=$(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.cpp=.o))

$(TARGET): $(OBJS)
	@echo " Linking..."
	@echo " $(CC) $^ -o $(TARGET) $(LD_FLAGS)"; $(CC) $^ -o $(TARGET) $(LD_FLAGS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $(CC_FLAGS) $(INCLUDES) -c -o $@ $<"; $(CC) $(CC_FLAGS) $(INCLUDES) -c -o $@ $<

clean:
	@echo " Cleaning..."
	@echo " $(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)

.PHONY: clean
