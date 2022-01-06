#include "cyoa.hpp"
//detect whether currpage is on the previous path in order to avoid infinite loop
bool isonthepath(std::vector<std::pair<story::Page, std::pair<int, int> > > & pages,
                 int currpagenum,
                 int nextpage) {
  int current = currpagenum;
  while (current != -2) {
    //if find the nextpage number already on the path, return true
    if (current == nextpage) {
      return true;
    }
    //following the existing path and iterate back
    current = pages[current - 1].second.first;
  }
  //if not find, return false
  return false;
}
//extract the path from the vector that stores the
void retracepath(std::vector<std::pair<story::Page, std::pair<int, int> > > & pages,
                 int winpagenum) {
  int current = winpagenum;
  std::vector<std::pair<int, int> > path;
  while (true) {
    path.push_back(std::make_pair(current, pages[current - 1].second.second));
    if (pages[current - 1].second.first <= 0) {
      break;
    }
    current = pages[current - 1].second.first;
  }
  //print path
  while (!path.empty()) {
    if (path.size() == 1) {
      std::cout << path.back().first << "(win)" << std::endl;
    }
    else {
      std::cout << path.back().first << "(" << path[path.size() - 2].second << ")"
                << ",";
    }
    path.pop_back();
  }
}

int main(int argc, char ** argv) {
  assert(argc == 2);
  story story;
  std::string directory(argv[1]);
  //check the validation of whole story
  story.checkstory(directory);
  //creat a vector storing (page, (prev page num, choice))
  std::vector<std::pair<story::Page, std::pair<int, int> > > pages;
  //initialize the vector with all pages and proper initial values
  for (int i = 1;; i++) {
    std::string pagename = directory + "/" + "page" + std::to_string(i) + ".txt";
    try {
      story::Page page(pagename);
      pages.push_back(std::make_pair(page, std::make_pair(-1, -1)));
    }
    catch (std::exception & e) {
      pages[0].second.first = -2;
      break;
    }
  }
  //performing DFS to find all winning path
  std::vector<int> stack;
  stack.push_back(1);
  int current;
  bool findwin = false;
  //repeat pop and pushing nextpages to the stack
  while (!stack.empty()) {
    current = stack.back();
    stack.pop_back();
    std::string pagename = directory + "/" + "page" + std::to_string(current) + ".txt";
    story::Page currpage(pagename);
    std::vector<int> nextpages = currpage.getnextpages();
    //if reach a winpage, retrace the winning path and print it
    if (currpage.iswinpage()) {
      findwin = true;
      retracepath(pages, current);
    }
    else if (nextpages.empty()) {
      continue;
    }
    //for every page, store the previous page and choice leading to that page
    for (size_t i = 0; i < nextpages.size(); i++) {
      //only push the next page to the stack when it is not already on the previous path
      if (isonthepath(pages, current, nextpages[i])) {
        continue;
      }
      pages[nextpages[i] - 1].second.first = current;
      pages[nextpages[i] - 1].second.second = i + 1;
      stack.push_back(nextpages[i]);
    }
  }
  //if already traversed using dfs through the whole tree, print the uwinnable message
  if (!findwin) {
    std::cout << "This story is unwinnable!" << std::endl;
  }

  return EXIT_SUCCESS;
}
