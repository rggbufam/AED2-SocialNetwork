#AED2 - SocialNetwork#

###Content###
######* Circular Queue to store all found vertexes######
######* Graph implementation using adjacency matrix######
######* BreadthFirst Search implementation######


### Files ###

####1. main.c####
######The *main.c* file contain a execution of the breadth first search, the entrance is constructed bellow : ######

######**Entrance :**  *argv[] = {vertexes_amount:int,is_ponderable:char,edges_file:char*,vertex_from:int,vertex_to:int}* ######

####2. graph.c####
######The *graph.c* file contain a implementation of a graph using adjacency matrix. The struct contains an offer edge method, a remove edge method, a recover edge method, a print path method (for print the path array got by breadthfirst search) and a print adjacency matrix method.######

####3. circularQueue.c####
######The *circularQueue.c* file contain a implementation of a circular queue using arrays applying properties of circularity within queues. This struct contains an offer method, a peek method, a pop method, a print method and a *isEmpty* method.######

