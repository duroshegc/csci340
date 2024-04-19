/************************************************************************************
* NIU CSCI 340 Section 1 *
* Assignment 7 
* Oluwasegun Durosinmi - z1978798 *
* *
* I certify that everything I am submitting is either provided by the professor for use in *
* the assignment, or work done by me personally. I understand that if I am caught submitting *
* the work of others (including StackOverflow or ChatGPT) as my own is an act of Academic *
* Misconduct and will be punished as such. *
* *
* * The purpose of this assignment is to have you perform a practical task using binary trees. This time, that task will be to
implement a simplified XML parser
************************************************************************************/
// Implement a simple parser for XML that uses a tilted binary tree for storage
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <map>

#include "nodes.h" // supplied node declarations
#include "bintree.h"
#include "xml.h"

using namespace std;

/**
 * @brief Converts an xml_element to its string representation.
 * 
 * This function converts an xml_element to its string representation, either as an opening tag or a closing tag.
 * 
 * @param element The xml_element to convert.
 * @param opening Flag indicating whether to generate an opening tag or a closing tag.
 * @return std::string The string representation of the xml_element.
 */

std::string to_string(const xml_element &element, bool opening) {
  if(element.name.empty())
  {
    // Check if the element has no name
    // Return the full text of the element
      return element.fulltext;
  }
  // If it's an opening tag
     string result;
    if (opening) {
       
        result += "<" + element.name;
        for (const auto& attr : element.attrs) {
            // Add attributes, if any
            result += " " + attr.first + "=\"" + attr.second + "\"";
        }
         // Close the opening tag
        result += ">";
        
    } else {
       // Add the closing tag with the element name
        result += "</" + element.name + ">";
    }
     // Return the constructed string representation
    return result;

  
}

/**
 * @brief Finds all XML nodes with the given name in the binary tree.
 * 
 * This function recursively searches the binary tree for XML nodes with the given name.
 * 
 * @param root The root of the binary tree to search.
 * @param name The name of the XML nodes to find.
 * @return std::vector<XMLNODE*> Vector containing pointers to XML nodes with the given name.
 */

std::vector <XMLNODE *> xml_find_by_name(XMLNODE * root, const std::string &name) {
    std::vector<XMLNODE*> myVec;
    // If the current node's name matches the target name
   if(root != nullptr)
  {
   if(root->data.name == name)
   {
      myVec.push_back(root);
   }
    // Recursively search the left and right subtrees
   vector<XMLNODE *> left = xml_find_by_name(root->left, name);
   vector<XMLNODE *> right = xml_find_by_name(root->right, name);

   myVec.insert(myVec.end(), left.begin(), left.end());
   myVec.insert(myVec.end(), right.begin(), right.end());
  }
  // Return the vector containing pointers to XML nodes with the given name
  return myVec;
}


   vector <XMLNODE *> xml_find_with_attr(XMLNODE * root, const string &attrname) {
   vector<XMLNODE *> myVec;
   if(root != nullptr)
  {
     // Iterate through attributes of the current node
    for (const auto& attr : root->data.attrs)    
    {
        
        if (attr.first == attrname) {
        {
            myVec.push_back(root);
            break;
        }
    }
    // Recursively search the left and right subtrees
    vector<XMLNODE *> left = xml_find_by_name(root->left, attrname);
    vector<XMLNODE *> right = xml_find_by_name(root->right, attrname);

    myVec.insert(myVec.end(), left.begin(), left.end());
    myVec.insert(myVec.end(), right.begin(), right.end());
    }
        
       
    }
    // Return the vector containing pointers to XML nodes with the given attribute name
    return myVec;
}

/**
 * @brief Adds an XML node to the tree.
 * 
 * This function adds an XML node to the tree rooted at 'state.root'.
 * 
 * @param element The XML element to add.
 * @param state The XML tree state.
 * @param verbose Flag indicating whether to display verbose output.
 * @return int 0 on success, 1 on error.
 */

