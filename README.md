# Resource Allocation Simulation

This repository contains a C++ program for simulating resource allocation among multiple processes. The program utilizes a custom runtime environment to manage processes and their resource usage.

## Overview

The program simulates the execution of multiple processes, each requiring a certain amount of resources. It keeps track of available resources and ensures that processes are allocated resources based on their requirements and availability.

## Features

Process Management: The program manages multiple processes, each with its own name, duration, and resource requirements.
Resource Allocation: Processes are allocated resources based on availability, ensuring that resource constraints are met.
Dynamic Process Generation: Processes can be dynamically generated with random parameters or inputted by the user.
Deadlock Detection: The program detects and handles deadlock situations, where processes cannot proceed due to resource unavailability.
Usage

Compilation: Compile the program using a C++ compiler. For example:  
`g++ -o resource_allocation resource_allocation.cpp`  
Execution: Run the compiled executable.  
bash  
`./resource_allocation`  
Simulation: The program simulates the execution of processes and displays the allocation of resources over time. It runs for a specified number of iterations or until a deadlock is detected.
