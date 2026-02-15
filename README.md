Examples and experiments on C++, including multithreading <br>

<h3>Strongly Connected Components</h3>
Some data on SCC example: <br>

same test case random data <br>
single thread: Total runtime: 2.09907 seconds <br>
16 thread: Total runtime: 0.347148 seconds <br>

different test cases <br>
single thread: Total runtime: 2.10117 seconds <br>
16 threads: Total runtime: 0.354872 seconds <br>


<h3>Treiber Stack with Shared Pointers</h3>
cpu thread limit:16 <br>
spawn a thread for each job: 12.5922ms <br>
Batching 10 jobs per thread: 2.3009ms <br>

<h3>Treiber Stack with Hazard Pointers</h3>
cpu thread limit:16 <br>
test scenario: each thread runs a loop 1e4 times on Treiber Stack with Shared Pointers and Treiber Stack with Hazard Pointers and Time to run(in milliseconds) each Program is as Follows: <br>
<b>Treiber Stack with Shared Pointers: 625.785ms </b><br>
<b>Treiber Stack with Hazard Pointers: 52.0765ms </b>

Todo: Implement Hazard Pointer in Treiber stack(done) and Lock free queue <br>
Todo: Implement Multithreading in Tree structure <br>
Todo: update Vector implementation to add functionalities <br>



