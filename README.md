# README

## Info:

Feel free to use these lines as you wish. These programs load a graph in main memory as (i) a list of edges or (ii) an adjacency array and terminate.

## To compile:

- "gcc edgelist.c -O9 -o edgelist"
- "gcc adjarray.c -O9 -o adjarray"
- "gcc convert.c -O9 -o convert"


## To execute:

- "zcat edgelist.txt | ./edgelist" : load the graph as a list of edges (for undirected or directed graphs)
- "zcat adjarray.txt.gz | ./adjarray" : load the undirected graph as an adjacency array
- "zcat edgelist.txt.gz | ./convert | gzip > adjaray.txt.gz"

## Input Format

n denotes the number of nodes, m the number of edges.

- "edgelist.txt" contains the graph: one edge on each line (two unsigned long (nodes' ID) separated by a space).
- "adjarray.txt" contains the graph: 
  - ligne 1: "n m"
  - then n lines with the degrees of the corresponding node (starting from node 0)
  - then m lines with each edge "u v" (2 unsigned) on each line

## Performance:

Up to 500 million edges on my laptop with 8G of RAM. Takes more or less 1.6G of RAM and 25 seconds (I have an SSD hardrive) for 100M edges.

## Note:

If the graph is directed (and weighted) with selfloops and you want to make it undirected unweighted without selfloops, use the following linux command line.  
awk '{if ($1<$2) print $1" "$2;else if ($2<$1) print $2" "$1}' net.txt | sort -k1,1n -k2,2n | uniq > net2.txt

## Initial contributors

Maximilien Danisch  
Mars 2021  
http://bit.ly/danisch  
maximilien.danisch@gmail.com

