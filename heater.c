#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "heater.h"

/**
 * We define our the constant states and sleep time (in seconds)
*/
const char SCHEDULE_ON_STATE = '1';
const char SCHEDULE_OFF_STATE = '0';
const int SCHEDULE_SLEEP_TIME = 2;
const int SCHEDULE_LENGTH = 2;


/**
 * The purpose of this function is to start the heater
*/
bool start(const char* schedule, const size_t schedule_len) { return true; }

/**
 * The purpose of this function is to stop the heater
*/
bool stop() { return true; }

/**
 * The purpose of this function is to return if the heater has started
*/
bool has_started() { return true; }

/**
 * This purpose of this method is to output the state of the heater
*/
void* output() { return NULL; }

/**
 * The purpose of this function is to update the heaters schedule
*/
bool update_schedule(const char* schedule, const size_t schedule_len) { return true; }

/**
 * The purpose of this method is to validate the updated schedule
*/
bool validate_schedule(const char* schedule, const size_t schedule_size, const size_t actual_size) {

    bool valid_size = validate_schedule_size(schedule_size, actual_size);
    bool valid_states = validate_schedule_states(schedule, schedule_size);
    return (valid_size == true && valid_states == true);

}


/**
 * The purpose of this method is to validate the size of the schedule
*/
bool validate_schedule_size(const size_t expected_size, const size_t actual_size) {
    return (expected_size == actual_size);
}


/**
 * The purpose of this method is to validate the states of the schedule
*/
bool validate_schedule_states(const char* schedule, const size_t schedule_size) {


    bool valid = true;
    for (int index = 0; index < schedule_size - 1; index++) {

        const char schedule_character = schedule[index];
        if (schedule_character != SCHEDULE_ON_STATE && schedule_character != SCHEDULE_OFF_STATE) {
            valid = false;
            break;
        }

    }

    return valid;

}
