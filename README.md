# Multithreaded-Server

A client-server model which processes the request one by one does not seem good to the user as the time delay for each request to be processed will be large.

## Aim
Multiple users(clients) may want to access some information from the server. All of them may simultaneously request the resources from the server. For better user experience the server needs to be more responsive that is it should be able to process as many requests as possible.Multithreading is the concept of using multiple threads to execute concurrently. In order to make the server more responsive we would assign the requests to different threads, so that the maximum number of requests can be processed concurrently. 

### Learnings :
- How to pass and receive arguments using pthreads.
- Use of mutex with threads.
- Understand the working of a simple server.
- Implement a simple server using the socket library. The server would read a file and display the number of bytes in the file.
- Understand how the client makes a connection to the server and asks it to perform the job by passing required instructions.
- Implement the client using a Ruby script and understand the working. 
- Understanding multithreaded servers and their advantages over simple servers.
- Implementing threads in our servers to make it more efficient
- Discussing all the problems involved with implementing threads on the server
- Understanding the various solutions to the issues discussed.
