#pragma once
#include "compiler.h"
#include "Connection.h"

using state_handler = void (*)();


struct StateMachine;

struct State
{	
	struct ConnectionBuffer { Connection** buff;		// ��������� �� ����� ������ ���������
							  uint16_t SIZE;			// ������ ������ ������ ���������
							};
		
	struct StateMachineNode { StateMachine *upper_stm;	// ��������� � ���������� ������� �����-������ 
							  StateMachine *inner_stm;	// ��������� � ���������� ������ �����-������ (����������)
							};
		
	struct StateFuncHandler { state_handler	in;			// ���������� ����� � ���������
							  state_handler	out;		// ���������� ������ �� ���������
							};

	uint16_t			stateID = {};					// ������������� ���������
	ConnectionBuffer	connections = {};				// ��������� ������ ���������
	StateMachineNode	stm_node = {};					// ��������� �����-������ 
	StateFuncHandler	handlers = {};					// ��������� ������������ �����-������ ��� ���������
	
	State() = delete;
	State(State const&) = delete;
	State& operator=(State const&) = delete;
	
	State(uint16_t);
	
	void set_function(state_handler in, state_handler out);
	void set_connections(Connection** array, uint16_t size);
	void set_upper_stm(StateMachine* stm);
	void set_inner_stm(StateMachine* stm);
};
