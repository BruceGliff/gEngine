$copyFromPath = $PSScriptRoot+"\res"
$copyToPath = $PSScriptRoot+"\build\bin\Debug\"

Copy-Item -Recurse -Force $copyFromPath $copyToPath