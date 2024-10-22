# Producer-Consumer Problem

## Overview
   This project implements the classic Producer-Consumer problem using C in a Linux environment. The producer generates items and puts them on a shared table, while the consumer picks up the items from the table. The table has a capacity of two items, and semaphores are used to synchronize the producer and consumer threads, ensuring mutual exclusion when accessing shared resources.

## 1. Installation
   Clone this repository, then locate the file then in the terminal type the prompts 

## 2. Compile the producer and consumer programs: Enter the Following in the Terminal: 
- gcc producer.c -pthread -o producer
- gcc consumer.c -pthread -o consumer

## 3. Usage
   To run the producer and consumer programs, execute the following command in your terminal:
   ./producer & ./consumer

## 4. Output
   The output in the terminal should look something like the following: 

      Producer produced: 12
      Consumer consumed: 12
      Producer produced: 3
      Consumer consumed: 3
      Producer produced: 69
      Consumer consumed: 69
      ...
   
   This will run in an infite loop as there is no limit to the producer producing and the consumer consuming. 