int xml_add_node(const xml_element &element, xml_tree_state & state, bool verbose) {
   if(state.root == nullptr)

   // If the tree is empty
   {
    // Create a new root node
      state.root = new XMLNODE(element);
      state.cur = state.root;
      // Return success
      return 0;
   }

   if(state.cur == nullptr)
   {
    // If the current node is null
    // If verbose mode is enabled
      if(verbose)
      {
         cout << "ERROR" << endl; // Display and create a new line
      }
      return 1;
   }

   XMLNODE *node = new XMLNODE(element);
   if(state.cur->data.type == xml_type::plain || state.cur->data.closed)
   {
      if(state.cur->parent != nullptr)
      {
         if(state.cur->right != nullptr)
         {
             // Adjust pointers to insert the new node
            state.cur->right->left = node;
            node->right = state.cur->right;
         }
         node->left = state.cur;
         node->parent = state.cur->parent;
         state.cur->right = node;  // Delete the newly created node

      }
      else
         {
            if( verbose)
            {
               cout << "ERROR" << endl;
            }

            delete node;
            return 1;
         }
   }
   else
   {
      if(state.cur->left != nullptr)
      {
        // Adjust pointers to insert the new node
        state.cur->left->right = node;
        node->left = state.cur->left;
      }
      // Adjust pointers to insert the new node
        node->parent = state.cur;
        node->right = state.cur;
        state.cur->left = node;
   }
    // Update the current node to the newly inserted node
      state.cur = node;
      return 0;
      
}

/**
 * @brief Closes the XML tag with the specified name.
 * 
 * This function closes the XML tag with the specified name in the XML tree state.
 * 
 * @param name The name of the XML tag to close.
 * @param state The XML tree state.
 * @param verbose Flag indicating whether to display verbose output.
 * @return int 0 on success, 1 on error.
 */

int xml_close_tag(const std::string name, xml_tree_state & state, bool verbose) {
   XMLNODE *ptr = state.cur;
    // Iterate through parent nodes
   while(ptr != nullptr)
   {
      xml_element &element = ptr->data;
           // If the tag matches the name, mark it as closed and update the current node
      if(element.type == xml_type::tag && element.name == name)
      {
         element.closed = true;
         state.cur = ptr->parent;
         return 0;
      }
      ptr = ptr->parent;
   }
   // If verbose mode is enabled, display an error message
   if(verbose)
   {
      cout << "ERROR " << name << endl;
   }
   return 1;
}

/**
 * @brief Handles plaintext in XML parsing.
 * 
 * This function handles plaintext in XML parsing, adding it to the XML tree state.
 * 
 * @param plaintext The plaintext to handle.
 * @param state The XML tree state.
 * @param verbose Flag indicating whether to display verbose output.
 * @return int 0 on success, 1 on error.
 */

int xml_handle_plaintext(std::string &plaintext, xml_tree_state & state, bool verbose) {
    // Create an XML element for the plaintext
   xml_element text(xml_type::plain, "", plaintext, map<string, string>());

    // Add the plaintext element to the XML tree state
   int outcome = xml_add_node(text, state, verbose);

   return outcome;
}

/**
 * @brief Handles attributes in XML parsing.
 * 
 * This function handles attributes in XML parsing, extracting attribute-value pairs from the input string.
 * 
 * @param input The input string containing attribute-value pairs.
 * @param attrs The map to store attribute-value pairs.
 * @param verbose Flag indicating whether to display verbose output.
 * @return int The number of attributes handled.
 */

