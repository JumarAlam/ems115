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
#include "main_window.h"

GtkWidget *main_window;
GtkDialog *about_dialog;
GtkStatusbar *statusbar;
GtkTreeIter iter;

enum
{
	COL_ID = 0,
	COL_NAME,
	COL_DESIGNATION,
	COL_EMAIL,
	COL_CONTACT,
	COL_SALARY,
	COL_DEPARTMENT,
	COL_ADDRESS,
	COL_JOINING_DATE,
	COL_GENDER,
	COL_DURATION,
	NUM_COLS
};

void show_main_window() {
	main_window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
	statusbar = GTK_STATUSBAR(gtk_builder_get_object(builder, "statusbar"));
	employee_list_store = GTK_LIST_STORE(gtk_builder_get_object(builder, "employee_list_store"));
	gtk_builder_connect_signals(builder, NULL);

	gtk_statusbar_push(statusbar, gtk_statusbar_get_context_id(statusbar, "boo"), "Ready");

	gtk_widget_show_all(main_window);
}

void add_new_employee_to_list(employee em1) {
    gtk_list_store_append (employee_list_store, &iter);
	gtk_list_store_set (employee_list_store, &iter,
                      COL_ID, em1.id,
                      COL_NAME, em1.name,
                      COL_DESIGNATION, em1.designation,
                      COL_EMAIL, em1.mail,
                      COL_CONTACT, em1.contact_no,
                      COL_SALARY, em1.salary,
                      COL_DEPARTMENT, em1.dept,
                      COL_ADDRESS, em1.address,
                      COL_JOINING_DATE, em1.joining_date,
                      COL_GENDER, em1.gender,
                      COL_DURATION, em1.duration,
                      -1);
	puts(em1.name);
}

void on_btn_view_profile_clicked(GtkObject *object, gpointer user_data) {

	gtk_list_store_clear(employee_list_store);
	employee_show_all(db);

}

void on_btn_add_employee_ok_clicked(GtkObject *object, gpointer user_data) {
	GtkEntry *name_box;
	GtkEntry *id_box;
	GtkEntry *designation_box;
	GtkEntry *salary_box;
	GtkEntry *email_box;
	GtkEntry *contactno_box;
	GtkEntry *department_box;
	GtkEntry *address_box;
	GtkEntry *joiningdate_box;
	GtkEntry *gender_box;
	GtkEntry *password_box;
	GtkEntry *duration_box;
	employee emp1;

	name_box = GTK_ENTRY(gtk_builder_get_object(builder, "txt_add_employee_name"));
	id_box = GTK_ENTRY(gtk_builder_get_object(builder, "txt_add_employee_id"));
	designation_box = GTK_ENTRY(gtk_builder_get_object(builder, "txt_add_employee_designation"));
	salary_box = GTK_ENTRY(gtk_builder_get_object(builder, "txt_add_employee_salary"));
	email_box = GTK_ENTRY(gtk_builder_get_object(builder, "txt_add_employee_email"));
	contactno_box = GTK_ENTRY(gtk_builder_get_object(builder, "txt_add_employee_contactno"));
	department_box = GTK_ENTRY(gtk_builder_get_object(builder, "txt_add_employee_department"));
	address_box = GTK_ENTRY(gtk_builder_get_object(builder, "txt_add_employee_address"));
	joiningdate_box = GTK_ENTRY(gtk_builder_get_object(builder, "txt_add_employee_joining_date"));
	gender_box = GTK_ENTRY(gtk_builder_get_object(builder, "txt_add_employee_gender"));
	password_box = GTK_ENTRY(gtk_builder_get_object(builder, "txt_add_employee_password"));
	duration_box = GTK_ENTRY(gtk_builder_get_object(builder, "txt_add_employee_duration"));

	strncpy(emp1.name, (char *) gtk_entry_get_text(name_box), 100 - 1);
	strncpy(emp1.designation, (char *) gtk_entry_get_text(designation_box), 50 - 1);
	strncpy(emp1.contact_no, (char *) gtk_entry_get_text(contactno_box), 100 - 1);
	strncpy(emp1.mail, (char *) gtk_entry_get_text(email_box), 100 - 1);
	strncpy(emp1.dept, (char *) gtk_entry_get_text(department_box), 50 - 1);
	strncpy(emp1.address, (char *) gtk_entry_get_text(address_box), 200 - 1);
	strncpy(emp1.joining_date, (char *) gtk_entry_get_text(joiningdate_box), 50 - 1);
	strncpy(emp1.gender, (char *) gtk_entry_get_text(gender_box), 20 - 1);
	strncpy(emp1.password, (char *) gtk_entry_get_text(password_box), 100 - 1);
	strncpy(emp1.duration, (char *) gtk_entry_get_text(duration_box), 50 - 1);
	strncpy(emp1.salary, (char *) gtk_entry_get_text(salary_box), 50 - 1);

	add_employee_to_db(emp1);
	gtk_list_store_clear(employee_list_store);
	employee_show_all(db);

	// gtk_widget_destory(add_employee_dialog);
	
}

