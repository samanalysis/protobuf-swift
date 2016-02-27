// Protocol Buffers for Swift
//
// Copyright 2014 Alexey Khohklov(AlexeyXo).
// Copyright 2008 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "swift_service.h"

#include <algorithm>
#include <google/protobuf/stubs/hash.h>
#include <google/protobuf/stubs/strutil.h>
#include <google/protobuf/io/printer.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include "swift_helpers.h"
#include "swift_method.h"
namespace google { namespace protobuf { namespace compiler { namespace swift {
    
    namespace {
        
        void SetMapVariables(const ServiceDescriptor* descriptor, map<string, string>* variables) {
            (*variables)["acontrol"] = GetAccessControlType(descriptor->file());
            (*variables)["className"] =  ClassName(descriptor);
//            (*variables)["classNameReturnedType"] = ClassNameReturedType(descriptor);
//            (*variables)["fileName"] = FileClassName(descriptor->file());
        }
        
    }  // namespace
    
    
    ServiceGenerator::ServiceGenerator(const ServiceDescriptor* descriptor) : descriptor_(descriptor) {
        SetMapVariables(descriptor, &variables_);
    }
    
    ServiceGenerator::~ServiceGenerator() {
    }
    
    void ServiceGenerator::GenerateSource(io::Printer* printer) {
        printer->Print(variables_,"$acontrol$ class $className$ {\n");
        printer->Indent();
        
        for (int i = 0; i < descriptor_->method_count(); i++) {
            MethodGenerator(descriptor_->method(i)).GenerateSource(printer);
        }

        printer->Outdent();
        printer->Print("}\n");
    }
    
}  // namespace swift
}  // namespace compiler
}  // namespace protobuf
}  // namespace google