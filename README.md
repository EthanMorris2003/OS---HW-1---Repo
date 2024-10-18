Operating-Systems Assignment 1 

Programming Assignment #1

In this programming assignment, you must provide the source codes, documents, and examples in detail on Github. They will be counted for the final score. Please submit the link to the project on Github.

Requirements:

You are required to use C/C++ in Linux/Unix. You can consider installing VirtualBox in your non-Linux environment.
Programs must succeed in compilation and execution as required (80 points)
Readme, documentation and example are required (20 points).

Topic: Producer-Consumer Problem

The producer generates items and puts items onto the table. The consumer will pick up items. The table can only hold two items at the same time. When the table is complete, the producer will wait. When there are no items, the consumer will wait. We use semaphores to synchronize producer and consumer. Mutual exclusion should be considered. We use threads in the producer program and consumer program. Shared memory is used for the “table”.

We expect to use these two programs (producer and consumer) like this:

$ gcc producer.c -pthread -lrt -o producer

$ gcc consumer.c -pthread -lrt -o consumer

$ ./producer & ./consumer &
