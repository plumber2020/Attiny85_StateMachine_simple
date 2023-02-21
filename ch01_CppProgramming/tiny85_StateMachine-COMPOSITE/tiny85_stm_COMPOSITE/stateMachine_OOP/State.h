#pragma once
#include "compiler.h"
#include "Connection.h"

using state_handler = void (*)();


struct StateMachine;

struct State
{	
	struct ConnectionBuffer { Connection** buff;		// Указатель на Буфер СВЯЗЕЙ СОСТОЯНИЯ
							  uint16_t SIZE;			// Размер буфера связей СОСТОЯНИЯ
							};
		
	struct StateMachineNode { StateMachine *upper_stm;	// Связанная с состоянием ВЕРХНЯЯ СТЕЙТ-Машины 
							  StateMachine *inner_stm;	// Связанная с состоянием НИЖНЯЯ СТЕЙТ-Машины (внутренняя)
							};
		
	struct StateFuncHandler { state_handler	in;			// Обработчик ВХОДА в СОСТОЯНИЕ
							  state_handler	out;		// Обработчик ВЫХОДА из СОСТОЯНИЯ
							};

	uint16_t			stateID = {};					// Идентификатор СОСТОЯНИЯ
	ConnectionBuffer	connections = {};				// Структура связей СОСТОЯНИЯ
	StateMachineNode	stm_node = {};					// Связанные СТЕЙТ-Машины 
	StateFuncHandler	handlers = {};					// Структура обработчиков входа-выхода для СОСТОЯНИЯ
	
	State() = delete;
	State(State const&) = delete;
	State& operator=(State const&) = delete;
	
	State(uint16_t);
	
	void set_function(state_handler in, state_handler out);
	void set_connections(Connection** array, uint16_t size);
	void set_upper_stm(StateMachine* stm);
	void set_inner_stm(StateMachine* stm);
};
