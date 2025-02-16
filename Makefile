SRC_DIR := src
TARGET_DIR := target

EXE := $(TARGET_DIR)/main
SRC := $(wildcard $(SRC_DIR)/*.c)

CC := gcc

.PHONY: all

all: run clean

run: $(EXE)
	@echo "Running.."
	@./$<

$(EXE): $(OBJ) | $(TARGET_DIR)
	@echo "Building binaries.."
	@$(CC) $^ -o $@

$(TARGET_DIR)/%.o: $(SRC_DIR)/%.c | $(TARGET_DIR)
	@echo "Building objects.."
	@$(CC) $< -o $@

$(TARGET_DIR):
	@echo "Create a target dir.."
	@mkdir -p $@

clean:
	@echo "Cleaning up.."
	@$(RM) -rv $(TARGET_DIR)
