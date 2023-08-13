#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "heater.h"


/**
 * The purpose of this function is to start the heater
*/
bool start(const char*, const size_t);

/**
 * The purpose of this function is to stop the heater
*/
bool stop();

/**
 * The purpose of this function is to return if the heater has started
*/
bool has_started();

/**
 * This purpose of this method is to output the state of the heater
*/
void* output();

/**
 * The purpose of this function is to update the heaters schedule
*/
bool update_schedule(const char*, size_t);

/**
 * The purpose of this method is to validate the updated schedule
*/
bool validate_schedule(const char*, const size_t, const size_t);

/**
 * The purpose of this method is to validate the size of the schedule
*/
bool validate_schedule_size(const size_t, const size_t);

/**
 * The purpose of this method is to validate the states of the schedule
*/
bool validate_schedule_states(const char*, size_t);
