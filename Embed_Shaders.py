import glob, os
from pathlib import Path

bin_path = 'shaders/bin/'
source_file = 'include/Resources/binary_resources.hpp'

def Get_File_Byte_String(filePath):
    val = "";
    with open(filePath, "rb") as file:
        byte_data = file.read();
        for byte in byte_data:
            val += f"0x{byte:02x},";
    return val[:-1];

def process_spv(filename, filePath):
    
    bin_str = Get_File_Byte_String(filePath);
    return f"const std::vector<uint8_t> {filename} {{ {bin_str} }};\n";


init_src = "";
spv_programs_src = "";

print("Compiling resources...")

print("Loading SPRv programs...")

for file in glob.glob(bin_path + "*.spv"):
    filename = os.path.splitext(os.path.basename(file))[0];
    print(f"\tLoad SPRv file: {filename}");
    init_src += f'spv_programs["{filename}"] = {filename};\n';
    spv_programs_src += process_spv(filename, file);



source_text = f"""
#pragma once

// This is a generated file. Do not edit directly.

#include <vector>
#include <unordered_map>
#include <stdint.h>

namespace SLCompute
{{
namespace Resources
{{
namespace Shader_Binaries
{{

{spv_programs_src}
std::unordered_map<std::string, std::vector<uint8_t>> spv_programs;

std::vector<std::string> Get_SPV_Programs()
{{
    std::vector<std::string> keys;
    for (const auto& pair : spv_programs) {{
        keys.push_back(pair.first);
    }}
    return keys;
}}

std::vector<uint8_t> Get_SPV_Binary(std::string name) {{ return spv_programs[name]; }}

static bool initialized = false;
void Init()
{{
if (initialized) return;
initialized = true;
{init_src}
}}



}} // namespace Shader_Binaries
}} // namespace Resources
}} // namespace SLC
"""

print("Writing 'include\\Resources\\binary_resources.hpp'")
Path(source_file).parent.mkdir(parents=True, exist_ok=True)
with open(source_file, "w") as file:
    file.write(source_text)

print("Finished compiling resources.")






    