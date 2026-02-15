Examples and experiments on C++, including multithreading

<h4>Strongly Connected Components</h4>
Some data on SCC example:

same test case random data
single thread: Total runtime: 2.09907 seconds
16 thread: Total runtime: 0.347148 seconds

different test cases
single thread: Total runtime: 2.10117 seconds
16 threads: Total runtime: 0.354872 seconds


<h4>Treiber Stack with Shared Pointers</h4>
cpu thread limit:16
spawn a thread for each job: 12.5922
Batching 10 jobs per thread: 2.3009

<h4>Treiber Stack with Hazard Pointers</h4>
cpu thread limit:16
test scenario: each thread runs a loop 1e4 times on Treiber Stack with Shared Pointers and Treiber Stack with Hazard Pointers and Time to run(in milliseconds) each Program is as Follows:
<br>
Treiber Stack with Shared Pointers: 625.785 <br>
Treiber Stack with Hazard Pointers: 52.0765

Todo: Implement Hazard Pointer in Treiber stack(done) and Lock free queue
Todo: Implement Multithreading in Tree structure
Todo: update Vector implementation to add functionalities



