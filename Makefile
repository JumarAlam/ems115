
# Copyright (c) 2016 Ashiqur Rahman <ashiqur.rahman05@northsouth.edu>
#              Aniruddha Adhikary <aniruddha.adhikary@northsouth.edu>

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

CC := clang
EXECUTABLE := ems
.DEFAULT_GOAL := ems

# XXX: remove Wno-all

CFLAGS := \
	-Wno-all \
	-Wno-incompatible-pointer-types \
	-Iincludes \
	-g

LDFLAGS := \
	-lsqlite3

GTKFLAGS := `pkg-config --cflags --libs gtk+-2.0`

LOCAL_SRC_FILES := \
	src/main.c \
	src/login.c \
	src/ui_utils.c \
	src/main_window.c \
	src/db_utils.c

glade:
	cp ui/*.glade build/

ems: glade
	$(CC) $(CFLAGS) $(LDFLAGS) $(GTKFLAGS) -o build/$(EXECUTABLE) $(LOCAL_SRC_FILES)

clean:
	rm -Rf *.o $(EXECUTABLE)