#include "pch.h" 
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <libpq-fe.h>
#include <fstream>
#include <json.hpp>
#include <algorithm>

#define UNUSED(x) (void)(x)

using namespace std;
/*
static const char* name_price_dscrptn[][3] = {
	{ "ice axe", "5000", "CT" },
	{ "rope", "4500", "10mm/60m" },
	{ "helmet", "2000", "CT" },
	{ "boots", "5500", "mammut"},
	{"waterproof jacket", "7000", "the north face"},
	{ NULL, NULL }
};*/



static PGconn* conn = NULL;
static PGresult* res = NULL;

static void
terminate(int code)
{
	if (code != 0)
		fprintf(stderr, "%s\n", PQerrorMessage(conn));

	if (res != NULL)
		PQclear(res);

	if (conn != NULL)
		PQfinish(conn);

	exit(code);
}

static void
clearRes()
{
	PQclear(res);
	res = NULL;
}

static void
processNotice(void *arg, const char *message)
{
	UNUSED(arg);
	UNUSED(message);
}

//что необходимо сделать:

//1. организовать запись в базу данных +
//1.1 Проверка пересечения полигонов-> return error code
//1.2 Проверка Совпадения полигонов -> no record to db
//2.Реализовать функцию, возвращающая вложенные полигоны
//INSERT INTO tablename IF polygon not same AS (как тут перебрать полигоны) AND not itersects


//PQconnectStart
//connectOptions1
	//parse_connection_string
		//conninfo_parse
			//pgoptions
//connectOptions2
//connectDBStart

