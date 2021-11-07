# Philosophers

This project is about learning the basics of threading a process, making threads and discovering the mutex.

• One or more philosophers are sitting at a round table  with a large bowl of spaghetti in the center, either eating, either thinking,
either sleeping. While they are eating, they do not think or sleep; while thinking
they don’t eat or sleep; and, of course, while sleeping, they do not eat or think.
(Each philosopher should be a thread)

• There are some forks on the table. Serving and eating spaghetti with a single fork
is very inconvenient, so the philosophers will eat with two forks, one for each hand.
(To avoid philosophers duplicating forks, you should protect the forks state with a
mutex for each of them.)

• The program should take the following arguments: 
number_of_philosophers 
time_to_die
time_to_eat 
time_to_sleep 
[number_of_times_each_philosopher_must_eat]
( if a philosopher doesn’t start eating ’time_to_die’
milliseconds after starting their last meal or the beginning of the simulation,
it dies)

• Any change of status of a philosopher must be written as follows (with X replaced
with the philosopher number and timestamp_in_ms the current timestamp in milliseconds):

◦ timestamp_in_ms X has taken a fork
◦ timestamp_in_ms X is eating
◦ timestamp_in_ms X is sleeping
◦ timestamp_in_ms X is thinking
◦ timestamp_in_ms X died
