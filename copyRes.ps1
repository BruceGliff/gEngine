$copyFromPath = $PSScriptRoot+"\res"
$copyToPath = $PSScriptRoot+"\build\bin\Release\"

Copy-Item -Recurse -Force $copyFromPath $copyToPath