#include <osmium/io/pbf_input.hpp>
#include <osmium/osm/types.hpp>
#include <osmium/visitor.hpp>
#include <osmium/handler.hpp>

#include <boost/coroutine/all.hpp>

#include <cstdint>
#include <cstdio>
#include <cstdlib>


using NodeId = osmium::unsigned_object_id_type;
using Coroutine = boost::coroutines::asymmetric_coroutine<NodeId>;


struct Handler final : osmium::handler::Handler {
  explicit Handler(Coroutine::push_type& sink_) : sink{sink_} {}
  void node(const osmium::Node& node) { sink(node.positive_id()); }
  Coroutine::push_type& sink;
};


int main(int argc, char** argv) try {

  if (argc != 2) {
    std::fprintf(stderr, "Usage: %s in.osm.pbf\n", argv[0]);
    return EXIT_FAILURE;
  }

  const auto entities = osmium::osm_entity_bits::node;
  osmium::io::Reader reader(argv[1], entities);

  Coroutine::pull_type nodeIdGenerator{[&reader](Coroutine::push_type& sink) { //
    Handler handler{sink};
    osmium::apply(reader, handler);
  }};


  // Magic happens here!
  for (const auto nodeId : nodeIdGenerator)
    std::printf("%ju\n", static_cast<std::uintmax_t>(nodeId));

} catch (const std::exception& e) {
  std::fprintf(stderr, "Error: %s\n", e.what());
  return EXIT_FAILURE;
}
