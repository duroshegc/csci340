/************************************************************************************
* NIU CSCI 340 Section 1 *
* Assignment 6
* Oluwasasegun Durosinmi   Z1978798 *
* *
* I certify that everything I am submitting is either provided by the professor for use in *
* the assignment, or work done by me personally. I understand that if I am caught submitting *
* the work of others (including StackOverflow or ChatGPT) as my own is an act of Academic *
* Misconduct and will be punished as such. *
* *
*  This assignment uses STL associative container types map and set to create a sudoku solver using INI files
************************************************************************************/

#include "settings.h"
#include "iniparse.h"
#include <algorithm>

using namespace std;
/**
 * @brief Reads an INI file from the input stream and parses it into an INI_CONFIG object.
 * 
 * @param input The input stream containing the INI file.
 * @param verbosity Verbosity level for debug output.
 * @return INI_CONFIG The parsed INI configuration.
 */

INI_CONFIG read_ini(std::istream &input, int verbosity) 
{
  INI_CONFIG obj;
  string buffer;
  string sectionName;
  while (getline(input, buffer)) 
  {
  // Trim leading and trailing whitespace from buffer
  buffer.erase(buffer.begin(), find_if(buffer.begin(), buffer.end(), [](unsigned char ch) { return !isspace(ch); }));
  buffer.erase(find_if(buffer.rbegin(), buffer.rend(), [](unsigned char ch) { return !isspace(ch); }).base(), buffer.end());

  // If the first character of buffer is '[' (indicating the start of a section):
  if (!buffer.empty() && buffer.front() == '[') 
  {
      // Find the position of the closing bracket ']'
      auto pos = buffer.find(']');
      if (pos != string::npos) {
          // Extract the section name from buffer, excluding the brackets
          sectionName = buffer.substr(1, pos - 1);
          // Trim leading and trailing whitespace from the extracted section name
          sectionName.erase(0, sectionName.find_first_not_of(" \t\r\n"));
          sectionName.erase(sectionName.find_last_not_of(" \t\r\n") + 1);
      }
      // Note: Do not create a section here to avoid adding empty sections
  }
  // Else (the line should be a key-value pair):
    else 
    {
        // Find the position of the equal sign '='
        auto pos = buffer.find('=');
        if (pos != string::npos) 
        {
            // Extract the key from the part of buffer before the equal sign
            string key = buffer.substr(0, pos);
            // Extract the value from the part of buffer after the equal sign
            string value = buffer.substr(pos + 1);
            // Trim leading and trailing whitespace from both key and value
            key.erase(0, key.find_first_not_of(" \t\r\n"));
            key.erase(key.find_last_not_of(" \t\r\n") + 1);
            value.erase(0, value.find_first_not_of(" \t\r\n"));
            value.erase(value.find_last_not_of(" \t\r\n") + 1);
            // If sectionName is not empty (meaning we are within a valid section):
            if (!sectionName.empty()) 
            {
              // Assign the trimmed value to the key within the current section in obj
              obj[sectionName][key] = value;
          }
      }
  }
  }
  // Return the populated INI_CONFIG object
    return obj;
}


/**
 * @brief Writes the INI_CONFIG object to the output stream in INI file format.
 * 
 * @param ost The output stream to write the INI file.
 * @param config The INI configuration to write.
 * @return true if writing is successful, false otherwise.
 */


bool write_ini( std::ostream & ost, const INI_CONFIG & config ) {
  // Iterate through each section in the config
  for(auto it = config.begin(); it != config.end(); it++)
  {
    // Write section header
    ost << '[' << it->first << ']'<< endl;
    // Iterate through each key-value pair in the section
    for(auto i = it->second.begin(); i != it->second.end(); i++)
    {
      // Write key-value pair
      ost << i->first << " = " << i->second << endl;
    }
  }
  return true;
}

/**
 * @brief Prints the INI_CONFIG object to the output stream with section names prefixed to key names.
 * 
 * @param ost The output stream to print the INI configuration.
 * @param config The INI configuration to print.
 */

