#include <assert.h>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <regex>
#include <vector>
#include <queue>
#include <fstream>
#include <cstdio>

#include "include/comm_module.h"

using namespace std;
using namespace pc_emulator;
using namespace pc_specification;
using MemType  = pc_specification::MemType;
using DataTypeCategory = pc_specification::DataTypeCategory;
using FieldIntfType = pc_specification::FieldInterfaceType;


std::unique_ptr<PCVariableContainer>
            CommModule::GetVariableContainer(string NestedAccessPath) {

    std::vector<string> results;

    boost::split(results, NestedAccessPath,
                boost::is_any_of(".[]"), boost::token_compress_on);
    if (NestedAccessPath.empty())
        return nullptr;

    auto V = __ConfigInterface.GetExternVariable(results[0]);
    if (V == nullptr)
        return nullptr;
    string RemField;
    if (results.size() > 1)
        RemField = NestedAccessPath.substr(NestedAccessPath.find('.') + 1,
                                        string::npos);

    V = V->GetPtrToField(RemField);
    return std::unique_ptr<PCVariableContainer>(new PCVariableContainer(V));
};

std::unique_ptr<PCVariableContainer> CommModule::GetVariableContainer(
                int RamByteOffset, int RamBitOffset,
                string VariableDataTypeName) {

    auto V = __ConfigInterface.GetVariablePointerToMem(
                RamByteOffset, RamBitOffset,VariableDataTypeName);
    if (V == nullptr)
        return nullptr;
    return std::unique_ptr<PCVariableContainer>(new PCVariableContainer(V));
}