void on_btn_edit_employee_ok_clicked(GtkObject *object, gpointer user_data) {
	GtkEntry *name_box;
	GtkEntry *id_box;
	GtkEntry *designation_box;
	GtkEntry *salary_box;
	GtkEntry *email_box;
	GtkEntry *contactno_box;
	GtkEntry *department_box;
	GtkEntry *address_box;
	GtkEntry *joiningdate_box;
	GtkEntry *gender_box;
	GtkEntry *password_box;
	GtkEntry *duration_box;
	int employee_id;
	employee emp1;

	name_box = GTK_ENTRY(gtk_builder_get_object(builder, "txt_edit_employee_name"));
	id_box = GTK_ENTRY(gtk_builder_get_object(builder, "txt_edit_employee_id"));
	designation_box = GTK_ENTRY(gtk_builder_get_object(builder, "txt_edit_employee_designation"));
	salary_box = GTK_ENTRY(gtk_builder_get_object(builder, "txt_edit_employee_salary"));
	email_box = GTK_ENTRY(gtk_builder_get_object(builder, "txt_edit_employee_email"));
	contactno_box = GTK_ENTRY(gtk_builder_get_object(builder, "txt_edit_employee_contactno"));
	department_box = GTK_ENTRY(gtk_builder_get_object(builder, "txt_edit_employee_department"));
	address_box = GTK_ENTRY(gtk_builder_get_object(builder, "txt_edit_employee_address"));
	joiningdate_box = GTK_ENTRY(gtk_builder_get_object(builder, "txt_edit_employee_joining_date"));
	gender_box = GTK_ENTRY(gtk_builder_get_object(builder, "txt_edit_employee_gender"));
	password_box = GTK_ENTRY(gtk_builder_get_object(builder, "txt_edit_employee_password"));
	duration_box = GTK_ENTRY(gtk_builder_get_object(builder, "txt_edit_employee_duration"));

	employee_id = atoi(gtk_entry_get_text(id_box));

	strncpy(emp1.name, (char *) gtk_entry_get_text(name_box), 100 - 1);
	strncpy(emp1.designation, (char *) gtk_entry_get_text(designation_box), 50 - 1);
	strncpy(emp1.contact_no, (char *) gtk_entry_get_text(contactno_box), 100 - 1);
	strncpy(emp1.mail, (char *) gtk_entry_get_text(email_box), 100 - 1);
	strncpy(emp1.dept, (char *) gtk_entry_get_text(department_box), 50 - 1);
	strncpy(emp1.address, (char *) gtk_entry_get_text(address_box), 200 - 1);
	strncpy(emp1.joining_date, (char *) gtk_entry_get_text(joiningdate_box), 50 - 1);
	strncpy(emp1.gender, (char *) gtk_entry_get_text(gender_box), 20 - 1);
	strncpy(emp1.password, (char *) gtk_entry_get_text(password_box), 100 - 1);
	strncpy(emp1.duration, (char *) gtk_entry_get_text(duration_box), 50 - 1);
	strncpy(emp1.salary, (char *) gtk_entry_get_text(salary_box), 50 - 1);


	update_employee(employee_id, emp1, db, rc);


}

gboolean on_txt_edit_employee_id_focus_out_event(GtkObject *object, GdkEvent  *event, gpointer user_data) {

	GtkEntry *id_box;
	id_box = GTK_ENTRY(gtk_builder_get_object(builder, "txt_edit_employee_id"));

	employee_show_in_edit(atoi(gtk_entry_get_text(id_box)), db);

	return (gboolean) 0;
}

