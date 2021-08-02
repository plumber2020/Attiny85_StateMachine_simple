#include "Connection.h"
#include "State.h"

Connection::Connection(Transaction* trans, State* to) :
	_trans(trans), _to(to)
{
}