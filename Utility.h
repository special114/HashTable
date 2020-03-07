#ifndef UTILITY_H
#define UTILITY_H

/* File from HashTable project
 * author: Rafał Surdej
 */

#include <string>
#include <fstream>

#include "HashTable.hpp"
#include "ConstIterator.hpp"
#include "Iterator.hpp"
#include "HashFunction.hpp"


const size_t LINE_BEG = 0;
const size_t DEFINE_LENGTH = 8; // "#define "
const std::string IN_FILE = "plikWejsciowy";
const std::string OUT_FILE = "plikWyjsciowy";

void addToTable(HashTable<std::string, std::string>& t1, std::string& lin, size_t pos = 0);

int defineFun();

void unit_tests();

#endif // UTILITY_H

