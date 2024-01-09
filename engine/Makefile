BASE_NAME := engine
TARGET_DIR = ../client
TARGET := lib$(BASE_NAME).so
MAIN_SRC_FILES := $(wildcard *.cpp)
MAIN_OBJ_FILES := $(patsubst %.cpp,%.o,$(MAIN_SRC_FILES))
TESTS_RUNNER := $(BASE_NAME)-tests-runner
TEST_SRC_FILES := $(wildcard ../UnitTest/*.cpp)
TEST_OBJ_FILES := $(patsubst %.cpp,%.o,$(TEST_SRC_FILES))
DEPENDENCIES_DIR := dependencies

CXX = g++
CXX_FLAGS = -c -fPIC -std=c++11 -O2
CXX_FLAGS += -I../engine
CXX_FLAGS += -I../$(DEPENDENCIES_DIR)/glm/include
CXX_FLAGS += -I../$(DEPENDENCIES_DIR)/freeimage/include
LD_FLAGS = -shared
LIBS = -lglut -lGL -lGLU -lfreeimage

install: $(TARGET) #$(TESTS_RUNNER)
	@echo "Engine installation done!"

$(TARGET): $(MAIN_OBJ_FILES)
	$(CXX) $(LD_FLAGS) -o $(TARGET_DIR)/$(TARGET) $(MAIN_OBJ_FILES) $(LIBS)
	@echo "$(TARGET) build done!"

$(TESTS_RUNNER): $(MAIN_OBJ_FILES) $(TEST_OBJ_FILES)
	$(CXX) -o $(TESTS_RUNNER) $^ $(LIBS)
	@echo "$(TESTS_RUNNER) build done!"
	./$(TESTS_RUNNER)
	@if [ $$? -ne 0 ]; then \
		echo "Tests failed"; \
		exit 1; \
	fi

$(TEST_OBJ_FILES): $(TEST_SRC_FILES)
	$(CXX) $(CXX_FLAGS) -o $@ $<

%.o: %.cpp
	$(CXX) $(CXX_FLAGS) -o $@ $<

clean:
	@rm -f $(TARGET_DIR)/$(TESTS_RUNNER)
	@rm -f $(TEST_OBJ_FILES)
	@rm -f $(TARGET_DIR)/$(TARGET)
	@rm -f $(MAIN_OBJ_FILES)

.PHONY: clean install
