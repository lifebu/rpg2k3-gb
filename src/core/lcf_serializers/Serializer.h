#pragma once

#include <string>
#include <vector>
#include <memory>

namespace tinyxml2 {class XMLDocument; };

template <typename T>
class Serializer {
protected:
    Serializer() {}

private:
    // Full Files:
    virtual T FromFile(std::string fileName) = 0;
    virtual void ToFile(std::string fileName, T& elem) = 0;
    
    virtual  std::vector<T> MultipleFromFile(std::string fileName) = 0;
    virtual  void MultipleToFile(std::string fileName, std::vector<T>& elems) = 0;

    // Partial Files:
    virtual  T FromFile(std::unique_ptr<tinyxml2::XMLDocument>& doc) = 0;
    virtual std::unique_ptr<tinyxml2::XMLDocument> ToFile(T& elem) = 0;

    virtual std::vector<T> MultipleFromFile(std::unique_ptr<tinyxml2::XMLDocument>& doc) = 0;
    virtual std::unique_ptr<tinyxml2::XMLDocument> MultipleToFile(std::vector<T>& elems) = 0;
};