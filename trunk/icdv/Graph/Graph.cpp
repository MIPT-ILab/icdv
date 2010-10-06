#include "predecls.h"
#include <assert.h>

void Graph::Dump()
{
	list<pNode>::iterator node_iter;
	list<pEdge>::iterator edge_iter;

	printf("Dumping graph\n");
	printf("Nodes:\n");
	for(node_iter = m_nodes_list.begin();
		node_iter !=m_nodes_list.end();
		node_iter++) {
			pNode pn = *node_iter;
			if(pn) {
				pn->Dump();
			}
	}

	printf("Edges:\n");
	for(edge_iter = m_edges_list.begin();
		edge_iter !=m_edges_list.end();
		edge_iter++) {
			pEdge pe = *edge_iter;
			if(pe) {
				pe->Dump();
			}
	}
}

void Graph::FreeNode(pNode p)
{
	assert(p != NULL);
	delete (pNode)p;
}

void Graph::FreeEdge(pEdge p)
{
	assert(p != NULL);
	delete (pEdge)p;
}

void Graph::Destroy()
{
	list<pNode>::iterator node_iter;
	list<pEdge>::iterator edge_iter;

	while(!m_nodes_list.empty()) {
		pNode pn = m_nodes_list.front();
		DeleteNode(pn);
	}
	assert(m_nodes_list.empty());
	assert(m_edges_list.empty());
	assert(m_total_edges_num == 0);
	assert(m_total_nodes_num == 0);
}

pNode Graph::AddNode()
{
	pNode new_node = new Node(this);
	return new_node;
}

pEdge Graph::AddEdge(pNode from, pNode to)
{
	pEdge new_edge = new Edge(from,to);
	return new_edge;
}

void Graph::DeleteNode(pNode p)
{
	while(!p->m_in_edges_list.empty()) {
		DeleteEdge(p->m_in_edges_list.front()->m_from,p);
	}
	while(!p->m_out_edges_list.empty()) {
		DeleteEdge(p,p->m_out_edges_list.front()->m_to);
	}
	m_nodes_list.remove(p);
	m_total_nodes_num--;
	FreeNode(p);
}

bool Graph::DeleteEdge(pNode from, pNode to)
{
	assert(from && from->m_graph == this);
	assert(to   &&   to->m_graph == this);

	list<pEdge>::iterator edge_iter;
	
	for(edge_iter = m_edges_list.begin();
		edge_iter !=m_edges_list.end();
		edge_iter++) {
			pEdge pe = *edge_iter;
			if(pe->m_from == from &&
				pe->m_to   == to) {
					m_edges_list.erase(edge_iter);
					pe->m_from->m_out_edges_list.remove(pe);
					pe->m_to->m_in_edges_list.remove(pe);
					pe->m_from = pe->m_to = NULL;
					m_total_edges_num--;
					FreeEdge(pe);
					return true;
			}
	}
	return false;
}

