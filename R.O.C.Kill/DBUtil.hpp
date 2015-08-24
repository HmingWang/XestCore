//#include<iostream>
//#include<libpq-fe.h>
//
//class DBUtil
//{
//private:
//	PGconn *conn;
//public:
//	/* Establish connection to database */
//	PGconn *Connect()
//	{
//		PGconn *conn = NULL;
//
//		// Make a connection to the database
//		conn = PQconnectdb("user=postgres password=1122 dbname=GameDB hostaddr=127.0.0.1 port=5432");
//
//		// Check to see that the backend connection was successfully made 
//		if (PQstatus(conn) != CONNECTION_OK)
//		{
//			printf("Connection to database failed");
//			Close(conn);
//		}
//
//		printf("Connection to database - OK\n");
//
//		return conn;
//	}
//	void Close(PGconn *conn)
//	{
//		PQfinish(conn);
//		getchar();
//		exit(1);
//	}
//};