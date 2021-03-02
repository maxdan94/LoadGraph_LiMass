/*
Maximilien Danisch
Mars 2021
http://bit.ly/danisch
maximilien.danisch@gmail.com

Info:
Feel free to use these lines as you wish. This program loads a graph (directed or undirected) in main memory as a list of edges and terminates.

To compile:
"gcc edgelist.c -O9 -o edgelist".

To execute:
"zcat edgelist.txt.gz | ./edgelist".

"edgelist.txt" should contain the graph: one edge on each line (two unsigned long (nodes' ID)) separated by a space.
*/

#include <stdlib.h>
#include <stdio.h>

#include <time.h>//to estimate the runing time

#include <stdint.h>//to use the types uint32_t andd unint64_t
#include <inttypes.h>

#define NLINKS 100000000 //maximum number of edges for memory allocation, will increase if needed

typedef uint32_t Node;
typedef uint64_t Edge;

typedef struct {
	Node s;
	Node t;
} edge;

//edge list structure:
typedef struct {
	Node n;//number of nodes
	Edge e;//number of edges
	edge *edges;//list of edges
} edgelist;

//compute the maximum of three unsigned long
inline Node max3(Node a,Node b,Node c){
	a=(a>b) ? a : b;
	return (a>c) ? a : c;
}

//reading the edgelist from file
edgelist* read_edgelist(FILE* file){
	Edge e1=NLINKS;

	edgelist *g=malloc(sizeof(edgelist));
	g->n=0;
	g->e=0;
	g->edges=malloc(e1*sizeof(edge));//allocate some RAM to store edges

	while (fscanf(file, "%" SCNu32 " %" SCNu32, &(g->edges[g->e].s), &(g->edges[g->e].t))==2) {
		g->n=max3(g->n,g->edges[g->e].s,g->edges[g->e].t);
		if (++(g->e)==e1) {//increase allocated RAM if needed
			e1+=NLINKS;
			g->edges=realloc(g->edges,e1*sizeof(edge));
		}
	}
	fclose(file);

	g->n++;

	g->edges=realloc(g->edges,g->e*sizeof(edge));

	return g;
}

void free_edgelist(edgelist *g){
	free(g->edges);
	free(g);
}

int main(int argc,char** argv){
	edgelist* g;
	time_t t1,t2;
	t1=time(NULL);

	fprintf(stderr, "Reading edgelist from file\n");
	g=read_edgelist(stdin);

	fprintf(stderr, "Number of nodes: %" SCNu32 "\n",g->n);
	fprintf(stderr, "Number of edges: %" SCNu64 "\n",g->e);

	free_edgelist(g);

	t2=time(NULL);

	fprintf(stderr, "- Overall time = %ldh%ldm%lds\n",(t2-t1)/3600,((t2-t1)%3600)/60,((t2-t1)%60));

	return 0;
}


