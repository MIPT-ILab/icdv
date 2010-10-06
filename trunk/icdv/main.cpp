#include <QtGui/QApplication>
#include <QtGui/QMainWindow>

#include "Graph\predecls.h"
#include "Deriv.h"

/**
 * Create a graph and call some of its methods.
 */
void Test_Graph()
{
	printf("\nBase graph test started..\n");

	Graph g;
	int num = 10;
	pNode *p = new pNode[num];
	for(int i = 0; i < num; i++) {
		p[i] = g.AddNode();
	}
	for(int i = 0; i < num-1; i++) {
		g.AddEdge(p[i], p[i+1]);
	}
	for(int i = 2; i < num; i+=3) {
		g.AddEdge(p[i], p[i-2]);
	}
	g.Dump();

	g.DeleteNode(p[5]);
	g.DeleteNode(p[7]);
	g.DeleteEdge(p[3],p[4]);
	g.Dump();
	g.Destroy();
	delete []p;
	printf("Base graph test passed!\n");
}

void Test_QT(int argc, char** argv)
{
	printf("\nQT test started..\n");
	QApplication app( argc, argv);
	QMainWindow mw;
	mw.show();
	app.exec();
	printf("QT test passed!\n");
}

/**
 * Main function
 */
int main(int argc, char **argv)
{
	// Test base graph
	Test_Graph();

	// Test derived graph
	Derivation_Example();

	// Test QT
	Test_QT(argc,argv);

	return 0;
}
