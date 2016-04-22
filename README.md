The Chord system is a structured peer-to-peer network architecture realizing a scalable distributed hash table. In
Chord, the peers are organized as a ring. A position within Chord which is held by a computing node is called an
index node or simply a peer. Each index node has a finger table and, in addition, holds data items associated with
its own key value and any other data items associated with keys larger than the previous index node in the Chord
ring.

To succeed with this programming task, you will need to fully understand the Chord system! Do not commence
the programming task until you have developed a solid understanding of the Chord system. You may need
to study the lecture notes, the relevant paragraphs in the text book, and relevant internet sources in order to
acquire the level of understanding of CHORD required for this assignment. Commence the work on this
assignment once you are confident to have understood how CHORD works.

Your task is to write a simulation of the Chord system on a single computer as a single (non-parallelized, not
multi-threaded) process. We will keep this task as simple as possible. The main objectives are:

	• to understand how the nodes in Chord communicate.
	• to understand how nodes are managed (added/removed) from the system.
	• to understand the effects of adding and removal of index nodes.
	• to understand how the finger table is computed and maintained.
	• to understand how memory utilization and data distribution takes place in Chord.
	• to understand how searching is done efficiently in Chord.
	• To understand why CHORD is a such a fast and efficient algorithm.
	• to understand the concept of scalable algorithms and fast code.
	
To keep the task as simple as possible, you are to write a single-threaded simulation (i.e. no additional threads
are to be created during runtime). Follow the following guidelines:

Develop data structures which are suitable to hold required information for each peer in a CHORD system. Note
that index nodes can hold (and access) local information only (I.e, an index nodes never knows of all the other
index nodes in a CHORD). Remember that your implementation is to simulate a distributed system.

Thus, do not make use of any global variables!

On the basis of the data structures developed by you, write a single threaded (single process) simulation in either
C, C++, or Java of the Chord system with the following functions (this is the minimum requirement). You may
introduce any number of functions in addition to those stated here 1:

InitChord(n,...): Create and initialize a new Chord system of size 2n. You can assume that the parameter
n is a positive valued integer whose value is limited to 1 ≤ n ≤ 32. Thus, the smallest CHORD that can be created
by this function is of size 2, and the largest CHORD is 232. Note that in general the size of a Chord is much larger
than the number of available index nodes. An example: The CHORD shown in the lecture notes “Architectures”
was of size 24 but consisted of only 5 peers.

This function will also print your name and student number to the screen (print to standard output). Normally, in
a real world CHORD, when a new CHORD is created than there will be at least one index node (the node which
created the CHORD will become the first index node in the system), and the new node would assume a random
location within CHORD. We will simulate this by creating a new index node at location 0 (zero) within the ring
as part of this InitChord(.) function. The size of the finger table for this peer (and any other peer that may
be added later) is equal to n.


If InitChord(.) is called more than once (i.e. when there is already a Chord when InitChord is called again)
then this function will completely remove the previous CHORD from memory then initialize a new Chord
system. The removing of a pre-existing CHORD requires the removal of all its associated peers from the system
and the release of all allocated memory (in case of a C or C++ implementation).
The value of parameter n is obtained from a script file (see example below).


AddPeer(ID, ...): Adds one new peer (an index node) to your Chord system. The ID (a positive integer
value) of the new peer is provided, and can be assumed to be a value within [0; 2n-1]. You will need to create a
finger table of appropriate size (of size n) for this new index node. Optional: you may also decide to associate a
key-list to this Chord. A key-list is a list of IDs which are in-between the current index and the previous index
node as was described in the textbook (see the section on Architectures). However, this is optional as it is
possible to implement an efficient and functional CHORD without this key-list. The value for ID is obtained
from a script file (see example below). If the addition of the peer was successful then this function prints to the
screen (standard output) the following: “PEER <ID> ADDED”, where <ID> is the ID of the peer just inserted.
Note: The addition of a new peer can require an update of the finger table of some of the other index nodes. This
is a very important aspect in Chord!

RemovePeer(ID, ...): Removes a given peer from Chord, associates any data items that this peer held
with the correct peer in the remaining CHORD, and appropriately updates the finger tables of the remaining
peers. This function removes this peer completely. You will need to think about how the removal of an index
node affects (the finger table, data items, etc) of the other remaining index nodes. If the removal of a peer was
successful then this function prints to the screen “PEER <ID> REMOVED”. If this function causes the removal
of the last remaining peer in the Chord, then all data items are lost (memory freed), and the program is to print
“Last of the peers removed. CHORD terminated”, then your program is to exit.

FindKey(key, ...): This function searches for the peer responsible for the given (hash-) key. This search
function must use the finger tables of the peers as described in the lectures and the text book. Follow the
algorithm as is described in the book (and illustrated in Figure 5-4) to locate the peer that is responsible for the
key. The function prints to standard output the IDs of the peers visited separated by the '>' symbol and a newline
character at the end. For example, if a peer with ID = 1 initiated a search and the IDs of the peers visited during
the search was 7,12 then this function will print 1>7>12

1 Note: Functions which have three dots in their parameter list may accept any number of additional parameters. For
example, the function Init(n, …), this function will accept the parameter n as well as any other parameter that you may
wish to pass to this function.

Hash(string): Computes a hash key for a given data item. You can assume that the data item is a nullterminated
string. The function returns a key value which is an integer within [0;2n). The algorithm that must be
used for this function is shown at the end of this assignment.