void print_ini( std::ostream & ost, const INI_CONFIG & config ) {
  // Check if config is empty
  if(config.empty())
  {
    // Print message if config is empty
    cout << "Configuration is empty. Nothing to print\n" << endl;
    return;
  }
  // Iterate through each section in the config

  for(auto it = config.begin(); it != config.end(); it++)
  {
    // Check if the section is empty
    if(it->second.empty())
    {
      // Print message if section is empty
      cout << "Section \"" << it->first << "\" is empty\n";
    }
    else
    {
      // Iterate through each key-value pair in the section
      for(auto i = it->second.begin(); i != it->second.end(); i++ )
      {
        // Print key-value pair with section prefix
      ost << it->first << '.' << i->first << " \t= \"" << i->second << "\"\n";
      }
    }
   
  }
  ost << endl;
}
  
/**
 * @brief Adds a new section to the INI configuration.
 * 
 * @param config The INI configuration to add the section to.
 * @param section The name of the section to add.
 */

void add_ini_section(INI_CONFIG & config, const std::string &section) {
  // Check if the section already exists
  auto it = config.find(section);
  if(it == config.end())
  {
    // Create a new empty section if it does not exist
   map<string, string>* mymap;
   mymap = new map<string, string>();
   
   pair<string, map<string, string>>* mypair;
   mypair = new pair<string, map<string, string>>(section, *mymap);

    config.insert(*mypair);
  }
}

/**
 * @brief Removes a section from the INI configuration. 
 * @param config The INI configuration to remove the section from.
 * @param section The name of the section to remove.
 * @return int Returns 1 if the section is successfully removed, 0 otherwise.
 */

int remove_ini_section(INI_CONFIG & config, const std::string &section) {
  // Find the section in the config
  
  auto it = config.find(section);
  if(it != config.end())
  {
     // Clear the section and erase it from the config
    it->second.clear();
    config.erase(it);
    return 1;
  }
  else
  {
    // Return 0 if the section is not found
    return 0;
  }
}

/**
 * @brief Gets the value of a key in a section of the INI configuration.
 * 
 * @param config The INI configuration to search for the key.
 * @param section The name of the section containing the key.
 * @param key The name of the key to retrieve the value for.
 * @return std::string The value associated with the specified key, or an empty string if the key is not found.
 */

std::string get_ini_key(const INI_CONFIG &config, const std::string &section, const std::string &key) {
   // Find the specified section in the config
  auto it = config.find(section);
  if(it != config.end())
  {
    // Find the specified key within the section
    auto ptr = it->second.find(key);
    if(ptr != it->second.end())
    {
      // Return the value associated with the key
      return ptr->second;
    }
    else
    {
      // Return an empty string if the key is not found
      return "";
    }
  }
  else
  {
    // Return an empty string if the section is not found
    return "";
  }
}

/**
 * @brief Sets the value of a key in a section of the INI configuration.
 * 
 * @param config The INI configuration to modify.
 * @param section The name of the section containing the key.
 * @param key The name of the key to set the value for.
 * @param value The new value to set for the key.
 */

void set_ini_key(INI_CONFIG &config, const std::string &section, const std::string &key, const std::string & value) {
  // Find the specified section in the config
  auto it = config.find(section);
  if(it != config.end())
  {
    // Find the specified key within the section
    auto ptr = it->second.find(key);
    if(ptr != it->second.end())
    {
      // Update the value of the existing key
      ptr->second = value;
    }
    else
    {
      // Insert a new key-value pair if the key does not exist
      it->second.insert(pair<string, string>(key, value));
    }
  }
  else
  {
    add_ini_section(config, section);
    config[section].insert(pair<string, string>(key, value));

  }
}

/**
 * @brief Removes a key from a section of the INI configuration.
 * 
 * @param config The INI configuration to modify.
 * @param section The name of the section containing the key.
 * @param key The name of the key to remove.
 * @return int Returns 1 if the key is successfully removed, 0 if the section or key does not exist.
 */

int remove_ini_key(INI_CONFIG &config, const std::string &section, const std::string &key) {
  // Find the specified section in the config
  auto it = config.find(section);
  if(it != config.end())
  {
    // Find the specified key within the section
    auto ptr = it->second.find(key);
    if(ptr != it->second.end())
    {
      // Erase the key from the section
      it->second.erase(ptr); 
      return 1;
    }
    else
    {
      // Return 0 if the key is not found within the section
      return 0;
    }
  }
  else
  {
    // Return 0 if the section is not found
    return 0;
  }
}