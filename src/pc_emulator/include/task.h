#ifndef __PC_EMULATOR_INCLUDE_TASK_H__
#define __PC_EMULATOR_INCLUDE_TASK_H__

#include <iostream>
#include <fcntl.h>
#include <fstream>
#include <unordered_map>
#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>

#include "pc_logger.h"
#include "pc_mem_unit.h"
#include "pc_variable.h"
#include "executor.h"
#include "src/pc_emulator/proto/configuration.pb.h"

using namespace std;
using namespace pc_specification;

using MemType  = pc_specification::MemType;
using DataTypeCategory = pc_specification::DataTypeCategory;
using FieldInterfaceType = pc_specification::FieldInterfaceType;


namespace pc_emulator {

    class PCConfigurationImpl;
    class PCVariable;
    class PCResourceImpl;
    class Task;
    class FunctionsRegistry;


    class ProgramContainer {
        public:
            string __ProgramName;
            PCResourceImpl * __AssociatedResource;
            PCVariable * __ExecPoUVariable;
            std::unique_ptr<Executor> __AssociatedExecutor;
            std::vector<ProgramVariableInitialization> __initialization_map;
            Task * __AssociatedTask;

            ProgramContainer(PCResourceImpl * AssociatedResource, 
                const ProgramSpecification& program_spec, Task * AssociatedTask);

            void Cleanup();
    };


    class Task {
        public :
            string __TaskName;
            int __priority;
            TaskType type;
            int __interval_ms;
            PCConfigurationImpl * __configuration;
            PCResourceImpl * __AssociatedResource;
            PCVariable * __CR;
            string __trigger_variable_name;
            bool __trigger_variable_previous_value;
            bool __IsReady;
            bool __Executing;
            double __nxt_schedule_time_ms;
            std::vector<std::unique_ptr<ProgramContainer>> __AssociatedPrograms;
            FunctionsRegistry * FCRegistry;
            

            Task(PCConfigurationImpl * configuration,
                PCResourceImpl * AssociatedResource,
                const IntervalTaskSpecification& task_spec);

            Task(PCConfigurationImpl * configuration,
                PCResourceImpl * AssociatedResource,
                const InterruptTaskSpecification& task_spec);

            void SetNextScheduleTime(double nxt_schedule_time_ms) {
                __nxt_schedule_time_ms = nxt_schedule_time_ms;
            };

            void AddProgramToTask(const ProgramSpecification& program_spec);

            void Execute();

            void Cleanup();

            

    };
}

#endif