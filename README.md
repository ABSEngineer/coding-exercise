# Coding Exercise
Coding exercise for Cotronix

### Design 

The inital idea was to build the application to be multi-threaded. This allows the heater to run it's schedule, and accept an updated schedule from direct user input from the console. 

### Assumptions
There were two assumptions: 

- The STDOUT was redirect to a file. This was because, while the task stated you had to use the STDOUT it never stated where the data would land. This also meant, the states output would not clutter the console. 

- When a new schedule was inputted it would switch to the newly updated state, however this can be easily modified. 

### Future Work

Given more time I would:

- Use structs to better encapsulate the heater variables, such as the schedule and threading primitives. This would allow us to spawn multiple heaters should we need.

- Use a CRON expressions or a real time clock to more accurately determine the time   between states.

- I would conduct more tests on the application and neaten some of the comments.

- I would provide a way to better exit out of the application. For example a user could enter 'exit' and it would shutdown the heater.


### Running the application
On windows you'll need to install pthreads, this shouldn't be a problem on linux. Use the command below to complie and run the app.

```
gcc -g -pthread main.c heater.c -o main
```
