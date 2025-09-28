from os.path import isfile
import shlex

Import('env')

env_path = ".env"

if not isfile(env_path):
    print("❌ File .env not found, skipping...")
else:
    build_flags = []
    with open(env_path, "r") as f:
        for line in f:
            line = line.strip()

            if not line or line.startswith("#"):
                continue
            if "=" in line:
                key, value = line.split("=", 1)
                key = key.strip()
                value = value.strip()
                value_escaped = shlex.quote(value)

                build_flags.append(f'-D{key}=\\"{value_escaped}\\"')
            else:
                build_flags.append(f"-D{line}")
    if build_flags:
        env.Append(BUILD_FLAGS=build_flags)
