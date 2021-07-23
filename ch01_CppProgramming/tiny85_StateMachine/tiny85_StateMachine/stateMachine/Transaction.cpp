#include "Transaction.h"

Transaction::Transaction(const char* name, condition_func cond, action_func act) :
	_name(name), _cond(cond), _act(act)
{
}
