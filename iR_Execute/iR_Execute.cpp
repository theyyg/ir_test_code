// iR_Execute.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// MIT License
//
// Copyright(c) 2022 Blaine Wood
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <exception>
#include <iostream>
#include <string>

#include "iR_Lib.h"

// The requirements of this function request did not allow for the removal of the root node
// I have modified the prototype to take the address of the root_node

/// <summary>
/// Removes a node from a linked list with a given value;
/// </summary>
/// <param name="value">The value to be removed from the list.</param>
/// <param name="h">A pointer to the root node of the list.</param>
/// <returns>Returns <c>true</c> if the node was successfully removed or <c>false</c> otherwise</returns>
bool RemoveNodeLoop(int value, node ** h)
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
    isRemoved = RemoveNode(0, &rootNode);
    std::cout << std::endl << "Remove node with value 0" << std::endl;
    PrintList(rootNode);
    PrintRemovalSuccess(0, isRemoved);

    isRemoved = RemoveNodeLoop(3, &rootNode);
    std::cout << std::endl << "Remove node with value 3" << std::endl;
    PrintList(rootNode);
    PrintRemovalSuccess(3, isRemoved);

    isRemoved = RemoveNode(7, &rootNode);
    std::cout << std::endl << "Remove node with value 7" << std::endl;
    PrintList(rootNode);
    PrintRemovalSuccess(7, isRemoved);
    
    isRemoved = RemoveNode(100, &rootNode);
    std::cout << std::endl << "Remove node with value 100" << std::endl;
    PrintList(rootNode);
    PrintRemovalSuccess(100, isRemoved);

    return 0;
}

