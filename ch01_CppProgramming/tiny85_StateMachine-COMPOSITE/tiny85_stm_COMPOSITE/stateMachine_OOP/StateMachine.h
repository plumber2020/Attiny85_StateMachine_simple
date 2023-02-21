#pragma once
#include "State.h"

struct StateMachine 
{
    State* initial_state = nullptr;		// Начальное СОСТОЯНИЕ
    State* current_state = nullptr;		// Текущее   СОСТОЯНИЕ

    StateMachine(State* initial);
	
    void start(State* state = nullptr);	// Инициализация СТЕЙТ-машины СОСТОЯНИЕМ (либо по умолчанию)
    void stop();						// Завершение действия СТЕЙТ-машины
    void check_event();					// Проверка актуальности событий переходов
};

