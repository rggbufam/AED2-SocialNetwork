# AED2 - SocialNetwork

### [Content]
###### * Circular Queue to store all found vertexes
###### * Graph implementation using adjacency matrix
###### * BreadthFirst Search implementation
###### * Brand BreadthFirstSearch mitigation for low memory
###### * All-to-all pathfinding


### [Files]

##### 1. main.c
###### The *main.c* file contains an execution of the breadth first search from each vertex to each vertex (All-to-all pathfinding), the entrance is constructed bellow :

###### *Entrance :  argv[] = {vertexes_amount:int,is_ponderable:char,edges_file:char[]}*

##### 2. graph.c
###### The *graph.c* file contains an implementation of a graph using adjacency matrix. The struct contains an offer edge method, a remove edge method, a recover edge method, a print path method (for print the path array got by breadthfirst search) and a print adjacency matrix method.

##### 3. circularQueue.c
###### The *circularQueue.c* file contains an implementation of a circular queue using arrays applying properties of circularity within queues. This struct contains an offer method, a peek method, a pop method, a print method and a *isEmpty* method.

##### 3. darray.c
###### The *darray.c* file contains an implementation of a Dynamic Array structure, it receives a number in any position, it recovers a number from any position, it's dangerous for careless people because it does not return an error, it just tries to acess a position or expand the array for your use of that position.

### [Contributors]

**String** ***contributors[]*** = {["Ivo Machado"](https://github.com/ivomachado) : "Algorithm implementation ideas", "My sadness" : "implementations", "My sorrow" : "Algorithm ideas", "My juicy orange juice" : "everything else"}