Insert(string, ...): This function simulates that an index node inserts a data item into the Chord. The
data item is given as a string parameter. The peer will call the function Hash(string) to compute the
associated hash-key. The string is then to be stored at the index node that is responsible for the computed key
value. Note that the FindKey() function may need to be called in order to locate the node responsible for this
data item. Once found, the peer that is responsible for this data item is to store the data item. Note that the data
item is stored in a part of the memory that is only accessible by the targeted peer. Note also that this means that a
peer may have to store more than one data value. This function will print to the screen the string “INSERTED
<string> (key=<key_value>) AT “ followed by the ID value of the peer at which the data item is stored.

Delete(string, ...): This function simulates that an index node requests the removal of a data item
identified by the parameter string from the Chord. You can again assume that the data item is given as a string
parameter. Similar as before, this function uses the hash function to compute the associated key value, then
FindKey(.) to compute the peer responsible for the data item, then removes the string from the memory of that
peer. If successful, this function will print to the screen: “REMOVED <string> (key=<key_value>) FROM “
followed by the ID value of the peer from which the string was removed.
Print(key, ...): This function will print information about the peer that is responsible for the given key.
Thus, the function may need to call FindKey() in order to find the peer that is responsible for key value. Once
found, the target peer will then print “DATA AT NODE <MYID:>”, where <MYID> is the ID of the peer,
followed by a newline, then followed by the list of all data items (strings) stored at this node (separated by a
newline), followed by the string “FINGER TABLE OF NODE <MYID>”, a newline, and the content of the
finger table of node “MYID”.
Read(filename): Reads a set of instructions from a given text file. The file contains one instruction per
line. Anything after a hash '#' symbol is to be treated as comment and is to be ignored. The instructions are
named analogous to the functions which need to be called. For example, a file may contain the following list of
instructions:
initchord 5 #Create a CHORD of size 32
addpeer 7 #Add a new peer whose ID is to be 7
addpeer 3 #Add peer 3...
removepeer 3 #...and remove it again
addpeer 12
addpeer 3
addpeer 9
removepeer 3
addpeer 17
insert THIS IS A TEST
insert Markus Hagenbuchner
insert CSCI319
print 12
delete THIS IS A TEST
print 12
removepeer 0
print 7
print 9
print 12
print 17
When compiled, the program should be executed at a command line and accept the file name of a file containing
the instructions. Assuming that the compiled code is named CHORD, and assume that the file myfile.dat
contains instructions (in the format as was shown before), then the program should be able to run by issuing the
following command line instruction:
./CHORD myfile.dat
this would execute all instructions within the myfile.dat. There is one instruction per line in myfile.dat.
Instructions not recognized by your program should be ignored quietly (i.e. no error message). Do not assume a
maximum file size for the file that contains the instructions. In other words, the file may contain any arbitrary
number of instructions.
A sample output of the chord for the example shown above is given in Attachment 3 below.
Note0: There is no node other than index nodes (the peers) in a CHORD. Thus, there is no master node or
supernode. This also means that any activity within a CHORD must be initiated by one of the index nodes in the
CHORD. An exception is the function Read which is to be invoked by the main routine of your implementation.
All other functions such as AddPeer, RemovePeer, FindKey, Hash, Insert, Delete, and Print must be invoked by a
(one) peer of the CHORD. When inintiating any one of these activities you are permitted to either:
a.) select a peer at random
b.) select the first peer in the CHORD (Peer with the lowest ID)
c.) select the last peer (peer with the highest ID)
The example shown in Attachment 3 assumes that strategy b (select the peer with the lowest ID) is taken. The
activity “addpeer 7” in the 2nd line of the script above would hence be invoked by peer ID=0 since this is the
peer with the lowest ID in the CHORD at the time of processing this activity.
Note1: Any of the functions mentioned above may accept any parameters in addition to the one specified, and
may return a value of your choosing.
Note2: The task is not to implement a full Chord system. There is no need to produce a multi-threaded
implementation. The aim is to:
1.) Simulate basic concepts of Chord. In particular, a deeper understanding to searching withing Chord, and
the maintenance of index nodes is to be obtained.
2.) Develop an appreciation of mechanisms required for maintaining index tables.
3.) Understand the impact of the size of an index table, and the number of index nodes on the efficiency of
the chord system.
Note 3: Your code will be compiled and marked using gcc, g++, or java as available within Ubuntu on the lab
computers for this subject. Ensure that your code compiles and runs within the UNIX environment used in the
computer lab. The correctness, functionality, and efficiency of your program will be marked. Ensure that
your code is scalable with respect to the size of the CHORD, number of index nodes, number of data items
stored. The code itself is being verified to contain your own work, and that it complies with the given task
specifications, but is otherwise not marked. We will use our own scripts to test your program. Do not submit
your own script file(s).
Note 4: While the code will not be marked, the lecturer and the tutors will look at the code very carefully in
order to identify whether the task was addressed correctly. Remember that the task is to simulate Chord. This
also means that no single peer has complete information. For example, this means that a search needs to be
carried out when inserting or removing a peer from Chord. We will look at the efficiency of your code.
Note 5: Your code is not to produce outputs other than those specified above. This means that you do not print to
stdout, stderr, or any other output stream any debugging information, or any other information not required by
this assignment. A violation to this will attract penalty marks!
Note 6: The correctness and speed (the efficiency) of your implementation will influence the marks that you can
earn for this task.
Note 7: We will test your code on the ability to efficiently handle possibly large amounts of peers and possibly
large amount of data items. We will test the correctness of the finger tables and the correct storage location of
any data item stored in the Chord.
Hint: What if there are only few peers in the Chord but a lot of data items that need to be stored? Think about
how to maintain the speed of adding/removing data items even if the number of peers is limited.