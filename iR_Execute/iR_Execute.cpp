// iR_Execute.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <exception>


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
/// <para>Throws exception if the hexidecimal value is not valid. (e.g. "2G") </returns>
int hex2int(const char * s)
{
    int converted_hex = 0;

    // Verify that the string has a valid pointer
    if (s == nullptr)
    {
        // Return an non-ASCII value for an error code
        throw std::invalid_argument("hex2int: cstring is NULL");
    }

    const char ZERO = '0';
    const char BIG_A = 'A';
    const char LITTLE_A = 'a';
    size_t string_size = strlen(s);
    long long hex_digit = 0;                      // Use -1 as an invalid digit
    size_t i = 0;

    // Skip over "0x" if formatted in that way
    if (string_size > 2 && s[0] == '0' && (s[1] == 'x' || s[1] == 'X'))
    {
        i = 2;
    }

    for (/*i is set prior*/; s[i] != '\0'; ++i)           // Traverse the string and convert 
    {
        // Shift the value up by one byte.
        // Unnecessary at i==0, but it's fast and prevents unecessary compares
        hex_digit = hex_digit << 4;

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
            hex_digit += s[i] - ZERO;
            break;
        case 'a':
        case 'b':
        case 'c':
        case 'd':
        case 'e':
        case 'f':
            // The integer value is the difference from the base ASCII value (a) + 0xA (or 10)
            hex_digit += s[i] - LITTLE_A + 0xA;
            break;
        case 'A':
        case 'B':
        case 'C':
        case 'D':
        case 'E':
        case 'F':
            // The integer value is the difference from the base ASCII value (A) + 0xA (or 10)
            hex_digit += s[i] - BIG_A + 0xA;
            break;
        case '\0':
            break;
        default:
            hex_digit = -1;
            break;
        }

        // Poorly formed 
        if (hex_digit == -1)
            throw std::invalid_argument("hex2int: Invalid string format");
    }

    return hex_digit;

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

    std::cout << (*h)->value << std::endl;

    // Satisfy the terminal case for recursion
    if ((*h)->value == value)
    {
        node * next_node = (*h)->next;
        (*h)->next == nullptr;
        *h == next_node;
        isNodeRemoved == true;
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
        node * new_root = (*h)->next;
        (*h)->next = nullptr;
        *h = new_root;

        return true;
    }

    node * active_node = (*h);
    for (node * next_node = active_node->next; active_node != nullptr; /* inc in loop */)
    {
        // Remove matching nodes
        if (next_node != nullptr && next_node->value == value)
        { 
            node * new_next = next_node->next;
            active_node->next = new_next;
            next_node->next = nullptr;
            isNodeRemoved = true;

            // This could be remove to remove all nodes with the given value
            break;
        }

        active_node = active_node->next;
        if (active_node != nullptr)
        {
            next_node = active_node->next;
        }
    }
    return isNodeRemoved;
}


int main()
{
    // Test and demonstrate the hex conversion
    try
    {
        std::cout << "Testing Hex Conversion" << std::endl;
        // Test Limits
        std::cout << "\"00\" = ";
        std::cout << hex2int("00") << std::endl;
        // Test Valid
        std::cout << "\"FFFFFFFF\" = ";
        std::cout << hex2int("FFFFFFFF") << std::endl;
        // Test Alternate Format
        std::cout << "\"0xD00d\" = ";
        std::cout << hex2int("0xD00d") << std::endl;
        // Test Invalid
        std::cout << "\"GOLF\" = ";
        std::cout << hex2int("GOLF") << std::endl;
    }
    catch (std::invalid_argument & e)
    {
        std::cerr << e.what() << std::endl;
    }

    // Test and demonstrate the linked list removal
    const unsigned int NODE_COUNT = 10;
    node nodes[NODE_COUNT];
    node * root_node = &(nodes[0]);

    // Populate the linked list with 
    node * active_node = root_node;
    for (unsigned int i = 0; i < NODE_COUNT; ++i)
    {
        active_node->next = nullptr;
        active_node->value = i;
        if (i != (NODE_COUNT - 1))
        {
            active_node->next = &(nodes[i + 1]);
        }

        active_node = active_node->next;
    }

    // Remove nodes
    remove(0, &root_node);
    bool isRemoved = remove(7, &root_node);
    remove(100, &root_node);

    // Display the results
    std::cout << "The linked list values: " << std::endl;
    for (active_node = root_node; active_node != nullptr; active_node = active_node->next)
    {
        std::cout << "  " << active_node->value << std::endl;
    }

    std::cout << "The node with value of 7 was ";
    if (!isRemoved)
    {
        std::cout << "not ";
    }
    std::cout << "removed.";

    return 0;
}

