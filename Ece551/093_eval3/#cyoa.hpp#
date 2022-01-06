#ifndef _CYOA_HPP_
#define _CYOA_HPP_
#include <assert.h>
#include <stdlib.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <queue>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
//story class, which constains page class and startthestory method and checkstory method
class story {
 public:
  //pageclass
  class Page {
   private:
    std::string pagename;
    //vector of string that stores the selection navigation part of one page
    std::vector<std::string> navigation;
    //the page nums referenced by navigation
    std::vector<int> nextpages;
    //the text part of the page
    std::vector<std::string> remainder;

   public:
    //constructor of page object, read the page in the meantime in order to initialize all members of within page
    explicit Page(std::string _namepage) : pagename(_namepage) { readpage(); }

    void printpage() {
      //print the text part
      for (size_t i = 0; i < remainder.size(); i++) {
        std::cout << remainder[i] << std::endl;
      }
      //print the navigation part
      if (navigation[0] == "LOSE") {
        std::cout << "\n"
                  << "Sorry, you have lost. Better luck next time!" << std::endl;
        return;
      }
      else if (navigation[0] == "WIN") {
        std::cout << "\n"
                  << "Congratulations! You have won. Hooray!" << std::endl;
        return;
      }
      std::cout << "\n"
                << "What would you like to do?\n"
                << std::endl;
      for (size_t i = 0; i < navigation.size(); i++) {
        std::cout << " " << i + 1 << ". " << navigation[i] << std::endl;
      }
    }
    //read the page and store all information in the page object, check the format of that page
    void readpage() {
      std::ifstream inputfile;
      inputfile.open(pagename);
      if (inputfile.fail()) {
        throw std::invalid_argument("input file does not exits!");
      }
      std::string str;
      //first read the navigation part
      while (std::getline(inputfile, str)) {
        if (str[0] == '#') {
          break;
        }
        //check the validation if the page is a win or lost page
        if (str == "LOSE" || str == "WIN") {
          std::string nextline;
          std::getline(inputfile, nextline);
          if (nextline[0] != '#') {
            std::cerr
                << "wrong input of navigation part, win/lose state line missing the "
                   "following # line!!"
                << std::endl;
            exit(EXIT_FAILURE);
          }
          else {
            std::string state;
            state = str.substr(0, str.size());
            navigation.push_back(state);
            break;
          }
        }
        //check if navigation part has the right format
        std::string::iterator locatec = std::find(str.begin(), str.end(), ':');
        if (locatec == str.end()) {
          std::cerr << "wrong input of navigation part, did not find column!!"
                    << std::endl;
          exit(EXIT_FAILURE);
        }
        //get the page num, check and store
        std::string topage = str.substr(0, std::distance(str.begin(), ++locatec));
        int nextpage = stoi(topage, NULL, 10);
        if (nextpage <= 0) {
          std::cerr << "wrong input of navigation part, negative pagenumber !"
                    << std::endl;
          exit(EXIT_FAILURE);
        }
        nextpages.push_back(nextpage);
        navigation.push_back(str.substr(std::distance(str.begin(), locatec), str.size()));
      }
      if (navigation.size() == 0) {
        std::cerr << "can not find navigation part !" << std::endl;
        exit(EXIT_FAILURE);
      }
      //read and store remaining text part
      while (std::getline(inputfile, str)) {
        // if (str[0] == '\n' || str == "") {
        //   continue;
        // }
        remainder.push_back(str);
      }
      inputfile.close();
    }

    std::string getpagename() { return pagename; }
    std::vector<int> getnextpages() { return nextpages; }
    bool iswinpage() { return navigation[0] == "WIN"; }
    bool islosepage() { return navigation[0] == "LOSE"; }
  };

  //start to display the story and interact with the user
  void startthestory(std::string direct) {
    //initialize the first page
    std::string pagename1 = direct + "/" + "page1.txt";
    Page page(pagename1);
    std::vector<int> nextpages = page.getnextpages();
    int choice = 0;
    //for (int i = 2;; i++) {
    while (true) {
      //display current page
      page.printpage();
      //if already arrived at win or lose, exit story
      if (page.islosepage() || page.iswinpage()) {
        return;
      }
      //read the input from std::in and check if it has the right format
      std::cin >> choice;
      while (!std::cin.good() || choice <= 0 || choice > (int)nextpages.size()) {
        if (!std::cin.good()) {
          std::cin.clear();
          std::string badinput;
          std::cin >> badinput;
          if (std::cin.eof()) {
            exit(EXIT_SUCCESS);
          }
          std::cerr << badinput << " This is not a valid input!" << std::endl;
          std::cin >> choice;
        }
        else {
          std::cerr << choice << " This is not a valid input!" << std::endl;
          std::cin >> choice;
        }
      }
      //set the next page according to choice from user
      std::string nextpagename =
          direct + "/" + "page" + std::to_string(nextpages[choice - 1]) + ".txt";

      Page nextpage(nextpagename);
      page = nextpage;
      nextpages = page.getnextpages();
    }
  }
  //check the validation of whole story
  int checkstory(std::string directory) {
    std::string pagename1 = directory + "/" + "page1.txt";
    Page page1(pagename1);
    std::set<int> visited_pages;
    visited_pages.insert(1);
    int win = false;
    bool lose = false;
    //bool allreferenced = false;
    int numofpages = 0;
    //bool refervalid = false;
    try {
      for (int i = 1;; i++) {
        std::string pagename = directory + "/" + "page" + std::to_string(i) + ".txt";
        Page page(pagename);
        numofpages++;
        if (page.iswinpage()) {
          win = true;
        }
        else if (page.islosepage()) {
          lose = true;
        }
        std::vector<int> nextpages = page.getnextpages();
        for (size_t j = 0; j < nextpages.size(); j++) {
          if (i != nextpages[j]) {
            visited_pages.insert(nextpages[j]);
          }
        }
        for (size_t n = 0; n < nextpages.size(); n++) {
          std::string npagename =
              directory + "/" + "page" + std::to_string(nextpages[n]) + ".txt";
          try {
            Page npage(npagename);
          }
          catch (std::exception & e) {
            //if reference is not valid, print error and exit failure
            std::cerr << "reference to next page " + npagename + " is not valid!!";
            exit(EXIT_FAILURE);
          }
        }
      }
    }
    catch (std::invalid_argument & e) {
      //make sure tha story has at least a win and a lose page
      assert(win && lose);
      //check if all pages in the story are referenced by other page
      // std::cout << "visited size" << visited_pages.size() << "numofp" << numofpages
      //           << std::endl;
      assert(visited_pages.size() == numofpages);
    }
    return numofpages;
  }
};
#endif
