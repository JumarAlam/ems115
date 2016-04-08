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

#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct 
{
	int id;
	char name[100];
	char designation[50];
	char mail[100];
	char contact_no[100];
	char salary[50];
	char dept[50];
	char address[200];
	char joining_date[50];
	char gender[20];
	char password[100];
	char duration[50];

} employee;

typedef struct 
{
	int id;
	char employee_id[10];
	char time_att[50];
	char date[50];
	char month[50];
	char comments[200];

} attendance;

typedef struct 
{
	int id;
	char employee_id[10];
	char start_date[50];
	char duration[50];
	char description[200];
	char comment[200];
	char status[5];

} leave;


typedef struct 
{
	int id;
	char employee_id[10];
	char basic[50];
	char extras[50];
	float total;
	char date[50];

} payroll;

typedef struct 
{
	int user_id;
	char user_name[100];
	char password[100];
	char role[50];
} portal_user;

#endif
