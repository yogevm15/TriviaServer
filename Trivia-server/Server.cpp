#include "Server.h"
void Server::run() {
	m_comunicator.serve(12345);
}
Server::Server() :database(new SqliteDatabase()),handleFactory(database),m_comunicator(this->handleFactory) {

}