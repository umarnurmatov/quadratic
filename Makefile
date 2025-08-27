# PROGRAM CONFIG
BUILD_DIR := build
SRC_DIR := src
TEST_DIR := test
INCLUDE_DIRS := include
LOG_DIR := log
EXECUTABLE := quadratic.out
DEFINES := SINGLE_THREAD

SOURCES := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst %.c,$(BUILD_DIR)/%.o,$(notdir $(SOURCES)))
DEPS := $(patsubst %.o,%.d,$(OBJS))

# TEST CONFIG
TEST_EXECUTABLE := test_quadratic.out
TEST_SOURCES := $(filter-out %main.c,$(SOURCES)) $(wildcard $(TEST_DIR)/*.c)
TEST_OBJS := $(patsubst %.c,$(BUILD_DIR)/%.o,$(notdir $(TEST_SOURCES)))

# COMPILER CONFIG
CC := g++
SDL2_FLAGS := -I/usr/include/SDL2 -D_GNU_SOURCE=1 -D_REENTRANT
SDL2_LINK_FLAGS := -L/usr/lib -lSDL2
CPPFLAGS := -MMD -MP $(addprefix -D,$(DEFINES)) $(addprefix -I,$(INCLUDE_DIRS)) -D _DEBUG -ggdb3 -std=c++17 -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -Wlarger-than=8192 -Wstack-usage=8192 -pie -fPIE -Werror=vla -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr

# PROGRAM
$(BUILD_DIR)/$(EXECUTABLE): $(OBJS)
	@echo Linking $@...
	@$(CC) $(SDL2_LINK_FLAGS) $(SDL2_FLAGS) $(CPPFLAGS) $(OBJS) -o $@
	@echo ...done

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c 
	@echo Building $@...
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(SDL2FLAGS) $(CPPFLAGS) -c $< -o $@

.PHONY: run
run: $(BUILD_DIR)/$(EXECUTABLE)
	@./$(BUILD_DIR)/$(EXECUTABLE)

# TEST
$(BUILD_DIR)/$(TEST_EXECUTABLE): $(TEST_OBJS)
	@$(CC) $(CPPFLAGS) $(TEST_OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(TEST_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(CPPFLAGS) -c $< -o $@

.PHONY: test
test: $(BUILD_DIR)/$(TEST_EXECUTABLE)
	@./$(BUILD_DIR)/$(TEST_EXECUTABLE)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
	rm -rf $(LOG_DIR)

-include $(DEPS)