int main() {
	
	PGconn * conn = nullptr;

	const char * pghost = "127.0.0.1";
	const char * pgport = "5431";
	const char *dbName = "postgres";
	const char *login = "postgres";
	const char *pwd = "postgres";
	const char *pgoptions = NULL;
	const char *pgtty = NULL;

	const char * conninfo = "postgresql:///mydb?host=localhost&port=5431";

	//conn = PQsetdbLogin(pghost, pgport, pgoptions, pgtty, dbName, login, pwd);

	PQconnectdb(conninfo);

	/*
	conn = PQconnectdb("user=postgres password=postgres dbname=postgres");
	//cout << *conn->pgoptions << endl;;
	if (PQstatus(conn) != CONNECTION_OK)
		terminate(1);
		*/
	//res = PQexec(conn, "CREATE TABLE IF NOT EXISTS polygons (id serial PRIMARY KEY, color varchar(64), name varchar(64), coordinates polygon);");
	//cout << PQresStatus(PQresultStatus(res)) << endl;

	

	//ifstream inputJSONStream("C:/Users/euge/source/repos/ConsoleApplication8/ConsoleApplication8/resources/poligon_1.txt");
	//auto command = "INSERT INTO polygons (color, name, coordinates) VALUES ($1, $2, $3);";
	//nlohmann::json deserializedHandler;
	//nlohmann::json color, name, coords;
	//string coordsString;
	//const char * coordChars;
	

	/*const char * params[3];

	if (inputJSONStream.is_open()) {
		deserializedHandler = nlohmann::json::parse(move(inputJSONStream));
		
		cout << deserializedHandler.type_name() << endl;
		for (int i = 0;  i < deserializedHandler.size(); i++) {
			color = *(deserializedHandler.begin()->find("color"));
			params[0] = (color.dump()).c_str();
			auto colorstrng = color.dump();
			auto colorchar = colorstrng.c_str();

			name = *(deserializedHandler.begin()->find("name"));
			auto namestrng = name.dump();
			auto namechar = namestrng.c_str();
			params[1] = (name.dump()).c_str();
			
			coords = *(deserializedHandler.begin()->find("coords"));
			auto coordValues = *coords.begin();
			coordsString = coordValues.dump();
			replace(coordsString.begin(), coordsString.end(), '[', '(');
			replace(coordsString.begin(), coordsString.end(), ']', ')');
			coordChars = coordsString.c_str();

			params[0] = colorchar;
			params[1] = namechar;
			params[2] = coordChars;

			//make checks before
			if (PQstatus(conn) == CONNECTION_OK) {
				res = PQexecParams(conn, command, 3, NULL,params,NULL,NULL,0);
				cout << PQresStatus(PQresultStatus(res)) << endl;
				cout << PQerrorMessage(conn) << endl;

				auto mess = PQerrorMessage(conn);
				cout << mess << endl;
			}
			
		}
		
	}

	//?#	Intersects?	lseg '((-1,0),(1,0))' ?# box '((-2,-2),(2,2))'
	//@>	Contains ? circle '((0,0),2)' @> point '(1,1)'
	//~= Same as ? polygon '((0,0),(1,1))' ~= polygon '((1,1),(0,0))'*/

	/*
	int libpq_ver = PQlibVersion();
	printf("Version of libpq: %d\n", libpq_ver);

	conn = PQconnectdb("user=postgres password=postgres host=127.0.0.1 dbname=postgres");
	if (PQstatus(conn) != CONNECTION_OK)
		terminate(1);

	// Don't output notices like:
	// NOTICE:  relation "phonebook" already exists, skipping
	// see http://stackoverflow.com/a/12504406/1565238
	PQsetNoticeProcessor(conn, processNotice, NULL);

	int server_ver = PQserverVersion(conn);
	char *user = PQuser(conn);
	char *db_name = PQdb(conn);

	printf("Server version: %d\n", server_ver);
	printf("User: %s\n", user);
	printf("Database name: %s\n", db_name);
	//cout << "Server version " << server_ver << endl;

	// same for insert, update, delete, begin, commit ...
	res = PQexec(conn, "CREATE TABLE IF NOT EXISTS goods "
		"(id SERIAL PRIMARY KEY, name VARCHAR(64), "
		"price VARCHAR(64), description TEXT)");

	if (PQresultStatus(res) != PGRES_COMMAND_OK)
		terminate(2);
	clearRes();

	cout << "Passed 2" << endl;
	*/
	//res = PQexec(conn, "DELETE FROM phonebook");
	/*if (PQresultStatus(res) != PGRES_COMMAND_OK)
		terminate(1);
	clearRes();
	
	const char* query =
		"INSERT INTO goods (name, price, description) VALUES ($1, $2, $3);";
	const char* params[2];
	
	for (int i = 0; ; i++)
	{
		const char* name = name_price_dscrptn[i][0];
		const char* price = name_price_dscrptn[i][1];
		//const char* description = name_price_dscrptn[i][2];
		if (name == NULL)
			break;

		params[0] = name;
		params[1] = price;
		//params[2] = description;

		res = PQexecParams(conn, command, 2, NULL, params,
			NULL, NULL, 0);
		if (PQresultStatus(res) != PGRES_COMMAND_OK)
			terminate(1);
		clearRes();
	}

	//тут параметры добавлены
	

	//достаем параметры
	/*
	res = PQexec(conn, "SELECT name, price, description "
		"FROM goods");
	if (PQresultStatus(res) != PGRES_TUPLES_OK) {
		cout << "No select result" << endl;
		terminate(1);
	}

	int ncols = PQnfields(res);
	printf("There are %d columns:", ncols);
	for (int i = 0; i < ncols; i++)
	{
		char *name = PQfname(res, i);
		printf(" %s", name);
	}
	printf("\n");

	int nrows = PQntuples(res);
	for (int i = 0; i < nrows; i++)
	{
		char* name = PQgetvalue(res, i, 0);
		char* price = PQgetvalue(res, i, 1);
		char* description = PQgetvalue(res, i, 2);
		printf("Name: %s, Price: %s, decription: %s\n",
			name, price, description);
	}
	printf("Total: %d rows\n", nrows);

	clearRes();
	terminate(0);*/
	return 0;
}