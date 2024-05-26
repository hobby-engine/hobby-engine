import sys

args = sys.argv

script_path = args[1]
header_path = args[2]
var_name = args[3]

header_guard = header_path.replace("/", "_").replace(".", "_").replace("src", "").upper()

print(f"writing {header_path}...")

src = ""
src += f"#ifndef {header_guard}\n"
src += f"#define {header_guard}\n\n"

script = open(script_path, "r")

src += f"const char {var_name}[] = R\"lua(\n";
src += script.read()
src += f")lua\";\n\n";

script.close()

src += f"#endif // {header_guard}"

header = open(header_path, "w")
header.write(src)
header.close()
