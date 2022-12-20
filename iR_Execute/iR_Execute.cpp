// iR_Execute.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <exception>
#include <iostream>
#include <string>

/// <summary>
/// Linked List Node with an integer value
/// </summary>
struct node
{
    int value;
    node * next;
};

/// <summary>
/// Implements a conversion from an ASCII C string
/// </summary>
/// <param name="s">A C-string that contains a hexidecimal value of an ASCII character</param>
/// <returns><para>Returns the integer value of the ASCII input</para>
/// <para>Throws exception if the c-string is a nullptr</para>
/// <para>Throws exception if the hexidecimal value is not valid. (e.g. "2G") </para></returns>
int hex2int(const char * s)
{
    int convertedHex = 0;

    // Verify that the string has a valid pointer
    if (s == 0)
    {
        // Return an non-ASCII value for an error code
        throw std::invalid_argument("hex2int: cstring is NULL");
    }

    size_t stringSize = strlen(s);

    const char ZERO = '0';
    const char BIG_A = 'A';
    const char LITTLE_A = 'a';
    int hexDigit = 0;                      // Use -1 as an invalid digit
    bool isValid = true;
    size_t i = 0;

    // Skip over "0x" if formatted in that way
    if (stringSize > 2 && s[0] == '0' && (s[1] == 'x' || s[1] == 'X'))
    {
        i = 2;
    }

    // Check for integer overflow (hex string is too big)
    if ((stringSize > 10 && i == 2) ||
        stringSize > 8)
    {
        throw std::invalid_argument("hex2int: argument string is too large for int conversion");
    }

    for (/*i is set prior*/; s[i] != '\0'; ++i)           // Traverse the string and convert 
    {
        // Shift the value up by one byte.
        // Unnecessary at i==0, but it's fast and prevents unecessary compares
        hexDigit = hexDigit << 4;

        // Extract 0-9
        switch (s[i])
        {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            // The integer value is the difference from the base ASCII value (0)
            hexDigit += s[i] - ZERO;
            break;
        case 'a':
        case 'b':
        case 'c':
        case 'd':
        case 'e':
        case 'f':
            // The integer value is the difference from the base ASCII value (a) + 0xA (or 10)
            hexDigit += s[i] - LITTLE_A + 0xA;
            break;
        case 'A':
        case 'B':
        case 'C':
        case 'D':
        case 'E':
        case 'F':
            // The integer value is the difference from the base ASCII value (A) + 0xA (or 10)
            hexDigit += s[i] - BIG_A + 0xA;
            break;
        case '\0':
            break;
        default:
            isValid = false;
            break;
        }

        // Poorly formed string
        if (!isValid)
            throw std::invalid_argument("hex2int: Invalid string format");
    }

    return hexDigit;

}

/// <summary>
/// Removes a node from a linked list with a given value;
/// </summary>
/// <param name="value">The value to be removed from the list.</param>
/// <param name="h">A pointer to the root node of the list.</param>
/// <returns>Returns <c>true</c> if the node was successfully removed or <c>false</c> otherwise</returns>
bool remove_recursive(int value, node ** h)
{
    bool isNodeRemoved(false);

    // Verify the that the node is a valid pointer
    if (h == nullptr || *h == nullptr)
    {
        // Failure: return immediately
        return false;
    }

    // Satisfy the terminal case for recursion
    if ((*h)->value == value)
    {
        node * nextNode = (*h)->next;
        (*h)->next = nullptr;
        *h = nextNode;
        isNodeRemoved = true;
    }
    else
    {
        // Treat the next node as the new root
        isNodeRemoved = remove_recursive(value, &((*h)->next));
    }

    return isNodeRemoved;
}

// The requirements of this function request did not allow for the removal of the root node
// I have modified the prototype to take the address of the root_node

/// <summary>
/// Removes a node from a linked list with a given value;
/// </summary>
/// <param name="value">The value to be removed from the list.</param>
/// <param name="h">A pointer to the root node of the list.</param>
/// <returns>Returns <c>true</c> if the node was successfully removed or <c>false</c> otherwise</returns>
bool remove(int value, node ** h)
{
    bool isNodeRemoved(false);

    // Verify the that the node is a valid pointer
    if (h == nullptr || *h == nullptr)
    {
        // Failure: return immediately
        return false;
    }

    // Handle root node removal
    if ((*h)->value == value)
    {
        node * newRoot = (*h)->next;
        (*h)->next = nullptr;
        *h = newRoot;

        return true;
    }

    node * activeNode = (*h);
    for (node * nextNode = activeNode->next; activeNode != nullptr; /* inc in loop */)
    {
        // Remove matching nodes
        if (nextNode != nullptr && nextNode->value == value)
        { 
            node * tempNext = nextNode->next;
            activeNode->next = tempNext;
            nextNode->next = nullptr;
            isNodeRemoved = true;

            // This could be remove to remove all nodes with the given value
            break;
        }

        activeNode = activeNode->next;
        if (activeNode != nullptr)
        {
            nextNode = activeNode->next;
        }
    }
    return isNodeRemoved;
}

