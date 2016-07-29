-- This file contains special configurations values, such as directories to extern libraries (Qt)
-- Editing this file is not required to use/compile the engine, as default values should be enough

-- Builds Nazara extern libraries (such as lua/STB)
BuildDependencies = true

-- Builds Nazara examples
BuildExamples = true

-- Setup additionnals install directories, separated by a semi-colon ; (library binaries will be copied there)
--InstallDir = "/usr/local/lib64"

-- Excludes client-only modules/tools/examples
ServerMode = false

-- Builds modules as one united library (useless on POSIX systems)
UniteModules = false

-- Qt5 include directories
--Qt5IncludeDir = [[C:\Users\Lynix\Documents\Qt\5.6\msvc2015\include]]
--Qt5BinDir_x86 = [[C:\Users\Lynix\Documents\Qt\5.6\msvc2015\bin]]
--Qt5BinDir_x64 = [[C:\Users\Lynix\Documents\Qt\5.6\msvc2015_64\bin]]
--Qt5LibDir_x86 = [[C:\Users\Lynix\Documents\Qt\5.6\msvc2015\lib]]
--Qt5LibDir_x64 = [[C:\Users\Lynix\Documents\Qt\5.6\msvc2015_64\lib]]
