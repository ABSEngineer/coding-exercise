#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <pthread.h>
#include <string.h>
#include <fcntl.h>
#include "heater.h"

/**
 * We define our the constant states and sleep time (in seconds)
*/
const char SCHEDULE_ON_STATE = '1';
const char SCHEDULE_OFF_STATE = '0';
const int SCHEDULE_SLEEP_TIME = 1800;
const int SCHEDULE_LENGTH = 48;

/**
 * We'll create on schedule for now, and push it into a struct laterr
*/
pthread_t SCHEDULE_THREAD_ID;
pthread_mutex_t SCHEDULE_THREAD_LOCK;
pthread_cond_t SCHEDULE_WAKEUP_COND;
char* current_schedule;


/**
 * The purpose of this function is to start the heater
*/
bool start(const char* schedule, const size_t schedule_len) { 


    /** We create a thread lock to handle the schedule. */
    const int thread_lock_init_error = pthread_mutex_init(&SCHEDULE_THREAD_LOCK, NULL);
    if (thread_lock_init_error) {
        return false;
    }

    /** We need a condition to wake up the heater */
    const int thread_cond_error = pthread_cond_init(&SCHEDULE_WAKEUP_COND, NULL);
    if (thread_cond_error) {
        return false;
    }

    /** We'll copy the schedule for a better mem safety */
    current_schedule = (char*)calloc(schedule_len, sizeof(char));
    if (current_schedule == NULL) {
        return false;

    } else {
        memcpy(current_schedule, schedule, schedule_len);

    }
    
    /** Then we'll spawn the heater */
    const int thread_creation_error = pthread_create(&SCHEDULE_THREAD_ID, NULL, &output, NULL);
    if (thread_creation_error) {
        return false;
    }
    

    return true; 
    
}

/**
 * The purpose of this function is to stop the heater
*/
bool stop() {    

    pthread_mutex_lock(&SCHEDULE_THREAD_LOCK);
    free(current_schedule);
    current_schedule = NULL;
    pthread_mutex_unlock(&SCHEDULE_THREAD_LOCK);
    return true;
    
}

/**
 * The purpose of this function is to return if the heater has started
*/
bool has_started() { 

    /* We can use the null of the schedule to decide if the heater has stopped.... */
    return !(current_schedule == NULL); 
}

/**
 * This purpose of this method is to output the state of the heater
*/
void* output() {     
    

    pthread_mutex_lock(&SCHEDULE_THREAD_LOCK);

    /** We can redirect the stdout to a file so it doesn't clutter the console */
    int output_stream = open("output.txt", O_WRONLY | O_CREAT, 0777);
    if (output_stream == -1) {
        fprintf(stderr, "Error: Output stream could not be created\n");
    }

    /* We dup the stream and push to a file */
    dup2(output_stream, STDOUT_FILENO);
    close(output_stream);

    /** We use the schedule being null to return from the thread */
    int schedule_index = 0;
    while (current_schedule != NULL) {

        if (current_schedule[schedule_index] == SCHEDULE_ON_STATE) {
            fprintf(stdout, "ON\n");

        } else if (current_schedule[schedule_index] == SCHEDULE_OFF_STATE) {
            fprintf(stdout, "OFF\n");

        } else {
            fprintf(stderr, "Error: State not valid\n");

        }

        /* The push the out to the file via flush */
        fflush(stdout);

        /** We want to zero the index should it reach the end of the schedule (i.e reset it) */
        if (schedule_index >= SCHEDULE_LENGTH - 1) {
            schedule_index = 0;

        } else {
            schedule_index = schedule_index + 1;

        }
        
        // We do a timed wait
        struct timespec ts;
        ts.tv_sec = time(NULL) + SCHEDULE_SLEEP_TIME;
        pthread_cond_timedwait(&SCHEDULE_WAKEUP_COND, &SCHEDULE_THREAD_LOCK, &ts);


    }


    pthread_mutex_unlock(&SCHEDULE_THREAD_LOCK); 
    
}


/**
 * The purpose of this function is to update the heaters schedule
*/
bool update_schedule(const char* new_schedule, const size_t schedule_len) { 
    

    pthread_mutex_lock(&SCHEDULE_THREAD_LOCK);

    /** We free the current schedule */
    free(current_schedule);
    current_schedule = NULL;

    /** We recreate the schedule via a copy */
    current_schedule = (char*)calloc(schedule_len, sizeof(char));
    memcpy(current_schedule, new_schedule, schedule_len);

    /** We want to pass a signal to the heater to wake up. This way it should accept a new schedule (Hopefully.. ) */
    pthread_mutex_unlock(&SCHEDULE_THREAD_LOCK);
    //pthread_cond_signal(&SCHEDULE_WAKEUP_COND);


    return true;
    
}

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
