BUILD_DIR := build
SRC_DIR := src
TEST_DIR := test
INCLUDE_DIR := include
EXECUTABLE := quadratic
TEST_EXECUTABLE := test_quadratic

CC := g++
CPPFLAGS := -MMD -MP -I$(INCLUDE_DIR) -D _DEBUG -ggdb3 -std=c++17 -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -Wlarger-than=8192 -Wstack-usage=8192 -pie -fPIE -Werror=vla -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr

SOURCES := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst %.c,$(BUILD_DIR)/%.o,$(notdir $(SOURCES)))
DEPS := $(patsubst %.o,%.d,$(OBJS))

# PROGRAM
$(BUILD_DIR)/$(EXECUTABLE).out: $(OBJS)
	$(CC) $(CPPFLAGS) $(OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c 
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(CPPFLAGS) -c $< -o $@

.PHONY: run
run: $(BUILD_DIR)/$(EXECUTABLE).out
	./$(BUILD_DIR)/$(EXECUTABLE).out

# TEST
TEST_SOURCES := $(filter-out %main.c,$(SOURCES)) $(wildcard $(TEST_DIR)/*.c)
TEST_OBJS := $(patsubst %.c,$(BUILD_DIR)/%.o,$(notdir $(TEST_SOURCES)))

$(BUILD_DIR)/$(TEST_EXECUTABLE).out: $(TEST_OBJS)
	$(CC) $(CPPFLAGS) $(TEST_OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(TEST_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(CPPFLAGS) -c $< -o $@

.PHONY: test
test: $(BUILD_DIR)/$(TEST_EXECUTABLE).out
	./$(BUILD_DIR)/$(TEST_EXECUTABLE).out

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

-include $(DEPS)
