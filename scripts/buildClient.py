import os
import re
import subprocess
import shutil

Import("env")

from _common import getPaths


pattern = re.compile(r".*\.LICENSE\.txt$|asset-manifest.json")

def ignoreFiles(dir, files):
    return [f for f in files if pattern.match(f)]

def buildReact(source, target, env):
    clientDir, buildDir, dataDir = getPaths(env)
   
    print("⏳ Starting React build in ", clientDir)

    try:
        if not (os.path.isdir(buildDir) and os.listdir(buildDir)):
            subprocess.check_call(['npm.cmd', 'ci'], cwd = clientDir)
            subprocess.check_call(['npm.cmd', 'run', 'build'], cwd = clientDir)
            print("✔ React build finished.")
        else:
            print("⚠ React build exists, skipping npm build.")
    
        if os.path.exists(dataDir):
            for item in os.listdir(dataDir):
                itemPath = os.path.join(dataDir, item)
                if os.path.isdir(itemPath):
                    shutil.rmtree(itemPath)
                else:
                    itemPath.unlink() if hasattr(itemPath, 'unlink') else os.unlink(itemPath)
        else:
            os.makedirs(dataDir)
        
        if not os.path.isdir(buildDir):
            raise FileNotFoundError(f"Build directory not found: {buildDir}")

        shutil.copytree(buildDir, dataDir, dirs_exist_ok=True, ignore=ignoreFiles)
        print("✔ Build copy finished.")
    except Exception as e:
        print("✖ React build or copy failed: ", e)
        raise

try:
    print("Registering 'build and copy react' action for 'buildfs' event")
    env.AddPreAction("buildfs", buildReact)
except NameError:
    pass