/*
Maximilien Danisch
Mars 2021
http://bit.ly/danisch
maximilien.danisch@gmail.com

Info:
Feel free to use these lines as you wish. This program loads a graph in main memory as compact adjacancy arrays.

To compile:
"gcc adjarray.c -O9 -o adjarray".

To execute:
"zcat adjarray.txt.gz | ./adjarray".
*/

#include <stdlib.h>
#include <stdio.h>

#include <time.h>//to estimate the runing time

#include <stdint.h>//to use the types uint32_t andd unint64_t
#include <inttypes.h>


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
	Edge *cd;//cumulative degree cd[0]=0 length=n+1
	Node *adj;//concatenated lists of neighbors of all nodes
} adjarray;

//compute the maximum of three unsigned long
inline Node max3(Node a,Node b,Node c){
	a=(a>b) ? a : b;
	return (a>c) ? a : c;
}

//reading the adjarray from file
adjarray* read_adjarray(FILE* file){
	Node i,u,v;
	Edge j;
	Node *d;
	adjarray *g=malloc(sizeof(adjarray));

	if (fscanf(file,"%" SCNu32 " %" SCNu64, &(g->n), &(g->e))!=2){
		fprintf(stderr,"read error");
	}
	
	g->cd=malloc((g->n+1)*sizeof(Edge));
	g->cd[0]=0;
	for (i=0;i<g->n;i++){
		if (fscanf(file,"%" SCNu64, &(g->cd[i+1]))!=1){
			fprintf(stderr,"read error");
		}
		g->cd[i+1]+=g->cd[i];
	}

	d=calloc(g->n,sizeof(Node));
	g->adj=malloc(2*g->e*sizeof(Node));
	for (j=0;j<g->e;j++){
		if (fscanf(file, "%" SCNu32 " %" SCNu32, &u, &v)!=2){
			fprintf(stderr,"read error");
		}
		g->adj[g->cd[u]+d[u]++]=v;
		g->adj[g->cd[v]+d[v]++]=u;
	}
	free(d);

	return g;
}

//freeing memory
void free_adjarray(adjarray *g){
	free(g->cd);
	free(g->adj);
	free(g);
}

int main(int argc,char** argv){
	adjarray* g;
	time_t t1,t2;

	t1=time(NULL);

	g=read_adjarray(stdin);

	fprintf(stderr,"Number of nodes: %" SCNu32 "\n",g->n);
	fprintf(stderr,"Number of edges: %" SCNu64 "\n",g->e);
	
	free_adjarray(g);

	t2=time(NULL);

	fprintf(stderr,"- Overall time = %ldh%ldm%lds\n",(t2-t1)/3600,((t2-t1)%3600)/60,((t2-t1)%60));

	return 0;
}