void propagate_edit_box(employee emp1) {

	GtkEntry *name_box;
	GtkEntry *id_box;
	GtkEntry *designation_box;
	GtkEntry *salary_box;
	GtkEntry *email_box;
	GtkEntry *contactno_box;
	GtkEntry *department_box;
	GtkEntry *address_box;
	GtkEntry *joiningdate_box;
	GtkEntry *gender_box;
	GtkEntry *password_box;
	GtkEntry *duration_box;
	// employee emp1;

	name_box = GTK_ENTRY(gtk_builder_get_object(builder, "txt_edit_employee_name"));
	id_box = GTK_ENTRY(gtk_builder_get_object(builder, "txt_edit_employee_id"));
	designation_box = GTK_ENTRY(gtk_builder_get_object(builder, "txt_edit_employee_designation"));
	salary_box = GTK_ENTRY(gtk_builder_get_object(builder, "txt_edit_employee_salary"));
	email_box = GTK_ENTRY(gtk_builder_get_object(builder, "txt_edit_employee_email"));
	contactno_box = GTK_ENTRY(gtk_builder_get_object(builder, "txt_edit_employee_contactno"));
	department_box = GTK_ENTRY(gtk_builder_get_object(builder, "txt_edit_employee_department"));
	address_box = GTK_ENTRY(gtk_builder_get_object(builder, "txt_edit_employee_address"));
	joiningdate_box = GTK_ENTRY(gtk_builder_get_object(builder, "txt_edit_employee_joining_date"));
	gender_box = GTK_ENTRY(gtk_builder_get_object(builder, "txt_edit_employee_gender"));
	password_box = GTK_ENTRY(gtk_builder_get_object(builder, "txt_edit_employee_password"));
	duration_box = GTK_ENTRY(gtk_builder_get_object(builder, "txt_edit_employee_duration"));


	gtk_entry_set_text(name_box, emp1.name);
	gtk_entry_set_text(designation_box, emp1.designation);
	gtk_entry_set_text(salary_box, emp1.salary);
	gtk_entry_set_text(email_box, emp1.mail);
	gtk_entry_set_text(contactno_box, emp1.contact_no);
	gtk_entry_set_text(department_box, emp1.dept);
	gtk_entry_set_text(address_box, emp1.address);
	gtk_entry_set_text(joiningdate_box, emp1.joining_date);
	gtk_entry_set_text(gender_box, emp1.gender);
	gtk_entry_set_text(password_box, emp1.password);
	gtk_entry_set_text(duration_box, emp1.duration);

}

void on_btn_add_employee_clicked(GtkObject *object, gpointer user_data) {
		GtkWidget *add_employee_dialog;
		add_employee_dialog = GTK_WIDGET(gtk_builder_get_object(builder, "add_employee_dialog"));
		gtk_builder_connect_signals(builder, NULL);
		gtk_widget_show_all(add_employee_dialog);
}

void on_btn_edit_employee_clicked(GtkObject *object, gpointer user_data) {
		GtkWidget *edit_employee_dialog;
		edit_employee_dialog = GTK_WIDGET(gtk_builder_get_object(builder, "edit_employee_dialog"));
		gtk_builder_connect_signals(builder, NULL);
		gtk_widget_show_all(edit_employee_dialog);

}

void on_btn_delete_employee_clicked(GtkObject *object, gpointer user_data) {
		GtkDialog *delete_dialog;
		delete_dialog = GTK_WIDGET(gtk_builder_get_object(builder, "delete_employee_dialog"));
		gtk_builder_connect_signals(builder, NULL);
		gtk_widget_show_all(delete_dialog);
}

void on_btn_delete_employee_ok_clicked(GtkObject *object, gpointer user_data) {
	GtkEntry *userid_box;
	int user_id;
	userid_box = GTK_ENTRY(gtk_builder_get_object(builder, "txt_delete_employee_id"));
	user_id = atoi(gtk_entry_get_text(userid_box));
	delete_employee(user_id, db, rc);
}

void on_menu_help_about_activate(GtkObject *object, gpointer user_data) {
	about_dialog = GTK_DIALOG(gtk_builder_get_object(builder, "about_dialog"));
	gtk_builder_connect_signals(builder, NULL);

	gtk_dialog_run(about_dialog);
}

void on_about_dialog_response(GtkObject *object, gpointer user_data) {

}

void on_main_window_destroy(GtkObject *object, gpointer user_data) {
	gtk_main_quit();
}

void on_treeview_employee_list_row_activated(GtkObject *object, gpointer user_data) {
	printf("Clicked!");
}

void on_menu_quit_activate(GtkObject *object, gpointer user_data) {
	gtk_main_quit();
}
