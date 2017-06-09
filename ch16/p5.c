/*
In the program in Figure 16.18, the server waits for the child to execute the
`uptime` command and exit before accepting the next connect request.
Redesign the server so that the time to service one request doesn't delay
the processing of incoming connect requests.
*/