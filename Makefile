CC = gcc
AS = nasm

CFLAGS = -g -m32 -c -Iinclude
ASFLAGS = -f elf32 -g
LDFLAGS = -static -m32 -g -no-pie -Wl,--no-warn-execstack
LDLIBS = -lm

METHOD ?= DIVIDING_METHOD

BUILD_DIR = build
BIN_DIR = bin
SOURCE_DIR = src
ASM_DIR = asm

TARGET = $(BIN_DIR)/programm
OBJS = $(BUILD_DIR)/funcs.o $(BUILD_DIR)/ders.o $(BUILD_DIR)/integral.o $(BUILD_DIR)/root.o $(BUILD_DIR)/main.o

.PHONY: all dividing tangent clean test

all: $(BUILD_DIR) $(BIN_DIR) $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

dividing:
	$(MAKE) clean
	$(MAKE) METHOD=DIVIDING_METHOD

tangent:
	$(MAKE) clean
	$(MAKE) METHOD=TANGENT_METHOD

$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) $(LDFLAGS) $(OBJS) -o $(TARGET) $(LDLIBS)

$(BUILD_DIR)/root.o: CFLAGS += -D$(METHOD)

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c include/%.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ 

$(BUILD_DIR)/%.o: $(ASM_DIR)/%.asm | $(BUILD_DIR)
	$(AS) $(ASFLAGS) $< -o $@ 

clean:
	mkdir -p $(BUILD_DIR) $(BIN_DIR)
	rm -f $(BUILD_DIR)/* $(BIN_DIR)/*

test: $(TARGET)
	./$(TARGET) --test-root 1:2:1:2:0.0001:1.27935
	./$(TARGET) --test-root 2:3:0:1:0.001:0.65052
	./$(TARGET) --test-root 1:3:-3:-2:0.01:-2.52222
	./$(TARGET) --test-integral 1:-2.52222:1.27935:0.001:7.052281
	./$(TARGET) --test-integral 2:0.65052:1.27935:0.001:0.718147
	./$(TARGET) --test-integral 1:-2.52222:0.65052:0.0001:5.18625