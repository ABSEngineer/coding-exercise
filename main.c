/**
 * Started at 13/08/2023 - 20:15PM
*/
#include <stdio.h>
#include <stdlib.h>
#include "heater.h"


int main() {


    while (true) {

         /** We increase the schedule size to include an end of line character */
        size_t input_size = SCHEDULE_LENGTH + 1;

        /* We create a buffer for the new schedule */
        char* new_schedule = (char*)calloc(input_size, sizeof(char));

        /** Next we read the user input */
        fprintf(stdout, "Entered schedule was not valid\n");
        size_t character_count = getline(&new_schedule, &input_size, stdin);

        /** Then we validate the input */
        bool outcome = validate_schedule(new_schedule, SCHEDULE_LENGTH + 1, character_count);
        if (outcome) {

            if (has_started() == false) {
                start(new_schedule, character_count);

            } else {
                update_schedule(new_schedule, character_count);

            }

        } else {
            
            fprintf(stderr, "Entered schedule was not valid\n");

        }

        /** Then we clean up */
        free(new_schedule);
        new_schedule = NULL;

    }
}

