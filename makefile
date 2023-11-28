SRC_DIR := .
OBJ_DIR := .
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
LDFLAGS := -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
CXXFLAGS := -g -Wall -fpermissive -std=c++17
TARGET := triangle.out

$(TARGET): $(OBJ_FILES)
	g++ -o $@ $^ $(LDFLAGS)
$(OBJ_DIR)/%.o: $(SRaC_DIR)/%.cpp
	g++ $(CXXFLAGS) -c -o $@ $<
run: $(TARGET)
	./$(TARGET)
clean:
	rm -f $(OBJ_FILES) $(TARGET)
