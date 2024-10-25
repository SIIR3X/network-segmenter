###########################################################################
#                                                                         #
#   Makefile                                                              #
#                                                                         #
#   Makefile of the Network Segmenter project.                            #
#                                                                         #
###########################################################################

###########################################################################
################################ ARGUMENTS ################################
###########################################################################

MAIN_ARGS = 2001:db8::1/20 80
TEST_ARGS = 2001:db8::/32 8

###########################################################################
################################ LIBRARIES ################################
###########################################################################

# Google Test
GTEST_INCLUDE_DIR = /usr/local/include
GTEST_LIB_DIR = /usr/local/lib

###########################################################################
############################### DIRECTORIES ###############################
###########################################################################

INCLUDE_DIR = include
SRC_DIR = src
TEST_DIR = tests
OBJ_DIR = obj
BIN_DIR = bin

###########################################################################
################################## FILES ##################################
###########################################################################

# Source files
SRC_FILES = \
	$(SRC_DIR)/main.cpp \
	$(SRC_DIR)/mask/mask.cpp \
	$(SRC_DIR)/address/ip_address.cpp \
	$(SRC_DIR)/address/ipv4_address.cpp \
	$(SRC_DIR)/address/ipv6_address.cpp \
	$(SRC_DIR)/network/network.cpp \
	$(SRC_DIR)/network/ipv4_network.cpp \
	$(SRC_DIR)/network/ipv6_network.cpp \
	$(SRC_DIR)/utils/utils.cpp \

# Test files
TEST_SRC_FILES = \
	$(TEST_DIR)/test_mask.cpp \
	$(TEST_DIR)/test_ip_address.cpp \
	$(TEST_DIR)/test_ipv4_address.cpp \
	$(TEST_DIR)/test_ipv6_address.cpp \
	$(TEST_DIR)/test_ipv4_network.cpp \
	$(TEST_DIR)/test_ipv6_network.cpp \

###########################################################################
############################### EXECUTABLES ###############################
###########################################################################

MAIN_EXEC = network-segmenter
TEST_EXEC = test-network-segmenter

###########################################################################
############################ COMPILER AND FLAGS ###########################
###########################################################################

CXX = g++
CXXFLAGS = -I$(INCLUDE_DIR) -Wall -Wextra -std=c++14
LDFLAGS = -lpthread
TEST_CXXFLAGS = $(CXXFLAGS) -I$(GTEST_INCLUDE_DIR)
TEST_LDFLAGS = -L$(GTEST_LIB_DIR) -lgtest -lgtest_main -lpthread

###########################################################################
####################### OS DETECTION AND VARIABLES ########################
###########################################################################

# Detect the operating system
ifeq ($(OS),Windows_NT)
	RM = del /Q /S
	RM_DIR = rmdir /Q /S
	MKDIR = mkdir
	OBJ_EXT = obj
	PROGRAM = $(BIN_DIR)\$(MAIN_EXEC).exe
	TEST_PROGRAM = $(BIN_DIR)\$(TEST_EXEC).exe
else
	RM = rm -f
	RM_DIR = rm -rf
	MKDIR = mkdir -p
	OBJ_EXT = o
	PROGRAM = $(BIN_DIR)/$(MAIN_EXEC)
	TEST_PROGRAM = $(BIN_DIR)/$(TEST_EXEC)
endif

# Commands
ifeq ($(OS),Windows_NT)
	MEMOCHECK_CMD = @echo Memory check is not supported on Windows.
	MEMORYCHECKTEST_CMD = @echo Memory check is not supported on Windows.
	CLEAN_CMD = if exist "$(OBJ_DIR)" ($(RM) "$(OBJ_DIR)\*" > NUL 2>&1) && FOR /D %%p IN ("$(OBJ_DIR)\*") DO $(RM_DIR) %%p > NUL 2>&1
	DELETE_CMD = if exist "$(PROGRAM)" $(RM) "$(PROGRAM)" > NUL 2>&1
	DELETE_TEST_CMD = if exist "$(BIN_DIR)\$(TEST_EXEC).exe" $(RM) "$(BIN_DIR)\$(TEST_EXEC).exe" > NUL 2>&1
	CLEANALL_CMD = if exist "$(OBJ_DIR)" (if exist "$(BIN_DIR)" ($(RM_DIR) "$(OBJ_DIR)" & $(RM_DIR) "$(BIN_DIR)") else ($(RM_DIR) "$(OBJ_DIR)")) else (if exist "$(BIN_DIR)" ($(RM_DIR) "$(BIN_DIR)"))
