import sys

inpath = sys.argv[1]
outpath = sys.argv[2]

infile = open(inpath, "r")
outfile = open(outpath, "w")

header_guard = outpath.replace("src", "") \
    .replace("/", "_") \
    .replace(".", "_") \
    .upper()

header_text = ""
header_text += f"#ifndef {header_guard}\n"
header_text += f"#define {header_guard}\n\n"

in_text = infile.read().strip()

var_name = header_guard.lower().replace("_hh", "")

header_text += f"const char* lua_script{var_name} = R\"lua(\n"

for line in in_text.split("\n"):
    header_text += f"{line}\n"

header_text += ")lua\";\n\n"
header_text += f"#endif // {header_guard}\n"

outfile.write(header_text)

infile.close()
outfile.close()
