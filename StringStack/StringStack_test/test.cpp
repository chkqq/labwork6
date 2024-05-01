#include "pch.h"

#include "../../StringStack/StringStack/CStringStack.cpp"
#include <gtest/gtest.h>

TEST(CStringStackTest, InitialState) 
{
    CStringStack stack;
    EXPECT_TRUE(stack.is_empty());
}

TEST(CStringStackTest, PushAndTop) 
{
    CStringStack stack;
    stack.push("Hello");
    stack.push("World");
    stack.push("C++");

    EXPECT_EQ(stack.top(), "C++"); 
}

TEST(CStringStackTest, Pop)
{
    CStringStack stack;
    stack.push("Hello");
    stack.push("World");

    stack.pop();
    EXPECT_EQ(stack.top(), "Hello");
    stack.pop();
    EXPECT_TRUE(stack.is_empty());
}

TEST(CStringStackTest, PopEmptyStack) 
{
    CStringStack stack;
    EXPECT_THROW(stack.pop(), std::out_of_range);
}
 
TEST(CStringStackTest, CopyConstructor) 
{
    CStringStack stack;
    stack.push("Hello");
    stack.push("World");

    CStringStack stack_copy(stack);
    EXPECT_EQ(stack_copy.top(), "World");
    EXPECT_FALSE(stack_copy.is_empty()); 

    stack_copy.pop();
    EXPECT_EQ(stack_copy.top(), "Hello");
}

TEST(CStringStackTest, MoveConstructor) 
{
    CStringStack stack;
    stack.push("Hello");
    stack.push("World");

    CStringStack stack_moved(std::move(stack));
    EXPECT_EQ(stack_moved.top(), "World"); 

    EXPECT_TRUE(stack.is_empty());
}

TEST(CStringStackTest, CopyAssignment) 
{
    CStringStack stack1;
    stack1.push("A");
    stack1.push("B");

    CStringStack stack2;
    stack2.push("X");

    stack2 = stack1;

    EXPECT_EQ(stack2.top(), "B");
    EXPECT_FALSE(stack2.is_empty());
}

TEST(CStringStackTest, MoveAssignment)
{
    CStringStack stack1;
    stack1.push("A");
    stack1.push("B");

    CStringStack stack2;
    stack2.push("X");

    stack2 = std::move(stack1);

    EXPECT_EQ(stack2.top(), "B");
    EXPECT_FALSE(stack2.is_empty());
    EXPECT_TRUE(stack1.is_empty());
}

TEST(CStringStackTest, LargeStack)
{
    CStringStack stack;

    for (int i = 0; i < 1000; i++) 
    {
        stack.push(std::to_string(i));
    }

    EXPECT_EQ(stack.top(), "999");

    for (int i = 0; i < 1000; i++)
    {
        stack.pop();
    }
    EXPECT_TRUE(stack.is_empty());
}

TEST(CStringStackTest, TopEmptyStack) 
{
    CStringStack stack;
    EXPECT_THROW(stack.top(), std::out_of_range); 
}
