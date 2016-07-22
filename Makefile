TARGET=main
CFLAGS=-Wall -Wextra -O3
PFLAGS=-Wall -Wextra -O3 -std=c++11
LFLAGS=-static -lmingw32 -lSDL2main -lSDL2 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lversion -luuid
FILES=$(wildcard src/*.cpp) $(wildcard src/*.c)
OBJS=$(patsubst %,build/%.o,$(basename $(FILES:src/%=%)))
.PHONY: all clean
all: $(TARGET)
$(TARGET): $(OBJS)
	@echo "Linking..."
	@mkdir -p $(@D)
	@g++ $(OBJS) $(LFLAGS) -o $@
	@echo "Done."
build/%.o: src/%.cpp
	@echo "Compiling $<"
	@mkdir -p $(@D)
	@g++ -c $< $(PFLAGS) -o $@
	@g++ $< $(PFLAGS) -MT $@ -MM -MF build/$*.d
build/%.o: src/%.c
	@echo "Compiling $<"
	@mkdir -p $(@D)
	@gcc -c $< $(CFLAGS) -o $@
	@gcc $< $(CFLAGS) -MT $@ -MM -MF build/$*.d
-include $(OBJS:.o=.d)
%.hpp %.h %.cpp %.c:
clean:
	@rm -rf *.o $(TARGET) $(TARGET).exe build/
	@echo "Cleaned."
