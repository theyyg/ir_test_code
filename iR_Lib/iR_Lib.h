// iR_Lib.h : This file contains the 'main' function. Program execution begins and ends there.
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

#pragma once

#ifdef IRLIB_EXPORTS
#define IR_LIB_API __declspec(dllexport)
#else
#define IR_LIB_API __declspec(dllimport)
#endif

/// <summary>
/// Linked List Node with an integer value
/// </summary>
struct node
{
    int value;
    node * next;
};

constexpr int INVALID_HEX2INT_PARAMETER = 0x7FFFFFFF;

extern "C" IR_LIB_API int hex2int(const char * s);

extern "C" IR_LIB_API bool RemoveNode(int value, node **h);