/// <summary>
/// Prints the hex string and it's converted value
/// - Catches any exceptions that occur during conversion
/// </summary>
/// <param name="hexString">A string containing the text representation of a hex value</param>
void PrintHex2Int(const std::string & hexString)
{
    std::cout << '\"'
        << hexString
        << "\" = ";
    try
    {
        std::cout << hex2int(hexString.c_str());
    }
    catch (std::invalid_argument & e)
    {
        std::cerr << std::endl
            << "Error converting string to integer:"
            << std::endl
            << " > "
            << e.what();
    }
    std::cout << std::endl;
}


void PrintList(node * activeNode, bool isVertical = false, bool isRoot = true)
{
    if (activeNode == nullptr) 
    { 
        return; 
    }

    if (isRoot) 
    { 
        std::cout << '*'; 
    }

    std::cout << activeNode->value;

    if (activeNode->next != nullptr)
    {
        if (isVertical)
        {
            std::cout << std::endl << " |" << std::endl;
        }
        else
        {
            std::cout << " -> ";
        }
    }

    PrintList(activeNode->next, isVertical, false);

    if (isRoot)
    {
        std::cout << std::endl;
    }
}

void PrintRemovalSuccess(int value, bool isRemoved)
{
    if (isRemoved)
    {
        std::cout << value << " has been removed";
    }
    else
    {
        std::cout << value << " was not removed";
    }
    std::cout << std::endl;
}

int main()
{
    // Test and demonstrate the hex conversion
    std::cout <<  "== Testing Hex Conversion ==" << std::endl;
    // Test Valid
    std::cout << std::endl << "Valid Hex:" << std::endl;
    PrintHex2Int("7");
    PrintHex2Int("23");
    PrintHex2Int("C");
    // Test Limits
    std::cout << std::endl << "Integer Limits:" << std::endl;
    PrintHex2Int("00");
    PrintHex2Int("FFFFFFFF");
    // Test Alternate Format
    std::cout << std::endl << "Alternate format:" << std::endl;
    PrintHex2Int("D00d");
    PrintHex2Int("0xBAD");
    PrintHex2Int("0xbeef");
    // Test Too Big
    std::cout << std::endl << "Too Big:" << std::endl;
    PrintHex2Int("1234567890ABCDEF");
    // Test Invalid
    std::cout << std::endl << "Invalid string:" << std::endl;
    PrintHex2Int("GOLF");
    // Test Bad Pointer
    std::cout << std::endl << "Null Pointer:" << std::endl;
    try { hex2int(nullptr); }
    catch (std::invalid_argument& e) { std::cerr << e.what() << std::endl; }

    std::cout << std::endl;

    // Test and demonstrate the linked list removal
    std::cout << "== Testing Linked List Removal ==" << std::endl;
    const unsigned int NODE_COUNT = 10;
    node nodes[NODE_COUNT];
    node * rootNode = &(nodes[0]);

    // Populate the linked list with values 0-10
    node * activeNode = rootNode;
    for (unsigned int i = 0; i < NODE_COUNT; ++i)
    {
        activeNode->next = nullptr;
        activeNode->value = i;
        if (i != (NODE_COUNT - 1))
        {
            activeNode->next = &(nodes[i + 1]);
        }

        activeNode = activeNode->next;
    }

    std::cout << std::endl << "Populate the list with consecutive integers (0-" << NODE_COUNT << ")" << std::endl;
    PrintList(rootNode);

    // Let's change node[8] to have a value of 3 so that there are duplicates
    nodes[8].value = 3;
    std::cout << std::endl << "Set the 8th node's value to 3 for a duplicate" << std::endl;
    PrintList(rootNode);

    // Remove nodes
    bool isRemoved;
    isRemoved = remove(0, &rootNode);
    std::cout << std::endl << "Remove node with value 0" << std::endl;
    PrintList(rootNode);
    PrintRemovalSuccess(0, isRemoved);

    isRemoved = remove_recursive(3, &rootNode);
    std::cout << std::endl << "Remove node with value 3" << std::endl;
    PrintList(rootNode);
    PrintRemovalSuccess(3, isRemoved);

    isRemoved = remove(7, &rootNode);
    std::cout << std::endl << "Remove node with value 7" << std::endl;
    PrintList(rootNode);
    PrintRemovalSuccess(7, isRemoved);
    
    remove(100, &rootNode);
    std::cout << std::endl << "Remove node with value 100" << std::endl;
    PrintList(rootNode);
    PrintRemovalSuccess(100, isRemoved);

    return 0;
}

