#ifndef CSVPARSER_HPP
#define CSVPARSER_HPP

#include "utils.hpp"
#include "book.hpp"
#include "subscriber.hpp"
#include <fstream>
#include <regex>
#include <algorithm>

std::string replaceOccurences(std::string const &in, std::string const &from, std::string const &to){
  return std::regex_replace( in, std::regex(from), to );
}

std::vector<std::string> retrieveDataset(std::string const &path){
    std::ifstream ifs(path, std::ifstream::in);
    std::vector<std::string> parsedCSV;
    std::string tmp;

    //Retrieving lines from CSV file
    while(!ifs.eof()){
        char c = ifs.get();

        tmp.push_back(c);
        if (c == '\n'){
            //Clean data set
            if (tmp.find("Article de REGLES inconnu ::") == std::string::npos)
                parsedCSV.push_back(tmp);
            tmp.clear();
        }
    }
    ifs.close();
    return (parsedCSV);
}

std::vector<Book>   importBooksCSV( std::string const &path){
    std::vector<std::string> parsedCSV = retrieveDataset(path);
    std::vector<Book> books;

    for (std::size_t i = 1; i < parsedCSV.size(); i++){
        //Tokenize CSV lines
        std::vector<std::string> tokenizedLine = split(parsedCSV[i], ";");
        //Clear forbidden characters in SQL
        for (std::size_t j = 0; j < tokenizedLine.size(); j++)
            tokenizedLine[j] = replaceOccurences(tokenizedLine[j], "'", "");
        Book elem = Book(
            std::atoi(tokenizedLine[0].c_str()),
            tokenizedLine[1],
            tokenizedLine[2],
            tokenizedLine[3],
            tokenizedLine[4],
            tokenizedLine[5],
            tokenizedLine[6],
            tokenizedLine[7],
            tokenizedLine[8],
            tokenizedLine[9],
            tokenizedLine[10],
            ":FREE:"
        );
        books.push_back(elem);
    }
    return (books);
}

std::vector<Subscriber>   importSubscribersCSV( std::string const &path){
    std::vector<std::string> parsedCSV = retrieveDataset(path);
    std::vector<Subscriber> subscribers;

    for (std::size_t i = 1; i < parsedCSV.size(); i++){
        //Tokenize CSV lines
        std::vector<std::string> tokenizedLine = split(parsedCSV[i], ";");
        Subscriber elem = Subscriber(
            std::atoi(tokenizedLine[0].c_str()),
            tokenizedLine[1],
            tokenizedLine[2]
        );

        subscribers.push_back(elem);
    }
    return (subscribers);
}

#endif