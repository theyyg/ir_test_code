// iR_Lib.cpp : Defines the exported functions for the DLL.
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

#include "pch.h"
#include <cstring>
#include <limits.h>
#include "iR_Lib.h"

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
        return INVALID_HEX2INT_PARAMETER;

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
        return INVALID_HEX2INT_PARAMETER;
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
        {
            return INVALID_HEX2INT_PARAMETER;
        }
    }

    return hexDigit;

}

/// <summary>
/// Removes a node from a linked list with a given value;
/// </summary>
/// <param name="value">The value to be removed from the list.</param>
/// <param name="h">A pointer to the root node of the list.</param>
/// <returns>Returns <c>true</c> if the node was successfully removed or <c>false</c> otherwise</returns>
bool RemoveNode(int value, node **h)
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
        isNodeRemoved = RemoveNode(value, &((*h)->next));
    }

    return isNodeRemoved;
}
