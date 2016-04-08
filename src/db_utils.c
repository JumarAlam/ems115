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

 /* Dear Ashiqur, kill your PHP. */

#include "common_includes.h"
#include <db_utils.h>

int login_status_global = 0;
int user_role_global = 0;

void remove_new_line(char *string) {
	int length = strlen(string);
	while (length > 0) {
		if (string[length - 1] == '\n') {
			--length;
			string[length] = '\0';
		}
		else
			break;
	}
}

int db_open_check(int db_ref, sqlite3 **db) {

	if (db_ref != SQLITE_OK) {

		fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(*db));
		sqlite3_close(*db);

		return 0;
	} else {
		//printf("DB okay!\n");
		return 1;
	}
}

//employee

void add_employee_to_db(employee emp1) {
	char *sql;
	char *err_msg = 0;

	asprintf(&sql, "INSERT INTO employee VALUES( %s, '%s', '%s', '%s', '%s', %f, '%s', '%s', '%s', '%s', '%s', '%s');",
			 NULL, emp1.name, emp1.designation, emp1.mail, emp1.contact_no, atof(emp1.salary), emp1.dept,
			 emp1.address, emp1.joining_date, emp1.gender, emp1.password, emp1.duration);

	puts(sql);
	rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

	if (rc != SQLITE_OK) {

		fprintf(stderr, "SQL error: %s\n", err_msg);
		sqlite3_free(err_msg);

	} else {

		// int last_id = sqlite3_last_insert_rowid(db);
		// printf("Employee with ID %d added!\n", last_id);
		gtk_list_store_clear(employee_list_store);
		employee_show_all(db);
		// gtk_widget_destroy(add_employee_dialog);

	}
}

 int callback_employee_show(void *data, int argc, char **argv, char **azColName) {
	int i;
	employee emp1;
	fprintf(stderr, "%s:\n", (const char *) data);
	for (i = 0; i < argc; i++) {
		// printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
		switch (i) {
			case 0:
				emp1.id = atoi(argv[i] ? argv[i] : "NULL");
				break;
			case 1:
				strncpy(emp1.name, argv[i] ? argv[i] : "NULL", 19);
				break;
			case 2:
				strncpy(emp1.designation, argv[i] ? argv[i] : "NULL", 19);
				break;
			case 3:
				strncpy(emp1.mail, argv[i] ? argv[i] : "NULL", 19);
				break;
			case 4:
				strncpy(emp1.contact_no, argv[i] ? argv[i] : "NULL", 19);
				break;
			case 5:
				strncpy(emp1.salary, argv[i] ? argv[i] : "NULL", 19);
				break;
			case 6:
				strncpy(emp1.dept, argv[i] ? argv[i] : "NULL", 19);
				break;
			case 7:
				strncpy(emp1.address, argv[i] ? argv[i] : "NULL", 19);
				break;
			case 8:
				strncpy(emp1.joining_date, argv[i] ? argv[i] : "NULL", 19);
				break;
			case 9:
				strncpy(emp1.gender, argv[i] ? argv[i] : "NULL", 19);
				break;
			case 10:
				strncpy(emp1.password, argv[i] ? argv[i] : "NULL", 19);
				break;
			case 11:
				strncpy(emp1.duration, argv[i] ? argv[i] : "NULL", 19);
				break;
			default:
				break;
		}
	}
	add_new_employee_to_list(emp1);
	return 0;
}

 int callback_employee_update(void *data, int argc, char **argv, char **azColName) {
	int i;
	fprintf(stderr, "%s:\n", (const char *) data);
	for (i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

int callback_employee_show_in_edit(void *data, int argc, char **argv, char **azColName) {
	int i;
	employee emp1;
	fprintf(stderr, "%s:\n", (const char *) data);
	for (i = 0; i < argc; i++) {
		// printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
		switch (i) {
			case 0:
				emp1.id = atoi(argv[i] ? argv[i] : "NULL");
				break;
			case 1:
				strncpy(emp1.name, argv[i] ? argv[i] : "NULL", 99);
				break;
			case 2:
				strncpy(emp1.designation, argv[i] ? argv[i] : "NULL", 49);
				break;
			case 3:
				strncpy(emp1.mail, argv[i] ? argv[i] : "NULL", 99);
				break;
			case 4:
				strncpy(emp1.contact_no, argv[i] ? argv[i] : "NULL", 99);
				break;
			case 5:
				strncpy(emp1.salary, argv[i] ? argv[i] : "NULL", 49);
				break;
			case 6:
				strncpy(emp1.dept, argv[i] ? argv[i] : "NULL", 48);
				break;
			case 7:
				strncpy(emp1.address, argv[i] ? argv[i] : "NULL", 199);
				break;
			case 8:
				strncpy(emp1.joining_date, argv[i] ? argv[i] : "NULL", 49);
				break;
			case 9:
				strncpy(emp1.gender, argv[i] ? argv[i] : "NULL", 19);
				break;
			case 10:
				strncpy(emp1.password, argv[i] ? argv[i] : "NULL", 99);
				break;
			case 11:
				strncpy(emp1.duration, argv[i] ? argv[i] : "NULL", 49);
				break;
			default:
				break;
		}
	}
	propagate_edit_box(emp1);
	return 0;
}


int employee_show_in_edit(int id, sqlite3 *db) {

	char *sql;
	asprintf(&sql, "SELECT * from employee where id=%d;", id);

	//sql = "SELECT * from employee";
	const char *data = "Employee data";
	char *zErrMsg = 0;

	int rc;
	rc = sqlite3_exec(db, sql, callback_employee_show_in_edit, (void *) data, &zErrMsg);


	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {
		//fprintf(stdout, "Operation done successfully\n");
	}

	return 0;

}

int employee_show(int id, sqlite3 *db) {

	char *sql;
	asprintf(&sql, "SELECT * from employee where id=%d;", id);

	//sql = "SELECT * from employee";
	const char *data = "Employee data";
	char *zErrMsg = 0;

	int rc;
	rc = sqlite3_exec(db, sql, callback_employee_show, (void *) data, &zErrMsg);


	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {
		//fprintf(stdout, "Operation done successfully\n");
	}

	return 0;

}

int employee_show_all(sqlite3 *db) {

	char *sql;

	sql = "SELECT * from employee";
	const char *data = "Employee data";
	char *zErrMsg = 0;

	int rc;
	rc = sqlite3_exec(db, sql, callback_employee_show, (void *) data, &zErrMsg);


	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {
		// fprintf(stdout, "Operation done successfully\n");
	}

	return 0;

}



int update_employee(int id, employee emp1, sqlite3 *db, int rc) {

	char *sql;
	char *zErrMsg = 0;
	const char *data = "Callback function called";

	asprintf(&sql, "UPDATE employee set %s = '%s', %s = '%s', %s = '%s', %s = '%s', %s = %f, %s = '%s', %s = '%s', %s = '%s', %s = '%s', %s = '%s', %s = '%s' where id=%d; ",
		"name", emp1.name,
		"designation", emp1.designation,
		"mail", emp1.mail,
		"contact_no", emp1.contact_no,
		"salary", atof(emp1.salary),
		"dept", emp1.dept,
		"address", emp1.address,
		"joining_date", emp1.joining_date,
		"gender", emp1.gender,
		"password", emp1.password,
		"duration", emp1.duration,
		id);

	// printf("%s\n", sql);


	rc = sqlite3_exec(db, sql, NULL, (void *) data, &zErrMsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {

		int last_id = sqlite3_changes(db);
		if (last_id) {
			gtk_list_store_clear(employee_list_store);
			employee_show_all(db);
			// gtk_widget_destroy(edit_employee_dialog);
		} else {
			//printf("Operation error!\n");
		}

	}

	return 1;


}



int delete_employee(int id, sqlite3 *db, int rc) {

	char *sql;
	char *zErrMsg = 0;
	const char *data = "Callback function called";

	asprintf(&sql, "DELETE from employee where id=%d; ", id);

	rc = sqlite3_exec(db, sql, 0, (void *) data, &zErrMsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {

		int last_id = sqlite3_changes(db);
		if (last_id) {
			puts("deleted");
			// gtk_widget_destroy(delete_dialog);
			gtk_list_store_clear(employee_list_store);
			employee_show_all(db);
		} else {
			printf("Operation error!\n");
		}

	}

	return 1;


}

//attendance

int get_add_attendance(attendance *attd1, sqlite3 *db, int rc) {


	printf("Employee ID:\n");
	fgets(attd1->employee_id, 10, stdin);

	printf("Time:\n");
	fgets(attd1->time_att, 50, stdin);

	printf("Date:\n");
	fgets(attd1->date, 50, stdin);

	printf("Month:\n");
	fgets(attd1->month, 50, stdin);

	printf("Comments:\n");
	fgets(attd1->comments, 200, stdin);


	printf("\n\nREVIEW!\n\n");
	printf("Employee ID: %d\n", atoi(attd1->employee_id));
	printf("Time: %s\n", attd1->time_att);
	printf("Date: %s\n", attd1->date);
	printf("Month: %s\n", attd1->month);
	printf("Comments: %s\n\n", attd1->comments);

	char confirm;
	int ans = 0;

	printf("Looks good? (y/n)\n");

	scanf("\n%c", &confirm);
	getchar();

	//printf("%c\n", confirm);

	if (confirm != 'y')
		return 0;

	remove_new_line(attd1->employee_id);
	remove_new_line(attd1->time_att);
	remove_new_line(attd1->date);
	remove_new_line(attd1->month);
	remove_new_line(attd1->comments);

	char *sql;
	asprintf(&sql, "INSERT INTO attendance VALUES( %s, %d, '%s', '%s', '%s', '%s');", NULL, atoi(attd1->employee_id),
			 attd1->time_att, attd1->date, attd1->month, attd1->comments);
//printf("%s\n", sql);
	char *err_msg = 0;
	rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

	if (rc != SQLITE_OK) {

		fprintf(stderr, "SQL error: %s\n", err_msg);
		sqlite3_free(err_msg);

	} else {

		//fprintf(stdout, "Employee Added!\n");
		int last_id = sqlite3_last_insert_rowid(db);
		printf("Attendance for user ID %d added! (attendance_id = %d)\n", atoi(attd1->employee_id), last_id);

	}


	return 1;

}

 int callback_attendance_show(void *data, int argc, char **argv, char **azColName) {
	int i;
	fprintf(stderr, "%s:\n", (const char *) data);
	for (i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

int attendance_show_all(sqlite3 *db) {

	char *sql;

	sql = "SELECT * from attendance";
	const char *data = "Attendance data:";
	char *zErrMsg = 0;

	int rc;
	rc = sqlite3_exec(db, sql, callback_attendance_show, (void *) data, &zErrMsg);


	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {
		//fprintf(stdout, "Operation done successfully\n");
	}

	return 0;

}

int attendance_show(int id, sqlite3 *db) {

	char *sql;
	asprintf(&sql, "SELECT * from attendance where employee_id=%d;", id);
	const char *data = "Attendance data:";
	char *zErrMsg = 0;

	int rc;
	rc = sqlite3_exec(db, sql, callback_attendance_show, (void *) data, &zErrMsg);


	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {

		int last_id = sqlite3_changes(db);
		if (last_id) {
			printf("Operation done!\n", last_id);
		} else {
			//printf("Operation error!\n");
		}
	}

	return 0;

}


int delete_attendance(int id, sqlite3 *db, int rc) {


	printf("\n\nAre you sure?\n\n");
	printf("(1) Yes!\n");
	printf("(2) Cancel!\n");


	int choice_update;
	char *delete_choice;


	scanf("\n%d", &choice_update);
	getchar();

	switch (choice_update) {

		case 1:
			delete_choice = "true";
			break;
		case 2:
			return 0;
			break;

		default:
			return 0;

	}


	char *sql;

	asprintf(&sql, "DELETE from attendance where id=%d; ", id);


	//printf("%s\n", sql);

	char *zErrMsg = 0;
	const char *data = "Callback function called";

	rc = sqlite3_exec(db, sql, NULL, (void *) data, &zErrMsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {
		int last_id = sqlite3_changes(db);
		if (last_id) {
			printf("Operation done!\n", last_id);
		} else {
			//printf("Operation error!\n");
		}
	}

	return 1;


}


int update_attendance(int id, sqlite3 *db, int rc) {


	printf("\n\nSelect Update Option:\n\n");
	printf("(1) Employee ID\n");
	printf("(2) Time\n");
	printf("(3) Date\n");
	printf("(4) Month\n");
	printf("(5) Comments\n");
	printf("(0) Main Menu\n");


	int choice_update;
	char *update_opt;


	scanf("\n%d", &choice_update);
	getchar();

	switch (choice_update) {

		case 0:
			return 0;
			break;
		case 1:
			update_opt = "employee_id";
			break;
		case 2:
			update_opt = "time";
			break;
		case 3:
			update_opt = "date";
			break;
		case 4:
			update_opt = "month";
			break;
		case 5:
			update_opt = "comments";
			break;

		default:
			return 0;

	}


	char new_val[200];
	printf("New value:\n");
	fgets(new_val, 200, stdin);
	remove_new_line(new_val);

	char *sql;
	if (choice_update == 1) {

		asprintf(&sql, "UPDATE attendance set %s = %d where id=%d; ", update_opt, atoi(new_val), id);

	} else {

		asprintf(&sql, "UPDATE attendance set %s = '%s' where id=%d; ", update_opt, new_val, id);

	}


	char *zErrMsg = 0;
	const char *data = "Callback function called";

	rc = sqlite3_exec(db, sql, NULL, (void *) data, &zErrMsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {

		int last_id = sqlite3_changes(db);
		if (last_id) {
			printf("Operation done!\n", last_id);
		} else {
			//printf("Operation error!\n");
		}
	}

	return 1;


}

////leave

int get_add_leave(leave *leave1, sqlite3 *db, int rc) {

	printf("Employee ID:\n");
	fgets(leave1->employee_id, 10, stdin);

	printf("Start Date:\n");
	fgets(leave1->start_date, 50, stdin);

	printf("Duration:\n");
	fgets(leave1->duration, 50, stdin);

	printf("Description:\n");
	fgets(leave1->description, 50, stdin);

	printf("Comments:\n");
	fgets(leave1->comment, 200, stdin);

	printf("Status (1 = yes, 0 = no):\n");
	fgets(leave1->status, 200, stdin);


	printf("\n\nREVIEW!\n\n");
	printf("Employee ID: %d\n", atoi(leave1->employee_id));
	printf("Start Date: %s\n", leave1->start_date);
	printf("Duration: %s\n", leave1->duration);
	printf("Description: %s\n", leave1->description);
	printf("Comments: %s\n\n", leave1->comment);
	printf("Status: %d\n\n", atoi(leave1->status));


	char confirm;
	int ans = 0;

	printf("Looks good? (y/n)\n");

	scanf("\n%c", &confirm);
	getchar();

	//printf("%c\n", confirm);

	if (confirm != 'y')
		return 0;

	remove_new_line(leave1->employee_id);
	remove_new_line(leave1->start_date);
	remove_new_line(leave1->duration);
	remove_new_line(leave1->description);
	remove_new_line(leave1->comment);
	remove_new_line(leave1->status);

	char *sql;
	asprintf(&sql, "INSERT INTO leave VALUES( %s, %d, '%s', '%s', '%s', '%s',%d);", NULL, atoi(leave1->employee_id),
			 leave1->start_date, leave1->duration, leave1->description, leave1->comment, atoi(leave1->status));
//printf("%s\n", sql);
	char *err_msg = 0;
	rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

	if (rc != SQLITE_OK) {

		fprintf(stderr, "SQL error: %s\n", err_msg);
		sqlite3_free(err_msg);

	} else {

		//fprintf(stdout, "Employee Added!\n");
		int last_id = sqlite3_last_insert_rowid(db);
		printf("Leave for user ID %d added! (leave_id = %d)\n", atoi(leave1->employee_id), last_id);

	}


	return 1;

}


 int callback_leave_show(void *data, int argc, char **argv, char **azColName) {
	int i;
	fprintf(stderr, "%s:\n", (const char *) data);
	for (i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

int leave_show_all(sqlite3 *db) {

	char *sql;

	sql = "SELECT * from leave";
	const char *data = "Leave data";
	char *zErrMsg = 0;

	int rc;
	rc = sqlite3_exec(db, sql, callback_leave_show, (void *) data, &zErrMsg);


	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {
		//fprintf(stdout, "Operation done successfully\n");
	}

	return 0;

}

int leave_show(int id, sqlite3 *db) {

	char *sql;
	asprintf(&sql, "SELECT * from leave where employee_id=%d;", id);
	const char *data = "Leave data";
	char *zErrMsg = 0;

	int rc;
	rc = sqlite3_exec(db, sql, callback_leave_show, (void *) data, &zErrMsg);


	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {
		//fprintf(stdout, "Operation done successfully\n");
		int last_id = sqlite3_changes(db);
		if (last_id) {
			printf("Operation done!\n", last_id);
		} else {
			//printf("Operation error!\n");
		}
	}

	return 0;

}

int update_leave(int id, sqlite3 *db, int rc) {


	printf("\n\nSelect Update Option:\n\n");
	printf("(1) Employee ID\n");
	printf("(2) Start Date\n");
	printf("(3) Duration\n");
	printf("(4) Description\n");
	printf("(5) Comment\n");
	printf("(6) Status\n");
	printf("(0) Main Menu\n");


	int choice_update;
	char *update_opt;


	scanf("\n%d", &choice_update);
	getchar();

	switch (choice_update) {

		case 0:
			return 0;
			break;
		case 1:
			update_opt = "employee_id";
			break;
		case 2:
			update_opt = "start_date";
			break;
		case 3:
			update_opt = "duration";
			break;
		case 4:
			update_opt = "description";
			break;
		case 5:
			update_opt = "comment";
			break;
		case 6:
			update_opt = "status";
			break;


		default:
			return 0;

	}


	char new_val[200];
	printf("New value:\n");
	fgets(new_val, 200, stdin);
	remove_new_line(new_val);

	char *sql;
	if (choice_update == 1 || choice_update == 6) {

		asprintf(&sql, "UPDATE leave set %s = %d where id=%d; ", update_opt, atoi(new_val), id);

	} else {

		asprintf(&sql, "UPDATE leave set %s = '%s' where id=%d; ", update_opt, new_val, id);

	}


	char *zErrMsg = 0;
	const char *data = "Callback function called";

	rc = sqlite3_exec(db, sql, NULL, (void *) data, &zErrMsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {
		int last_id = sqlite3_changes(db);
		if (last_id) {
			printf("Operation done!\n", last_id);
		} else {
			//printf("Operation error!\n");
		}
	}

	return 1;


}


int delete_leave(int id, sqlite3 *db, int rc) {


	printf("\n\nAre you sure?\n\n");
	printf("(1) Yes!\n");
	printf("(2) Cancel!\n");


	int choice_update;
	char *delete_choice;


	scanf("\n%d", &choice_update);
	getchar();

	switch (choice_update) {

		case 1:
			delete_choice = "true";
			break;
		case 2:
			return 0;
			break;

		default:
			return 0;

	}


	char *sql;

	asprintf(&sql, "DELETE from leave where id=%d; ", id);


	//printf("%s\n", sql);

	char *zErrMsg = 0;
	const char *data = "Callback function called";

	rc = sqlite3_exec(db, sql, NULL, (void *) data, &zErrMsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {

		int last_id = sqlite3_changes(db);
		if (last_id) {
			printf("Operation done!\n", last_id);
		} else {
			//printf("Operation error!\n");
		}

	}

	return 1;


}


//payroll

int get_add_payroll(payroll *pay1, sqlite3 *db, int rc) {

	printf("Employee ID:\n");
	fgets(pay1->employee_id, 10, stdin);

	printf("Basic:\n");
	fgets(pay1->basic, 50, stdin);

	printf("Extars:\n");
	fgets(pay1->extras, 50, stdin);

	float total = atof(pay1->basic) + atof(pay1->extras);

	printf("Total:\n");
	//fgets(pay1->total, 50, stdin);
	printf("%f\n", total);
	pay1->total = total;

	printf("Date:\n");
	fgets(pay1->date, 50, stdin);


	printf("\n\nREVIEW!\n\n");
	printf("Employee ID: %d\n", atoi(pay1->employee_id));
	printf("Basic: %f\n", atof(pay1->basic));
	printf("Extars: %f\n", atof(pay1->extras));
	printf("Total: %f\n", pay1->total);
	printf("Date: %s\n\n", pay1->date);


	char confirm;
	int ans = 0;

	printf("Looks good? (y/n)\n");

	scanf("\n%c", &confirm);
	getchar();

	//printf("%c\n", confirm);

	if (confirm != 'y')
		return 0;

	remove_new_line(pay1->employee_id);
	remove_new_line(pay1->basic);
	remove_new_line(pay1->extras);
//remove_new_line(pay1->total);
	remove_new_line(pay1->date);

	char *sql;
	asprintf(&sql, "INSERT INTO payroll VALUES( %s, %d, '%f', '%f', '%f', '%s');", NULL, atoi(pay1->employee_id),
			 atof(pay1->basic), atof(pay1->extras), pay1->total, pay1->date);


	char *err_msg = 0;
	rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

	if (rc != SQLITE_OK) {

		fprintf(stderr, "SQL error: %s\n", err_msg);
		sqlite3_free(err_msg);

	} else {

		//fprintf(stdout, "Employee Added!\n");
		int last_id = sqlite3_last_insert_rowid(db);
		printf("Payroll for user ID %d added! (payroll_id = %d)\n", atoi(pay1->employee_id), last_id);

	}


	return 1;

}

 int callback_payroll_show(void *data, int argc, char **argv, char **azColName) {
	int i;
	fprintf(stderr, "%s:\n", (const char *) data);
	for (i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

int payroll_show_all(sqlite3 *db) {

	char *sql;

	sql = "SELECT * from payroll";
	const char *data = "Payroll data";
	char *zErrMsg = 0;

	int rc;
	rc = sqlite3_exec(db, sql, callback_payroll_show, (void *) data, &zErrMsg);


	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {
		//fprintf(stdout, "Operation done successfully\n");
	}

	return 0;

}

int payroll_show(int id, sqlite3 *db) {

	char *sql;
	asprintf(&sql, "SELECT * from payroll where employee_id=%d;", id);
	const char *data = "Payroll data";
	char *zErrMsg = 0;

	int rc;
	rc = sqlite3_exec(db, sql, callback_payroll_show, (void *) data, &zErrMsg);


	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {
		//fprintf(stdout, "Operation done successfully\n");
		int last_id = sqlite3_changes(db);
		if (last_id) {
			printf("Operation done!\n", last_id);
		} else {
			//printf("Operation error!\n");
		}

	}

	return 0;

}


int update_payroll(int id, sqlite3 *db, int rc) {


	printf("\n\nSelect Update Option:\n\n");
	printf("(1) Employee ID\n");
	printf("(2) Basic\n");
	printf("(3) Extras\n");
	printf("(4) Total\n");
	printf("(5) Date\n");
	printf("(0) Main Menu\n");


	int choice_update;
	char *update_opt;


	scanf("\n%d", &choice_update);
	getchar();

	switch (choice_update) {

		case 0:
			return 0;
			break;
		case 1:
			update_opt = "employee_id";
			break;
		case 2:
			update_opt = "basic";
			break;
		case 3:
			update_opt = "extras";
			break;
		case 4:
			update_opt = "total";
			break;
		case 5:
			update_opt = "date";
			break;

		default:
			return 0;

	}


	char new_val[200];
	printf("New value:\n");
	fgets(new_val, 200, stdin);
	remove_new_line(new_val);

	char *sql;
	if (choice_update == 2 || choice_update == 3 || choice_update == 4) {

		//add additional summation here

		asprintf(&sql, "UPDATE payroll set %s = '%f' where id=%d; ", update_opt, atof(new_val), id);

	} else {

		asprintf(&sql, "UPDATE payroll set %s = '%s' where id=%d; ", update_opt, new_val, id);

	}


	char *zErrMsg = 0;
	const char *data = "Callback function called";

	rc = sqlite3_exec(db, sql, NULL, (void *) data, &zErrMsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {

		int last_id = sqlite3_changes(db);
		if (last_id) {
			printf("Operation done!\n", last_id);
		} else {
			//printf("Operation error!\n");
		}

	}

	return 1;


}


int delete_payroll(int id, sqlite3 *db, int rc) {


	printf("\n\nAre you sure?\n\n");
	printf("(1) Yes!\n");
	printf("(2) Cancel!\n");


	int choice_update;
	char *delete_choice;


	scanf("\n%d", &choice_update);
	getchar();

	switch (choice_update) {

		case 1:
			delete_choice = "true";
			break;
		case 2:
			return 0;
			break;

		default:
			return 0;

	}


	char *sql;

	asprintf(&sql, "DELETE from payroll where id=%d; ", id);


	//printf("%s\n", sql);

	char *zErrMsg = 0;
	const char *data = "Callback function called";

	rc = sqlite3_exec(db, sql, NULL, (void *) data, &zErrMsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {

		int last_id = sqlite3_changes(db);
		if (last_id) {
			printf("Operation done!\n", last_id);
		} else {
			//printf("Operation error!\n");
		}

	}

	return 1;


}


//portal_user

int get_add_portal_user(portal_user *portal_user, sqlite3 *db, int rc) {

	printf("UserName:\n");
	fgets(portal_user->user_name, 100, stdin);

	printf("Password:\n");
	fgets(portal_user->password, 100, stdin);

	printf("Role:\n");
	fgets(portal_user->role, 50, stdin);


	printf("\n\nREVIEW!\n\n");
	printf("UserName: %s\n", portal_user->user_name);
	printf("Password: %s\n", portal_user->password);
	printf("Role (admin, manager): %s\n", portal_user->role);


	char confirm;
	int ans = 0;

	printf("Looks good? (y/n)\n");

	scanf("\n%c", &confirm);
	getchar();

	//printf("%c\n", confirm);

	if (confirm != 'y')
		return 0;

	remove_new_line(portal_user->user_name);
	remove_new_line(portal_user->password);
	remove_new_line(portal_user->role);

	char *sql;
	asprintf(&sql, "INSERT INTO portal_user VALUES( %s, '%s', '%s', '%s');", NULL, portal_user->user_name,
			 portal_user->password, portal_user->role);


	char *err_msg = 0;
	rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

	if (rc != SQLITE_OK) {

		fprintf(stderr, "SQL error: %s\n", err_msg);
		sqlite3_free(err_msg);

	} else {

		//fprintf(stdout, "Employee Added!\n");
		int last_id = sqlite3_last_insert_rowid(db);
		printf("Portal User with user ID %d added!\n", last_id);

	}


	return 1;

}

 int callback_portal_user_show(void *data, int argc, char **argv, char **azColName) {
	int i;
	fprintf(stderr, "%s:\n", (const char *) data);
	for (i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

int portal_user_show_all(sqlite3 *db) {

	char *sql;

	sql = "SELECT * from portal_user";
	const char *data = "Portal user data";
	char *zErrMsg = 0;

	int rc;
	rc = sqlite3_exec(db, sql, callback_portal_user_show, (void *) data, &zErrMsg);


	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {
		//fprintf(stdout, "Operation done successfully\n");
	}

	return 0;

}

int portal_user_show(int id, sqlite3 *db) {

	char *sql;
	asprintf(&sql, "SELECT * from portal_user where user_id=%d;", id);
	const char *data = "Portal user data";
	char *zErrMsg = 0;

	int rc;
	rc = sqlite3_exec(db, sql, callback_portal_user_show, (void *) data, &zErrMsg);


	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {
		//fprintf(stdout, "Operation done successfully\n");
		int last_id = sqlite3_changes(db);
		if (last_id) {
			printf("Operation done!\n", last_id);
		} else {
			//printf("Operation error!\n");
		}
	}

	return 0;

}

int update_portal_user(int id, sqlite3 *db, int rc) {


	printf("\n\nSelect Update Option:\n\n");
	printf("(1) UserName\n");
	printf("(2) Password\n");
	printf("(3) Role\n");
	printf("(0) Main Menu\n");


	int choice_update;
	char *update_opt;


	scanf("\n%d", &choice_update);
	getchar();

	switch (choice_update) {

		case 0:
			return 0;
			break;
		case 1:
			update_opt = "user_name";
			break;
		case 2:
			update_opt = "password";
			break;
		case 3:
			update_opt = "role";
			break;

		default:
			return 0;

	}


	char new_val[200];
	printf("New value:\n");
	fgets(new_val, 200, stdin);
	remove_new_line(new_val);

	char *sql;

	asprintf(&sql, "UPDATE portal_user set %s = '%s' where user_id=%d; ", update_opt, new_val, id);


	char *zErrMsg = 0;
	const char *data = "Callback function called";

	rc = sqlite3_exec(db, sql, NULL, (void *) data, &zErrMsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {

		int last_id = sqlite3_changes(db);
		if (last_id) {
			printf("Operation done!\n", last_id);
		} else {
			//printf("Operation error!\n");
		}

	}

	return 1;


}

 int portal_user_delete_callback(void *data, int argc, char **argv, char **azColName) {


	printf("Callback!\n");
	return 0;
}

int delete_portal_user(int id, sqlite3 *db, int rc) {


	printf("\n\nAre you sure?\n\n");
	printf("(1) Yes!\n");
	printf("(2) Cancel!\n");


	int choice_update;
	char *delete_choice;


	scanf("\n%d", &choice_update);
	getchar();

	switch (choice_update) {

		case 1:
			delete_choice = "true";
			break;
		case 2:
			return 0;
			break;

		default:
			return 0;

	}


	char *sql;

	asprintf(&sql, "DELETE from portal_user where user_id=%d; ", id);


	//printf("%s\n", sql);

	char *zErrMsg = 0;
	const char *data = "Callback function called";

	rc = sqlite3_exec(db, sql, NULL, (void *) data, &zErrMsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {
		//fprintf(stdout, "Portal user deleted!\n");
		//sqlite3_int64 last_id = sqlite3_last_insert_rowid(db);
		int last_id = sqlite3_changes(db);
		if (last_id) {
			printf("Employee deleted!\n", last_id);
		} else {
			//printf("Delete error!\n");
		}

	}

	return 1;


}

 int login_callback(void *data, int argc, char **argv, char **azColName) {

	int i;
	if (i > 0) {
		if (strcmp(argv[2], "admin") == 0) {
			user_role_global = 1;
		} else if (strcmp(argv[2], "manager") == 0) {
			user_role_global = 2;
		} else {
			user_role_global = 0;
		}

		login_status_global = 1;
		gtk_widget_hide(login_window);
		show_main_window();
	} else {
		show_wrong_password_dialog();
	}
	return 0;
}

int login_user_func(sqlite3 *db, int rc, sqlite3_stmt *res, int *role) {

	char userName[100];
	char password[100];
	char user_type[50];

	printf("UserName:\n");
	fgets(userName, 100, stdin);

	printf("Password:\n");
	fgets(password, 100, stdin);

	printf("User Type [p - portal user, e - employee]:\n");
	fgets(user_type, 100, stdin);


	remove_new_line(userName);
	remove_new_line(password);
	remove_new_line(user_type);

	if (user_type[0] == 'e') {
		printf("Employee access not available!\n");
		return 0;
	} else if (user_type[0] == 'p') {

		char *sql;
		asprintf(&sql,
				 "SELECT user_id, user_name, role from portal_user where user_name='%s' AND password='%s' LIMIT 1;",
				 userName, password);

		//printf("%s\n", sql);
		char *zErrMsg = 0;
		const char *data = "Callback function called";

		int rc;
		rc = sqlite3_exec(db, sql, login_callback, (void *) data, &zErrMsg);


		if (rc != SQLITE_OK) {
			//fprintf(stderr, "SQL error: %s\n", zErrMsg);
			return 0;
			sqlite3_free(zErrMsg);
		} else {
			if (login_status_global) {
				*role = user_role_global;
				//printf("user rol %d\n", user_role_global);

				return 1;
			}
			//fprintf(stdout, "Operation done successfully\n");
		}


	} else {

		printf("Please enter correct role!\n");
		return 0;
	}


	return 0;

}