int xml_handle_attributes(const std::string &input, std::map<std::string, std::string> &attrs, bool verbose) {
    // Initialize variables
 size_t index = 0;
    int attributeCount = 0;
    bool encounteredError = false;
    // Iterate through the input string
    while (index < input.length()) 
    {
        // Find the start of the attribute key
        size_t keyStart = input.find_first_not_of(" \t\n\r", index);
    // Handle cases where no key is found
        if (keyStart == string::npos) 
        {
            cout << "ERROR: xml_handle_attributes done. Invalid string remaining \"" << input.substr(index) << "\"" << std::endl; 
            break;
        }
        // Find the end of the attribute key

        size_t keyEnd = input.find('=', keyStart);
        // Handle cases where no end of key is found

        if (keyEnd == std::string::npos) 
        {
            if (!encounteredError) 
            {
                cout << "  ERROR: xml_handle_attributes done. Invalid string remaining \"" << input.substr(keyStart) << "\"" << std::endl;
                encounteredError = true;
            }
            break;
        }
        // Extract the attribute key

        std::string key = input.substr(keyStart, keyEnd - keyStart);
        index = keyEnd + 1;

        // Check for attribute value

        if (index < input.length() || (input[index] != '\"' && input[index] != '\'')) 
        {
            char quoteChar = input[index++];
            size_t valueEnd = input.find(quoteChar, index);
            if (valueEnd == std::string::npos) 
            {
                if (!encounteredError) 
                {
                   cout << "  ERROR: xml_handle_attributes tag ended before value's quotation ended." << std::endl;
                    encounteredError = true;
                }
                break;
            }
            // Add attribute-value pair to the map
            std::string value = input.substr(index, valueEnd - index);
            attrs[key] = value;
            index = valueEnd + 1;
            attributeCount++;
        } else {
            if (!encounteredError) 
            {
                cout << "  ERROR" << input.substr(index) << "\"" << std::endl;
                encounteredError = true;
            }
            break;
        }
        // Find the next attribute
        index = input.find_first_not_of(" \t\n\r", index);
    }
    // Display error if there are remaining characters in the input string

    if (index < input.length() && !encounteredError) {
        std::cerr << "  ERROR" << input.substr(index) << "\"" << std::endl;
    }

    return attributeCount;
}

/**
 * @brief Handles XML tags in parsing.
 * 
 * This function handles XML tags in parsing, including opening and closing tags.
 * 
 * @param tagstring The XML tag string to handle.
 * @param state The XML tree state.
 * @param verbose Flag indicating whether to display verbose output.
 * @return int 0 on success, 1 on error.
 */

int xml_handle_tag(std::string &tagstring, xml_tree_state & state, bool verbose) {
    // Check for valid tag format
   if(tagstring.size() < 3 || tagstring.front() != '<' || tagstring.back() != '>') 
   {
    if (verbose) 
    {
        cout << "  ERROR: Invalid tag: " << tagstring << endl;
    }
    return 1;
}
// Check if the tag is a closing tag
if (tagstring[1] == '/') 
{
    if (tagstring.size() < 4) 
    {
        if (verbose) 
        {
            cout << "ERROR" << tagstring << std::endl;
        }
        return 1;
    }

     // Close the tag with the specified name

    return xml_close_tag(tagstring.substr(2, tagstring.size() - 3), state, verbose);
} 
else 
{
    // Find the position of the first space (if any)
    size_t spacePos = tagstring.find(' ');
    string tag = (spacePos != string::npos) ? tagstring.substr(1, spacePos - 1) : tagstring.substr(1, tagstring.size() - 2);
        // Create an XML element for the tag
    xml_element element(xml_type::tag, tag, "", std::map<std::string, std::string>());
    map<string, string> attributes;

     // Handle attributes if present

    if (spacePos != string::npos) {
        if (xml_handle_attributes(tagstring.substr(spacePos), attributes, verbose) == 0)
        {
            element.attrs = attributes;
        }
    } 
    else 
    {
        return 1;
    
    
    // Add the XML element to the XML tree state}

    return xml_add_node(element, state, verbose);
}

}

/**
 * @brief Prints the subtree rooted at the specified XML node.
 * 
 * This function prints the subtree rooted at the specified XML node to the output stream.
 * 
 * @param root The root of the subtree to print.
 * @param ost The output stream to print to.
 */

void xml_print_subtree(XMLNODE *root, std::ostream & ost) {
     // Base case: if root is null, return
  if(root == nullptr)
  {
   return;
  }

    // Get the XML element associated with the root node
  const xml_element &element = root->data;
// Check if the element is a tag
  if(element.type == xml_type::tag)
  {
    // Print the opening tag
      ost << '<' << element.name; 
      map<string, string> attrb(element.attrs.begin(), element.attrs.end());
        // Print attributes
      for(const auto &at : attrb)
      {
         ost << " " << at.first << "=\"" << at.second << "\"";
      }
    // Close the opening tag
      ost <<'>';

      //Recursively print child nodes
      for(XMLNODE *child = root->left; child != nullptr; child = child->right)
      {
         xml_print_subtree(child, ost);
      }

       // Print the closing tag

      ost << "</" << element.name << ">";
  }
  else
  {
      // If the element is plaintext, print it
      ost << element.fulltext;
  }



}
