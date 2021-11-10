PROJECT := hello.exe
SRC_DIR := ../src
BUILD_DIR := ../build
OBJ_DIR := ../build/obj
EXT_DIR := ../external
 
SRC_FILES := $(wildcard $(SRC_DIR)/**/*.cpp) $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))

LIBRAIRIES := -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lglew32 -lzlib1 -lopengl32 -lSDL2_ttf

INCLUDE :=-I$(EXT_DIR)\SDL2-2.0.12\include \
	-I$(EXT_DIR)\SDL2_image-2.0.5\include \
	-I$(EXT_DIR)\SDL2_mixer-2.0.4\include \
	-I$(EXT_DIR)\glew-2.1.0\include \
	-I$(EXT_DIR)\SDL2_ttf-2.0.15\include \
	
LIB :=-L$(EXT_DIR)\SDL2-2.0.12\lib\x64 \
	-L$(EXT_DIR)\SDL2_image-2.0.5\lib\x64 \
	-L$(EXT_DIR)\SDL2_mixer-2.0.4\lib\x64 \
	-L$(EXT_DIR)\SDL2_ttf-2.0.15\lib\x64 \
	-L$(EXT_DIR)\glew-2.1.0\lib\Release\x64
 
all: $(PROJECT)
 
$(PROJECT): $(OBJ_FILES)
	g++ -o $(BUILD_DIR)/$@ $^ $(LIB) $(LIBRAIRIES)
 
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	g++ -std=c++17 -g -Wall -Wextra -pedantic -c -o $@ $< $(INCLUDE) 