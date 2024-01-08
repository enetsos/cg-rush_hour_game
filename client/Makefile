BASE_NAME := rush-hour
TARGET_DIR = .
TARGET := $(BASE_NAME) 
TARGET_ARCHIVE := $(BASE_NAME).tar.gz
MAIN_SRC_FILES := $(wildcard *.cpp)
MAIN_OBJ_FILES := $(patsubst %.cpp,%.o,$(MAIN_SRC_FILES))
ENGINE_BASE_NAME := engine
ENGINE_DIR := ../engine
ENGINE_LIB_NAME := $(ENGINE_BASE_NAME)
ENGINE_LIB_FILENAME := lib$(ENGINE_LIB_NAME).so
DEPENDENCIES_DIR := ../dependencies

CXX = g++
CXX_FLAGS = -std=c++11 -O2
CXX_FLAGS += -I$(DEPENDENCIES_DIR)/glm/include/glm
CXX_FLAGS += -I$(ENGINE_DIR)
LDFLAGS = -L$(ENGINE_DIR) -l$(ENGINE_LIB_NAME)
TAR_GZ = tar zcvf

package: $(TARGET_ARCHIVE)
	@echo "Client package created successfully!"

$(TARGET_ARCHIVE): $(TARGET)
	# Package your distribution tar.gz archive here with the necessary distribution artifacts
	# Example:
	tar zcvf $(TARGET_ARCHIVE) -C ../engine libengine.so
	@echo "$(TARGET_ARCHIVE) package done!"

$(TARGET): $(MAIN_OBJ_FILES)
	$(CXX) -o $(TARGET) $(MAIN_OBJ_FILES) $(LDFLAGS)
	@echo "$(TARGET) compile done!"

%.o: %.cpp
	# Compile your sources here
	$(CXX) $(CXX_FLAGS) -c -o $@ $<

clean:
	@rm -f $(TARGET)
	@rm -f $(MAIN_OBJ_FILES)
	@rm -f $(TARGET_ARCHIVE)

.PHONY: clean package