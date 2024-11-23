IPC with Semaphores and Shared Memory

Overview
This project demonstrates Inter-Process Communication (IPC) in a multi-process environment using semaphores for synchronization and shared memory for data exchange. It simulates a real-world banking scenario where multiple processes interact to manage a shared bank account in a synchronized and controlled manner.

The project is designed to highlight key software engineering concepts such as concurrency, process synchronization, and resource sharing, making it a strong addition to any portfolio.

What the Program Does
The program simulates a scenario where parents (Dear Old Dad and Lovable Mom) and children (Poor Students) interact to manage a shared bank account:

Parent Processes:
Dear Old Dad:

Periodically checks the bank account balance.
Deposits money if the balance is below a threshold and funds are available.
Logs actions like deposits or decisions not to deposit.
Lovable Mom:

Also monitors the account balance.
Deposits money based on her own logic when the balance is low.
Ensures the shared account remains functional and logs every action.
Child Processes:
Each student:
Checks the bank account balance.
Determines how much money they need to withdraw.
Withdraws the requested amount if sufficient funds are available, or logs that funds were insufficient.
Shared Memory:
The bank account balance is stored in shared memory, allowing all processes to access and modify it.
Shared memory ensures real-time updates that all processes can observe.
Semaphores:
A semaphore ensures mutual exclusion, so only one process can access the shared memory at a time.
Prevents race conditions and guarantees consistency of the bank account balance.
Synchronization:
Parent and child processes alternate their access to the shared memory using synchronization mechanisms, ensuring orderly interaction.
Key Features
Inter-Process Communication (IPC):
Uses shared memory to allow multiple processes to communicate and share a single resource.
Concurrency Control:
Implements semaphore-based synchronization to manage access to shared memory and ensure data integrity.
Real-World Use Case Simulation:
Models practical scenarios like fund deposits, withdrawals, and resource contention between multiple users.
Multi-Process Interaction:
Showcases how parent and child processes behave under shared resource constraints.
Why This Project Matters
This project highlights key software engineering and operating system principles, making it valuable for:

Teaching process synchronization using semaphores.
Understanding shared memory as an IPC mechanism.
Practicing multi-process communication in a Linux/UNIX environment.
Modeling concurrency challenges found in real-world applications.
Getting Started
Follow the steps below to set up and run the project.

Command Line Access and Running the Program
This project is terminal-based and requires a Linux/UNIX environment. The following commands will help you compile and execute the code.

Step 1: Compile the Program
Copy code:
gcc -o ipc_project ipc_project.c
Step 2: Run the Program
Copy code:
./ipc_project <num_parents> <num_children>
Replace <num_parents> with the number of parent processes (e.g., 1 or 2).
Replace <num_children> with the number of child processes (e.g., 1 or more).
Step 3: Observe the Output
The program logs interactions between the parents and children, including deposits, withdrawals, and balance checks.

Development Tools
This project is designed to run on Codio or other development environments, leveraging tools such as:

Integrated Terminal Access: Allows you to compile and run the program directly within the IDE.
Debugger: Use a visual debugger to analyze the program's behavior, step through code, and debug semaphore synchronization issues.
Version Control Integration: Built-in Git support for managing project versions and pushing updates to GitHub.
To understand the basics of debugging and error resolution in programming, the resource below is highly recommended:

LaunchCode Debugging Exercises:
Learn the fundamentals of debugging, including techniques to identify, analyze, and fix errors effectively. These skills are essential for maintaining and improving projects like this one.

References and Citations
To better understand the underlying concepts and extend this project, the following resources are highly recommended:

"Operating System Concepts" by Silberschatz, Galvin, and Gagne:

A comprehensive guide to operating system principles, covering semaphores, shared memory, and process synchronization.
"Modern Operating Systems" by Andrew S. Tanenbaum:

A practical exploration of process communication and concurrency challenges.
Linux Manual Pages:

shmget: For shared memory allocation.
semget: For creating semaphores.
fork: For creating child processes.
GeeksforGeeks - IPC Mechanisms in C:

A hands-on guide to shared memory and semaphores. GeeksforGeeks IPC Tutorial
Khan Academy Programming Basics:

Foundational programming courses for beginners. Khan Academy Programming(https://www.khanacademy.org/)
LaunchCode Debugging Exercises:
Exercises that build core debugging skills. LaunchCode Debugging

Future Enhancements
This project can be further enhanced by:

Implementing semaphore-based signaling to replace busy-waiting.
Introducing logging to an external file for better traceability.
Creating a graphical interface to visualize transactions.
Author
Russell Langham Jr
