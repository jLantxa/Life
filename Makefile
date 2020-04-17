define define_mkdir_target
$(1):
	@mkdir -p $(1)
endef

CXXFLAGS := -Wall -Werror -O3

INCLUDE 	 := include
SRC		 	:= src
BUILD	 	:= build
TEST	 	:= test
TARGET	 	:= Life
TEST_TARGET := LifeTest

# Source files without main
SRC_FILES := \
	$(SRC)/BitBoard.cpp \

TEST_FILES := $(SRC_FILES) \
	$(TEST)/LifeTest.cpp \
	$(TEST)/BitBoardTest.cpp

# Main file
SRC_FILES += $(SRC)/Life.cpp

all:
	make life
	make tests
	make run-tests

life:
	$(CXX) $(CXXFLAGS) -lSDL2 -I $(INCLUDE)/ $(SRC_FILES) -o $(BUILD)/$(TARGET)

tests:
	$(CXX) $(CXXFLAGS) -lgtest -I $(INCLUDE)/ $(TEST_FILES) -o $(BUILD)/$(TEST_TARGET)

run-tests:
	./$(BUILD)/$(TEST_TARGET)

clean:
	rm -rf $(BUILD)/
