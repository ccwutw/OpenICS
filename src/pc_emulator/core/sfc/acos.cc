#include "src/pc_emulator/include/sfc/acos.h"
#include "src/pc_emulator/include/utils.h"


using namespace std;
using namespace pc_emulator;
using namespace pc_specification;

void ACOS::Execute(PCVariable *CurrentResult,
    std::vector<PCVariable*>& Operands) {
    auto configuration = __AssociatedResource->__configuration;
    auto CR = CurrentResult;
    if (!Utils::IsRealType(CR->__VariableDataType)) {
        configuration->PCLogger->RaiseException("ACOS SFC error: CR is not "
            " a real number");
    }

    if (CR->__VariableDataType->__DataTypeCategory == DataTypeCategory::REAL) {
        float RealValue = CR->GetValueStoredAtField<float>("",
                DataTypeCategory::REAL);
        RealValue = acos(RealValue);
        CR->SetField("", &RealValue, sizeof(RealValue));
    } else {
        double LRealValue = CR->GetValueStoredAtField<double>("",
                DataTypeCategory::LREAL);
        LRealValue = acos(LRealValue);
        CR->SetField("", &LRealValue, sizeof(LRealValue));
    }
}