#include "cyoa.hpp"
//determine if the target page is on the path
bool isonpath(int target, std::vector<std::pair<int, int> > & path) {
  for (size_t i = 0; i < path.size(); i++) {
    if (path[i].first == target) {
      return true;
    }
  }
  return false;
}
//print path
void printpath(std::vector<std::pair<int, int> > & path) {
  for (size_t i = 0; i < path.size(); i++) {
    if (i == path.size() - 1) {
      std::cout << path[i].first << "(win)" << std::endl;
    }
    else {
      std::cout << path[i].first << "(" << path[i + 1].second << ")"
                << ",";
    }
  }
}
//find win path
void findwinpath(int current,
                 std::vector<std::pair<int, int> > path,
                 std::vector<story::Page> & pages,
                 std::pair<int, int> lpair,
                 bool & findwin) {
  //push the current page onto path
  path.push_back(lpair);
  //if findwin page, print the path
  if (pages[current - 1].iswinpage()) {
    findwin = true;
    printpath(path);
  }
  //for all neighbours of current page, if not already on the path(not forming a cycle), make recursive call according to dfs
  for (size_t i = 0; i < pages[current - 1].getnextpages().size(); i++) {
    if (!isonpath(pages[current - 1].getnextpages()[i], path)) {
      findwinpath(pages[current - 1].getnextpages()[i],
                  path,
                  pages,
                  std::make_pair(pages[current - 1].getnextpages()[i], i + 1),
                  findwin);
    }
  }
}

int main(int argc, char ** argv) {
  assert(argc == 2);
  story story;
  std::string directory(argv[1]);
  //check the validation of whole story
  story.checkstory(directory);
  std::vector<story::Page> pages;
  //initialize the vector with all pages and proper initial values
  for (int i = 1;; i++) {
    std::string pagename = directory + "/" + "page" + std::to_string(i) + ".txt";
    try {
      story::Page page(pagename);
      //pages.push_back(std::make_pair(page, std::make_pair(-1, -1)));
      pages.push_back(page);
    }
    catch (std::exception & e) {
      break;
    }
  }
  std::vector<std::pair<int, int> > path;
  bool findwin = 0;
  //if did not find a win page print the message
  findwinpath(1, path, pages, std::make_pair(1, -1), findwin);
  if (!findwin) {
    std::cout << "This story is unwinnable!" << std::endl;
  }

  return EXIT_SUCCESS;
}
