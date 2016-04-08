/*
 * Copyright (c) 2016 Ashiqur Rahman <ashiqur.rahman05@northsouth.edu>
 *              Aniruddha Adhikary <aniruddha.adhikary@northsouth.edu>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILI  TY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "common_includes.h"
#include "main.h"

#ifndef DB_NAME
#define DB_NAME "employee_db.db"
#endif

int main(int argc, char *argv[]) {

	int stat;

	rc = sqlite3_open(DB_NAME, &db);
	stat = db_open_check(rc, &db);

	// exit upon db fail, no time for extra UI compontent
	if (stat != 1)
		return 0;

	gtk_init (&argc, &argv);
	builder = gtk_builder_new();
	gtk_builder_add_from_file (builder, GLADE_UI_FILE, NULL);

	show_login(builder);

	gtk_main();
	// g_object_unref(G_OBJECT (builder)); this fudges the memory :/

	return 0;
}
