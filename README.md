# Producer-Consumer Problem

## Overview
This project implements the classic Producer-Consumer problem using C in a Linux environment. The producer generates items and puts them on a shared table, while the consumer picks up the items from the table. The table has a capacity of two items, and semaphores are used to synchronize the producer and consumer threads, ensuring mutual exclusion when accessing shared resources.

## Requirements
- C/C++ programming language
- Linux/Unix environment (can be set up using VirtualBox on non-Linux systems)
- POSIX Threads (`pthread`)
- POSIX Semaphores (`semaphore.h`)
- A C compiler (e.g., GCC)

## Installation
1. Clone this repository:
   ```bash
   git clone <repository-url>
   cd <repository-folder>
