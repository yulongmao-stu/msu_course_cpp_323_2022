#include "printing.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

namespace printing {
namespace json {

std::string print_vertex(const Graph::Vertex& vertex, const Graph& graph) {
  std::ostringstream vertex_repr;
  bool is_first = true;
  auto edges_ids_of_vertex = graph.adjacency_list().at(vertex.id());
  vertex_repr << "\n{ \"id\": " << vertex.id() << ", \"edges_ids\": [";
  for (const auto& edge_id : edges_ids_of_vertex) {
      if (!is_first)
        vertex_repr << ", " << edge_id;
      else {
        vertex_repr << edge_id;
        is_first = false;
      }
  }
  vertex_repr << "] }";
  return vertex_repr.str();
}

std::string print_edge(const Graph::Edge& edge) {
  std::ostringstream edge_repr;
  edge_repr << "\n{\"id\": " << edge.id() << ", \"vertex_ids\": ["
            << edge.from_vertex_id() << ", " << edge.to_vertex_id() << "]}";
  return edge_repr.str();
}

std::string print_graph(const Graph& graph) {
  std::string json_string = "{\"vertices\": [";
  bool is_first = true;
  for (const auto& [_, vertex] : graph.vertices()) {
    if (!is_first) {
      json_string.append(", ");
    } else {
      is_first = false;
    }
    json_string.append(print_vertex(vertex, graph));
  }

  json_string.append("],\n\"edges\": [");
  is_first = true;
  for (const auto& [_, edge] : graph.edges()) {
    if (!is_first) {
      json_string.append(", ");
    } else {
      is_first = false;
    }
    json_string.append(print_edge(edge));
  }
  json_string.append("]}\n");
  return json_string;
}
};  // namespace json

};  // namespace printing
