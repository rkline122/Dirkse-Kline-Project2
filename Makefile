CC = gcc
CFLAGS = -Wall -Werror
SRCDIR = src
BUILDDIR = build

SRCFILES = $(wildcard $(SRCDIR)/*.c)
OBJFILES = $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(SRCFILES))
TARGET = $(BUILDDIR)/bakeOff

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $@ $^

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean

clean:
	rm -f $(BUILDDIR)/*.o $(TARGET)
