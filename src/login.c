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
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "common_includes.h"
#include "login.h"

GtkWidget *login_window;
GtkEntry *txt_username;
GtkEntry *txt_password;

int login(char * username, char * password) {
	return (strlen(username) > 0 && strlen(password) > 0);
}

void show_forgot_password() {

}

void show_login() {
	login_window = GTK_WIDGET(gtk_builder_get_object(builder, "login_dialog"));
	gtk_builder_connect_signals(builder, NULL);

	txt_username = GTK_ENTRY(gtk_builder_get_object(builder, "txt_username"));
	txt_password = GTK_ENTRY(gtk_builder_get_object(builder, "txt_password"));

	gtk_widget_show(login_window);
}

void show_wrong_password_dialog() {
  GtkWidget *dialog;
  dialog = gtk_message_dialog_new(GTK_WINDOW(login_window),
            GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_INFO,
            GTK_BUTTONS_OK,
            LOGIN_WINDOW_WRONG_PASSWORD_MESSAGE);
  gtk_window_set_title(GTK_WINDOW(dialog), LOGIN_WINDOW_WRONG_PASSWORD_TITLE);
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy(dialog);
}

void on_btn_login_clicked(GtkObject *object, gpointer user_data) {
	if(login((char *)gtk_entry_get_text(txt_username),
		     (char *)gtk_entry_get_text(txt_password))) {
		gtk_widget_hide(login_window);
		show_main_window();
	} else {
		show_wrong_password_dialog();
	}
}

void on_login_dialog_close(GtkObject *object, gpointer user_data) {
	gtk_main_quit();
}