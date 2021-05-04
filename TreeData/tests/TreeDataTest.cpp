#include <gtest/gtest.h>
#include "TreeData.hpp"

#include <memory>
#include <map>

TEST(TreeDataTest, create_tree_object_contianing_different_types){

    // Creating Objects containing different types   
        std::string myData5_Name = "MyInt5";
        int myData5_Value = 5;
        TreeData myData5 { myData5_Name, myData5_Value};

        std::string myData6_Name = "MyInt6";
        int myData6_Value = 6;
        TreeData myData6 { myData6_Name, myData6_Value};

        std::string myDataFloat_Name = "MyFloat";
        float myDataFloat_Value = 6.5f;
        TreeData myDataFloat { myDataFloat_Name, myDataFloat_Value};

        std::string myDataDouble_Name = "MyDouble";
        double myDataDouble_Value = 6.5;
        TreeData myDataDouble { myDataDouble_Name, myDataDouble_Value};

        std::string myStringBla_Name = "MyString";
        std::string myStringBla_Value = "Bla";
        TreeData myStringBla { myStringBla_Name, myStringBla_Value};

        std::string myIntArray_Name = "MyIntArray";
        auto myIntArray_Value = std::array<int, 4>( {1,2,3,4} );
        TreeData myIntArray { myIntArray_Name, myIntArray_Value};

        std::string myStringArray_Name = "MyStringArray";
        auto myStringArray_Value = std::array<std::string, 4>({     std::string("Ich"), 
                                                                    std::string("bin"), 
                                                                    std::string("ein"), 
                                                                    std::string("Genie!")}
                                                                    );
        TreeData myStringArray { myStringArray_Name, myStringArray_Value};

        TreeData innerNode { "InnerNode", TreeNode {    { "innerData5", myData5 },
                                                        { "innerData6", myData6 },
                                                        { "innerDataFloat", myDataFloat }
                                                    } 
                            };

        std::map<std::string, TreeData> dataMap;
        dataMap[myData5.Name()] = myData5;
        dataMap[myData6.Name()] = myData6;
        dataMap[myDataFloat.Name()] = myDataFloat;
        dataMap[myDataDouble.Name()] = myDataDouble;
        dataMap[myStringBla.Name()] = myStringBla;
        dataMap[myIntArray.Name()] = myIntArray;
        dataMap[myStringArray.Name()] = myStringArray;
        dataMap["InnerNode"] = innerNode;

    // Extracting the values of the different objects
        EXPECT_EQ(dataMap[myData5_Name].Value<int>(), myData5_Value);
        EXPECT_EQ(dataMap[myData6_Name].Value<int>(), myData6_Value);
        EXPECT_EQ(dataMap[myDataFloat_Name].Value<float>(), myDataFloat_Value);
        EXPECT_EQ(dataMap[myDataDouble_Name].Value<double>(), myDataDouble_Value);
        EXPECT_EQ(dataMap[myStringBla_Name].Value<std::string>(), myStringBla_Value);
         auto tstIntArray = dataMap[myIntArray_Name].Value<std::array<int, 4>>();
         EXPECT_EQ(tstIntArray, myIntArray_Value);
         auto tstStringArray = dataMap[myStringArray_Name].Value<std::array<std::string, 4>>();
         EXPECT_EQ(tstStringArray, myStringArray_Value);
         auto tstInnerNodemyData6 = dataMap["InnerNode"].Value<TreeNode>()["innerData6"].Value<int>();
         EXPECT_EQ(tstInnerNodemyData6, myData6_Value);

         dataMap.deepSearch("innerData6").Value<int>();

    // Changing the value of an object
        int myData5_NewValue = 9;
        dataMap[myData5_Name].Value<int>(myData5_NewValue);
        EXPECT_EQ(dataMap[myData5_Name].Value<int>(), myData5_NewValue);

    // Changing the value and its type
        std::string myData6_NewValue = "NewString";
        dataMap[myData6_Name].Value<std::string>(myData6_NewValue);
        EXPECT_EQ(dataMap[myData6_Name].Value<std::string>(), myData6_NewValue);
}