else
	MEMOCHECK_CMD = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes $(PROGRAM)
	MEMORYCHECKTEST_CMD = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes $(TEST_PROGRAM)
	CLEAN_CMD = $(RM_DIR) $(OBJ_DIR)/*
	DELETE_CMD = $(RM) $(PROGRAM)
	DELETE_TEST_CMD = $(RM) $(TEST_PROGRAM)
	CLEANALL_CMD = $(RM_DIR) $(OBJ_DIR) $(BIN_DIR)
endif

MKDIR_BIN = $(if $(filter Windows_NT, $(OS)), if not exist $(BIN_DIR) mkdir $(subst /,\\,$(BIN_DIR)), mkdir -p $(BIN_DIR))
MKDIR_OBJ = $(if $(filter Windows_NT, $(OS)), if not exist $(dir $@) mkdir $(subst /,\\,$(dir $@)), mkdir -p $(dir $@))

###########################################################################
############################### OBJECT FILES ##############################
###########################################################################

SRC_OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.$(OBJ_EXT), $(filter-out $(SRC_DIR)/main.cpp, $(SRC_FILES)))
TEST_OBJ_FILES = $(patsubst $(TEST_DIR)/%.cpp, $(OBJ_DIR)/tests/%.$(OBJ_EXT), $(TEST_SRC_FILES))

###########################################################################
################################## RULES ##################################
###########################################################################

# Compile the source files
$(OBJ_DIR)/%.$(OBJ_EXT): $(SRC_DIR)/%.cpp
	@$(MKDIR_OBJ)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile the test files
$(OBJ_DIR)/tests/%.$(OBJ_EXT): $(TEST_DIR)/%.cpp
	@$(MKDIR_OBJ)
	$(CXX) $(TEST_CXXFLAGS) -c $< -o $@

# Link the object files
$(PROGRAM): $(SRC_OBJ_FILES) $(OBJ_DIR)/main.$(OBJ_EXT)
	@$(MKDIR_BIN)
	$(CXX) $^ -o $@ $(LDFLAGS)

# Link the test object files
$(TEST_PROGRAM): $(SRC_OBJ_FILES) $(TEST_OBJ_FILES)
	@$(MKDIR_BIN)
	$(CXX) $^ -o $@ $(TEST_LDFLAGS)

###########################################################################
################################ COMMANDS #################################
###########################################################################

.PHONY: all run test memorycheck memoychecktest clean delete deletetest cleanall docs

# Default rule
all: clean delete $(PROGRAM)

# Command to run the program
run: $(PROGRAM)
	$(PROGRAM) $(MAIN_ARGS)

# Command to run the tests
test: $(TEST_PROGRAM)
	$(TEST_PROGRAM) $(TEST_ARGS)

# Command to run the memory check on the program
memorycheck: clean $(PROGRAM)
	$(MEMOCHECK_CMD) $(MAIN_ARGS)

# Command to run the memory check on the tests
memorychecktest: clean $(TEST_PROGRAM)
	$(MEMORYCHECKTEST_CMD) $(TEST_ARGS)

# Command to clean the object files
clean:
	$(CLEAN_CMD)

# Command to delete the program executable
delete:
	$(DELETE_CMD)

# Command to delete the test executable
deletetest:
	$(DELETE_TEST_CMD)

# Command to clean all files
cleanall:
	$(CLEANALL_CMD)

# Command to generate the documentation
docs:
	doxygen Doxyfile

###########################################################################