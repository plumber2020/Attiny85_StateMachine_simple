#include "Transaction.h"

Transaction::Transaction(condition_func cond, action_func act) :
	_cond(cond), _act(act)
{
		static unsigned id = 0; _id = id++;
}
