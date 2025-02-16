SRC_DIR := src
INC_DIR := include
TARGET_DIR := target

EXE := $(TARGET_DIR)/main
INC := $(wildcard $(INC_DIR)/*.h)
SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(patsubst $(SRC_DIR)/%.cpp, $(TARGET_DIR)/%.o, $(SRC))

CPPC := g++
CPPFLAGS := -lpthread -Wall

.PHONY: all

all: run clean

run: $(EXE)
	@echo "Running.."
	@./$<
 
$(EXE): $(OBJ) | $(TARGET_DIR)
	@echo "Building binaries."
	@$(CPPC) $^ -o $@

$(TARGET_DIR)/%.o: $(SRC_DIR)/%.cpp $(INC) | $(TARGET_DIR)
	@echo "Building objects.."
	@$(CPPC) $(CPPFLAGS) -c $< -o $@ -I $(INC_DIR) 

$(TARGET_DIR):
	@echo "Create target dir.."
	@mkdir -p $@

clean:
	@echo "Cleaning up.."
	@$(RM) -rv $(TARGET_DIR)
