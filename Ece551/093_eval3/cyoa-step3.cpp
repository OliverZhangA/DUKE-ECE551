#include "cyoa.hpp"

int main(int argc, char ** argv) {
  //initialize the story object and check the story
  story story;
  assert(argc == 2);
  std::string directory(argv[1]);
  story.checkstory(directory);
  //create a vector named pages holding pairs of page and a int(which is used to store the depth of a page)
  std::vector<std::pair<story::Page, int> > pages;
  //initialze the vector
  for (int i = 1;; i++) {
    std::string pagename = directory + "/" + "page" + std::to_string(i) + ".txt";
    try {
      story::Page page(pagename);
      pages.push_back(std::make_pair(page, -1));
    }
    catch (std::exception & e) {
      pages[0].second = 0;
      break;
    }
  }
  //use queue to perform BFS in order to decide depth of each page
  std::queue<int> pagequeue;
  //push the first page to the stack
  pagequeue.push(1);
  int current;
  //repeat push and pop the page until the queue is empty
  while (!pagequeue.empty()) {
    current = pagequeue.front();
    pagequeue.pop();
    std::string pagename = directory + "/" + "page" + std::to_string(current) + ".txt";
    story::Page currpage(pagename);
    std::vector<int> nextpages = currpage.getnextpages();
    //for all next pages referenced by current page and not yet has a valid depth, update the depth to be current depth + 1
    for (size_t i = 0; i < nextpages.size(); i++) {
      if (pages[nextpages[i] - 1].second == -1) {
        pages[nextpages[i] - 1].second = pages[current - 1].second + 1;
        pagequeue.push(nextpages[i]);
      }
    }
  }
  //print depth of all pages
  for (size_t i = 0; i < pages.size(); i++) {
    if (pages[i].second != -1) {
      std::cout << "Page " << i + 1 << ":" << pages[i].second << std::endl;
    }
    else {
      std::cout << "Page " << i + 1 << " is not reachable" << std::endl;
    }
  }
  // for (size_t i = 0; i < pages.size(); i++) {
  //   if (pages[i].second == -1) {
  //     std::cout << "Page " << i + 1 << " is not reachable" << std::endl;
  //   }
  //}
  return EXIT_SUCCESS;
}
