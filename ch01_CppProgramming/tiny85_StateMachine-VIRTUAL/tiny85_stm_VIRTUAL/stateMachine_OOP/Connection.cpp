#include "Connection.h"

Connection::Connection(Transaction* trans, State* to) :
	trans(trans), to_State(to)
{
}