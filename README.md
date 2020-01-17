# Ex4v2
# Ex4

Ex4 is a shortest path finding server.

## Running

To compile the program you should use the following line:

```bash
g++ -std=c++14 *.cpp -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -o a.out -pthread
```
And then to run:
```bash
./a.out XXXX
```
Please notice that 'XXXX' refers to the port you would like the server to use.
## Usage

Now you can connect as a client and send a matrix as text lines like so:

X,X,X

X,X,X

X,X,X

S,S

E,E

end

X - your matrix;
S - starting point;
E - ending point

The server can handle many clients simultaneously

## GIT
https://github.com/guytiklu/Ex4v2
