#include "cyoa.hpp"

int main(int argc, char ** argv) {
  assert(argc == 2);
  std::string directory(argv[1]);
  story story;
  //check the validatin of the story pages
  story.checkstory(directory);
  //start playing the story
  story.startthestory(directory);
  return EXIT_SUCCESS;
}
