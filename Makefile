CCFLAGS  := -Wall -std=c11 -g -DDEBUG -D_POSIX_C_SOURCE=200112L $(CCFLAGS)

W_SRCS   := w.c
PAS_SRCS := pascal.c
LIB_SRCS := worker.c socket.c path.c err.c

W_OBJS   := $(patsubst %.c, build/%.o, $(W_SRCS))
PAS_OBJS := $(patsubst %.c, build/%.o, $(PAS_SRCS))
LIB_OBJS := $(patsubst %.c, build/%.o, $(LIB_SRCS))

SRCS     := $(W_SRCS) $(PAS_SRCS) $(LIB_SRCS)
DEPS     := $(patsubst %.c, build/%.d, $(SRCS))

.PHONY: clean all

all: build/W build/Pascal

# Build directories.
build:
	@mkdir -p $@

# The W process.
build/W: $(W_OBJS) $(LIB_OBJS) | build
	$(CC) $(CCFLAGS) $^ -o $@

# The pascal process.
build/Pascal: $(PAS_OBJS) $(LIB_OBJS) | build
	$(CC) $(CCFLAGS) $^ -o $@

# Object files.
build/%.o: %.c | build
	$(CC) -c $(CCFLAGS) $< -o $@

# Dependency files.
build/%.d: %.c | build
	@$(CC) -MM -MT '$(patsubst %.c, build/%.o, $<)' $(CCFLAGS) $< > $@

# Cleaning.
clean:
	rm -rf build

-include $(DEPS)
