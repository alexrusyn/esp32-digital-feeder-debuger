import os

def getPaths(env):
    projectDir = env['PROJECT_DIR']
    clientDir = os.path.join(projectDir, 'client')
    buildDir = os.path.join(clientDir, 'build')
    dataDir = os.path.join(projectDir, 'data')
    return clientDir, buildDir, dataDir
