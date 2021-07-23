#include "Connection.h"

Connection::Connection(State* from, Transaction* trans, State* to) :
	_from(from), _trans(trans), _to(to)
{
	++count;
}

unsigned Connection::count = 0;
