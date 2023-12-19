BASE_NAME := engine
TARGET_DIR = .
TARGET := lib$(BASE_NAME).so
MAIN_SRC_FILES := $(wildcard *.cpp)
MAIN_OBJ_FILES := $(patsubst %.cpp,%.o,$(MAIN_SRC_FILES))
TESTS_RUNNER := $(BASE_NAME)-tests-runner
TEST_SRC_FILES := $(wildcard *_test.cpp)
TEST_OBJ_FILES := $(patsubst %.cpp,%.o,$(TEST_SRC_FILES))
DEPENDENCIES_DIR := dependencies

CXX = g++
CXX_FLAGS = -c -fPIC -std=c++11 -O2
CXX_FLAGS += -I../$(DEPENDENCIES_DIR)/glm/include/glm/
CXX_FLAGS += -I../$(DEPENDENCIES_DIR)/freeimage/include/
LD_FLAGS = -shared
LIBS = -lglut -lGL -lGLU #-lfreeimage

install: $(TARGET)
	@echo "all done!"

$(TARGET): $(MAIN_OBJ_FILES) #$(TESTS_RUNNER)
	$(CXX) $(LD_FLAGS) -o $(TARGET) $(MAIN_OBJ_FILES) $(LIBS)
	@echo "$(TARGET) build done!"

# $(TESTS_RUNNER): $(TEST_OBJ_FILES)
#         $(CXX) -o $(TESTS_RUNNER) $(TEST_OBJ_FILES) $(LIBS)
#         @echo "$(TESTS_RUNNER) build done!"
#         ./$(TESTS_RUNNER) # execute your tests here (on test failure, exit with exit code = 1)
#         @echo "tests execution done!"

%.o: %.cpp
	$(CXX) $(CXX_FLAGS) -o $@ $<

clean: 
	@rm -f $(TESTS_RUNNER)
	@rm -f $(TEST_OBJ_FILES)
	@rm -f $(TARGET)
	@rm -f $(MAIN_OBJ_FILES)

.PHONY: clean install
